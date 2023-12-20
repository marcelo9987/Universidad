#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>
#include <signal.h>
#include <sys/wait.h>

#define K_MAX_TAMANHO_MENSAJE 1000


void manejadorDeSIGINT(int senhal)
{
    printf("Servidor.- Finalizando la ejecución.\n\n");

    // exit fuerza al SO a cerrar el socket de escucha y a liberar el puerto
    exit(EXIT_SUCCESS);
}


void manejadorDeSIGCHLD(int senhal)
{
    while (waitpid(WAIT_ANY, NULL, WNOHANG) > 0)
    {
        printf("[Padre %5d] Servidor.- Detectado proceso hijo finalizado.\n\n", getpid());
    }
}

int esperarPeticion(int socketEscucha, struct sockaddr_in *datosConexionCliente, pid_t pid_padre)
{
    int socketConexion;

    socklen_t tam_sockaddr_in = sizeof(struct sockaddr_in);

    // ---Esperamos a que se conecte un cliente y atendemos la conexión---
    if ((socketConexion = accept(socketEscucha, (struct sockaddr *) &datosConexionCliente, &tam_sockaddr_in)) == -1)
    {
        printf("[Padre %5d] Error en la función inet_ntop\n", pid_padre);
        perror("Error en la función accept");
        // En esta versión no se hace un exit al poder haber otros procesos en marcha en ese momento.
//        exit(EXIT_FAILURE);
    }

    return socketConexion;
}

void muestraDatosCliente(struct sockaddr_in *datosConexionCliente, pid_t pid_hijo)
{
    char ipCliente[INET_ADDRSTRLEN];
    // ---Recuperamos la IP y el puerto del cliente---
    if (inet_ntop(AF_INET, &(*datosConexionCliente).sin_addr, ipCliente, INET_ADDRSTRLEN) == NULL)
    {
        printf("[Hijo  %5d] Error en la función inet_ntop\n", pid_hijo);
        perror("Error en la función inet_ntop");

        // En esta versión no se hace un exit al poder haber otros procesos en marcha en ese momento.
        return;
    }

    // Convertimos la ip del cliente a formato textual
    uint16_t puertocliente = htons((*datosConexionCliente).sin_port);  // Pasamos el puerto del cliente

    // --

    // Imprimimos IP y puerto de cada cliente que se conecte
    printf("[Hijo  %5d] Recibida petición. IP del cliente: %s Puerto del cliente: %d\n", pid_hijo, ipCliente, puertocliente);
}

void gestionarPeticion(int socketConexion, pid_t pid_hijo)
{
    char mensaje[K_MAX_TAMANHO_MENSAJE];

    bool detectadoFinDeArchivo = false;

    while (!detectadoFinDeArchivo)
    {
        // Recuperamos una línea de texto
        size_t lenMensajeRecibido = recv(socketConexion, mensaje, K_MAX_TAMANHO_MENSAJE, 0);

        if (lenMensajeRecibido == -1)
        {
            printf("[Hijo  %5d] Error en la función recv\n", pid_hijo);
            perror("Error en la función recv");
            exit(EXIT_FAILURE);
        }

        if (lenMensajeRecibido == 0)
        {
            detectadoFinDeArchivo = true;

            printf("[Hijo  %5d] Servidor.- Detectado fin de archivo. Cerramos el socket\n\n", pid_hijo);

            // --

            // Cerramos el socket de conexión
            if (close(socketConexion) != 0)
            {
                printf("[Hijo  %5d] Error en la función close\n", pid_hijo);
                perror("Error al intentar cerrar el socket de la conexión");
                exit(EXIT_FAILURE);
            }

        } else
        {

            printf("[Hijo  %5d] Linea recibida: <%s> (%ld bytes)\n", pid_hijo, mensaje, lenMensajeRecibido);

            // --

            // Usamos el bucle for para convertir la línea a mayúsculas, carácter a carácter
            for (int pos = 0; mensaje[pos] != '\0'; pos++)
            {
                mensaje[pos] = toupper(mensaje[pos]);
            }

            // --

            // Le enviamos la línea en mayúsculas al cliente
            if (send(socketConexion, mensaje, lenMensajeRecibido, 0) < 0)
            {
                printf("[Hijo  %5d] Error en la función send\n", pid_hijo);
                perror("Error en la función send");
                exit(EXIT_FAILURE);
            }

            printf("[Hijo  %5d] Linea ENVIADA:  <%s> (%ld bytes)\n\n", pid_hijo, mensaje, lenMensajeRecibido);

        }

    }

}

