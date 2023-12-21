#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <string.h>
#include <stdbool.h>
#include <signal.h>

#define K_MAX_TAMANHO_MENSAJE 1000

void manejadorDeSenhales(int senhal)
{
    printf("Servidor.- Finalizando la ejecución.\n\n");

    // exit fuerza al SO a cerrar el socket de escucha y a liberar el puerto
    exit(EXIT_SUCCESS);
}

int esperarPeticion(int socketEscucha);

void gestionarPeticion(int socketConexion, bool enviarSegundoMensaje, long segundosEspera);


int main(int argc, char *argv[])
{

    if (argc != 2 && argc != 3)
    {
        printf("Es necesario introducir el puerto por línea de comandos.\n");
        printf("Uso: .\\%s PUERTO [opcional APARTADO]\n", argv[0]);
        printf("\t APARTADO: apartado específico a ejecutar:\n");
        printf("\t\tC0: envía un segundo mensaje al cliente.\n");
        printf("\t\tC1: envía un segundo mensaje al cliente con un segundo de espera antes del segundo envío.\n");
        printf("\t\t<OTROS>: Se ejecuta de forma normal.\n");

        // Se devuelve un código de error en caso de que el usuario no introduzca el puerto por línea de comandos
        exit(EXIT_FAILURE);
    }

    // --

    bool enviarSegundoMensaje = false;
    long segundosEspera = 0;

    if (argc == 3)
    {
        if (strcasecmp(argv[2], "C0") == 0)
        {
            enviarSegundoMensaje = true;

        } else if (strcasecmp(argv[2], "C1") == 0)
        {
            enviarSegundoMensaje = true;
            segundosEspera = 1;
        }
    }

    // --

    // --- Creamos el socket por el que se va a escuchar ---
    int socketEscucha;
    // El 0 indica que se le deja al proveedor de servicios escoger el protocolo más adecuado
    if ((socketEscucha = socket(AF_INET, SOCK_STREAM, 0)) < 0)
    {
        perror("Error en la función socket");
        exit(EXIT_FAILURE);
    }

    // --

    // Pasamos el puerto de un string a un unsigned int de 16 bits
    // Como el puerto es de 16b y el strtol devuelve un long, comprobamos si el valor es aceptable para un posible uso en sockets.
    long _numPuertoEscucha = strtol(argv[1], NULL, 10);
    if (_numPuertoEscucha <= 0 || _numPuertoEscucha > 65535)
    {
        printf("Error: El puerto debe ser un número entre 1 y 65535\n");
        exit(EXIT_FAILURE);
    }

    u_int16_t numPuertoEscucha = (u_int16_t) _numPuertoEscucha;

    // --

    // Registramos el manejador de señales
    if (signal(SIGINT, manejadorDeSenhales) == SIG_ERR)
    {
        perror("Error en la función signal");
        exit(EXIT_FAILURE);
    }

    // --

    struct sockaddr_in ser;
    ser.sin_family = AF_INET;
    ser.sin_addr.s_addr = htonl(INADDR_ANY);  // Aceptamos conexiones desde cualquiera de las IPs de esta máquina
    ser.sin_port = htons(numPuertoEscucha);  // Introducimos el puerto en la estructura sockaddr_in

    // --

    // Asignamos la estructura sockaddr_in llamada "ser" al socket
    if (bind(socketEscucha, (struct sockaddr *) &ser, sizeof(struct sockaddr_in)) < 0)
    {
        perror("Error en la función bind");
        exit(EXIT_FAILURE);
    }

    // --

    // --- Ponemos el socket a la escucha ---
    if (listen(socketEscucha, 10) < 0)
    {
        // Con listen marcamos el socket como pasivo para atender e introducimos el número de peticiones de clientes que pueden estar en cola a la espera de ser atendidos
        perror("Error en la función listen");
        exit(EXIT_FAILURE);
    }

    printf("Servidor.- Escuchando por el puerto %d.\n\n", numPuertoEscucha);

    // --

    // Ponemos un bucle que se repita mientras no se pulse Ctrl+C
    while (true)
    {
        printf("--------------------------------------\n\n");
        printf("Servidor.- Esperando nueva petición...\n\n");

        int socketConexion = esperarPeticion(socketEscucha);

        printf("Servidor.- Petición recibida. Realizamos su procesamiento.\n\n");

        gestionarPeticion(socketConexion, enviarSegundoMensaje, segundosEspera);

        printf("Servidor.- Procesamiento finalizado.\n\n");

    }

    ////********** INACCESIBLE **********////

    // --

    close(socketEscucha); // Cerramos el socket pasivo de servidor antes de finalizar

    // --

    return (EXIT_SUCCESS);
}

int esperarPeticion(int socketEscucha)
{
    int socketConexion;

    struct sockaddr_in cli;
    socklen_t tam_sockaddr_in = sizeof(struct sockaddr_in);

    // ---Esperamos a que se conecte un cliente y atendemos la conexión---
    if ((socketConexion = accept(socketEscucha, (struct sockaddr *) &cli, &tam_sockaddr_in)) < 0)
    {
        // Esperamos a que se conecte un cliente y atendemos la conexión
        perror("Error en la función accept");
        exit(EXIT_FAILURE);
    }

    // ---Recuperamos la IP y el puerto del cliente---
    char ipCliente[INET_ADDRSTRLEN];
    if (inet_ntop(AF_INET, &cli.sin_addr, ipCliente, INET_ADDRSTRLEN) == NULL)
    {
        // Convertimos la ip del cliente a formato textual
        perror("Error en la función inet_ntop");
        exit(EXIT_FAILURE);
    }

    uint16_t puertocliente = htons(cli.sin_port);  // Pasamos el puerto del cliente

    // --

    // Imprimimos IP y puerto de cada cliente que se conecte
    printf("Recibida petición. IP del cliente: %s Puerto del cliente: %i\n", ipCliente, puertocliente);

    // --

    return socketConexion;
}

void gestionarPeticion(int socketConexion, bool enviarSegundoMensaje, long segundosEspera)
{
    char mensaje[K_MAX_TAMANHO_MENSAJE] = "Saludos desde el servidor";

    // ---Enviamos el mensaje al cliente---
    if (send(socketConexion, mensaje, strlen(mensaje), 0) < 0)
    {
        perror("Error en la función send");
        exit(EXIT_FAILURE);
    }

    // --

    if (enviarSegundoMensaje)
    {
        if (segundosEspera > 0)
        {
            sleep(segundosEspera);
        }

        char mensaje2[K_MAX_TAMANHO_MENSAJE] = "Este es mi segundo mensaje";

        // ---- Enviamos el segundo mensaje al cliente ---
        if (send(socketConexion, mensaje2, strlen(mensaje2), 0) < 0)
        {
            perror("Error en la función send");
            exit(EXIT_FAILURE);
        }

        printf("Segundo mensaje enviado.\n");
    }


    // Cerramos el socket de conexión
    if (close(socketConexion) != 0)
    {
        perror("Error al intentar cerrar el socket de la conexión");
        exit(EXIT_FAILURE);
    }

}
