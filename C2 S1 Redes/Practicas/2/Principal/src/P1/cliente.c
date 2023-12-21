#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdbool.h>

#define K_MAX_TAMANHO_MENSAJE 1000

int main(int argc, char *argv[])
{
    if (argc < 3 || argc > 5)
    {
        printf("Es necesario introducir la dirección IP y el puerto por línea de comandos\n");
        printf("Uso: .\\%s IP PUERTO [opcional SEGUNDOS [opcional BYTES_LECTURA]]\n", argv[0]);
        printf("\t SEGUNDOS: Tiempo de espera entre que se establece la conexión y se recibe el mensaje (para poder hacer el apartado c).\n");
        printf("\t BYTES_LECTURA: Número de bytes que se leen en cada lectura (para poder hacer el apartado d).\n");

        // Ponemos un código de error en el caso de que el usuario no introduzca el número de parámetros esperados
        exit(EXIT_FAILURE);
    }

    // --

    // Pasamos el puerto de un string a un unsigned int de 16 bits
    // Como el puerto es de 16b y el strtol devuelve un long, comprobamos si el valor es aceptable para un posible uso en sockets.
    long _numPuertoServidor = strtol(argv[2], NULL, 10);
    if (_numPuertoServidor <= 0 || _numPuertoServidor > 65535)
    {
        printf("Error: El puerto debe ser un número entre 1 y 65535\n");
        exit(EXIT_FAILURE);
    }

    u_int16_t numPuertoServidor = (u_int16_t) _numPuertoServidor;

    // --

    long segundosEspera = 0;
    if (argc >= 4)
    {
        segundosEspera = strtol(argv[3], NULL, 10);
        if (segundosEspera < 0)
        {
            printf("\nERROR: El número de segundos debe ser un número positivo\n");
            exit(EXIT_FAILURE);
        }

        printf("\nAviso: Se esperarán %ld segundos entre que se establece la conexión y se recibe el mensaje.\n\n", segundosEspera);
    }

    // --

    bool usarBucleWhileEnRecepcion = false;

    long bytesArecibir = K_MAX_TAMANHO_MENSAJE;
    if (argc == 5)
    {
        usarBucleWhileEnRecepcion = true;

        bytesArecibir = strtol(argv[4], NULL, 10);
        if (bytesArecibir <= 0 || bytesArecibir > K_MAX_TAMANHO_MENSAJE)
        {
            printf("\nERROR: El número de bytes debe ser un número positivo menor o igual que %d\n", K_MAX_TAMANHO_MENSAJE);
            exit(EXIT_FAILURE);
        }

        printf("\nAviso: Se leerán %ld bytes en cada lectura.\n\n", bytesArecibir);
    }

    // --

    // Creamos el socket de conexión
    int socketConexion;
    // El 0 indica que se le deja al proveedor de servicios escoger el protocolo más adecuado
    if ((socketConexion = socket(AF_INET, SOCK_STREAM, 0)) < 0)
    {
        perror("Error en la función socket");
        exit(EXIT_FAILURE);
    }

    // --

    // Dirección IP introducida por el usuario
    char *dir_ip = argv[1];

    // Introducimos en la estructura sockaddr_in la IP y el puerto
    struct sockaddr_in cli;
    cli.sin_family = AF_INET;
    cli.sin_addr.s_addr = inet_addr(dir_ip); // inet_addr()  traduce una cadena en notación decimal estándar a una dirección IPv4 en Network Byte Order (Independiente de la arquitectura)
    if (cli.sin_addr.s_addr == (in_addr_t) -1)
    {
        fprintf(stderr,"Error: La dirección ip (%s) introducida como parámetro no es válida\n", dir_ip);
        exit(EXIT_FAILURE);
    }
    cli.sin_port = htons(numPuertoServidor); // htons() traduce una IPv4 de Host Byte Order(Formato específico de la arquitectura) a Network Byte Order (Independiente a la arquitectura)

    // --

    // Solicitamos la conexión con el servidor
    if (connect(socketConexion, (struct sockaddr *) &cli, sizeof(struct sockaddr_in)) < 0)
    {
        perror("Error en la función connect");
        exit(EXIT_FAILURE);
    }

    // --

    if (segundosEspera > 0)
    {
        printf("\nDuermo %ld segundos\n", segundosEspera);
        sleep(segundosEspera);
        printf("Despierto\n\n");
    }

    // --

    long numBytesRecibidos;
    char mensajeRecibido[K_MAX_TAMANHO_MENSAJE + 1];

    if (!usarBucleWhileEnRecepcion)
    {
        printf("Recibiendo mensaje...\n");

        // Con recv recuperamos el mensaje recibido y el número de bytes que ocupa
        if ((numBytesRecibidos = recv(socketConexion, mensajeRecibido, K_MAX_TAMANHO_MENSAJE, 0)) < 0)
        {
            perror("Error en la función recv");
            exit(EXIT_FAILURE);
        }

        // Añadimos un '\0' al final del mensaje para evitar que aparezcan caracteres extraños
        mensajeRecibido[numBytesRecibidos] = '\0';

        // Imprimimos el mensaje y el número de bytes que ocupa este
        printf("Mensaje recibido: %s\n", mensajeRecibido);
        printf("Bytes recibidos: %ld\n", numBytesRecibidos);

    } else
    {
        printf("Recibiendo mensaje de %ld bytes...\n", bytesArecibir);

        long totalBytesRecibidos = 0;

        while ((numBytesRecibidos = recv(socketConexion, mensajeRecibido, bytesArecibir, 0)) > 0)
        {

            // Añadimos un '\0' al final del mensaje para evitar que aparezcan caracteres extraños
            mensajeRecibido[numBytesRecibidos] = '\0';

            // Imprimimos el mensaje y el número de bytes que ocupa este
            printf("Mensaje recibido: %s\n", mensajeRecibido);
            printf("Bytes recibidos: %ld\n", numBytesRecibidos);

            totalBytesRecibidos += numBytesRecibidos;
        }

        if (numBytesRecibidos < 0)
        {
            perror("Error en la función recv");
            exit(EXIT_FAILURE);
        }

        printf("\nTotal bytes recibidos: %ld\n", totalBytesRecibidos);
    }

    // --

    // Antes de salir cerramos el socket
    if (close(socketConexion) == -1)
    {
        perror("Error en la función close al intentar cerrar el socket de la conexión");
        exit(EXIT_FAILURE);
    }

    // --

    printf("Cliente.- Finalizo el programa.\n\n");

    return (EXIT_SUCCESS);
}