int main(int argc, char *argv[])
{

    if (argc != 2)
    {
        printf("Es necesario introducir el puerto por línea de comandos.\n");
        printf("Uso: .\\%s PUERTO\n", argv[0]);

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

    // Registramos los manejadores de señales

    if (signal(SIGINT, manejadorDeSIGINT) == SIG_ERR)
    {
        perror("Error en la función signal");
        exit(EXIT_FAILURE);
    }

    if (signal(SIGCHLD, manejadorDeSIGCHLD) == SIG_ERR)
    {
        perror("Error en la función signal");
        exit(EXIT_FAILURE);
    }

    // --

    const pid_t pid_padre = getpid();

    printf("[Padre %5d] Servidor.- Iniciando...\n\n", pid_padre);

    // --- Creamos el socket por el que se va a escuchar ---
    int socketEscucha;
    // El 0 indica que se le deja al proveedor de servicios escoger el protocolo más adecuado
    if ((socketEscucha = socket(AF_INET, SOCK_STREAM, 0)) == -1)
    {
        perror("Error en la función socket");
        exit(EXIT_FAILURE);
    }

    // --

    struct sockaddr_in datosConexionServidor;
    datosConexionServidor.sin_family = AF_INET;
    datosConexionServidor.sin_addr.s_addr = htonl(INADDR_ANY);  // Aceptamos conexiones desde cualquiera de las IPs de esta máquina
    datosConexionServidor.sin_port = htons(numPuertoEscucha);  // Introducimos el puerto en la estructura sockaddr_in

    // --

    // Asignamos la estructura sockaddr_in llamada "datosConexionServidor" al socket
    if (bind(socketEscucha, (struct sockaddr *) &datosConexionServidor, sizeof(struct sockaddr_in)) == -1)
    {
        perror("Error en la función bind");
        exit(EXIT_FAILURE);
    }

    // --

    // --- Ponemos el socket a la escucha ---
    if (listen(socketEscucha, 10) == -1)
    {
        // Con listen marcamos el socket como pasivo para atender e introducimos el número de peticiones de clientes que pueden estar en cola a la espera de ser atendidos
        perror("Error en la función listen");
        exit(EXIT_FAILURE);
    }

    printf("[Padre %5d] Servidor.- Escuchando por el puerto %d.\n\n", pid_padre, numPuertoEscucha);

    // --

    // Ponemos un bucle que se repita mientras no se pulse Ctrl+C
    while (true)
    {
        printf("--------------------------------------\n\n");
        printf("[Padre %5d] Servidor.- Esperando nueva petición...\n\n", pid_padre);

        struct sockaddr_in datosConexionCliente;

        int socketConexion = esperarPeticion(socketEscucha, &datosConexionCliente, pid_padre);

        if (socketConexion >= 0)
        {
            //Recibida conexión válida

            pid_t pid_hijo = fork();
            if (pid_hijo == -1)
            {
                perror("Error en la función fork");
                // En esta versión no se hace un exit al poder haber otros procesos en marcha en ese momento.
                close(socketConexion);
            } else if (pid_hijo != 0)
            {
                // Soy el padre
                close(socketConexion);
            } else
            {
                // Soy el hijo

                pid_hijo = getpid();

                //Imprimo el proceso que atiende la petición
                printf("[Hijo  %5d] Servidor.- Petición recibida. Realizamos su procesamiento.\n\n", pid_hijo);

                muestraDatosCliente(&datosConexionCliente, pid_hijo);

                gestionarPeticion(socketConexion, pid_hijo);

                printf("[Hijo  %5d] Servidor.- Procesamiento concluido. Finalizamos este proceso.\n\n", pid_hijo);
                exit(EXIT_SUCCESS);
            }
        }

    }

    ////********** INACCESIBLE **********////

    // --

    close(socketEscucha); // Cerramos el socket pasivo de servidor antes de finalizar

    // --

    return (EXIT_SUCCESS);
}
