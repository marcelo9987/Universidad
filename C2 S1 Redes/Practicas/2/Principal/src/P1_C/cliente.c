#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define K_MAX_TAMANHO_MENSAJE 1000

int main(int argc, char *argv[])
{
    if (argc != 3)
    {
        printf("Es necesario introducir la dirección IP y el puerto por línea de comandos\n");
        printf("Uso: .\\%s IP PUERTO\n", argv[0]);
        exit(EXIT_FAILURE);  // Ponemos un código de error en el caso de que el usuario no introduzca la IP y el puerto por línea de comandos
    }


    int socketConexion;
    // El 0 indica que se le deja al proveedor de servicios escoger el protocolo más adecuado
    if ((socketConexion = socket(AF_INET, SOCK_STREAM, 0)) < 0)
    {
        perror("Error en la función socket");
        exit(EXIT_FAILURE);
    }

    struct sockaddr_in cli;
    u_int16_t numPuertoServidor = (u_int16_t) strtol(argv[2], NULL, 10);                 // Pasamos el puerto de un string a un int
    cli.sin_family = AF_INET;                   // Introducimos el puerto y la IP en una estructura sockaddr_in
    cli.sin_addr.s_addr = inet_addr(argv[1]);// Leemos la dirección IP introducida por el usuario
    cli.sin_port = htons(numPuertoServidor);

    // Solicitamos la conexión con el servidor
    if (connect(socketConexion, (struct sockaddr *) &cli, sizeof(struct sockaddr_in)) < 0)
    {
        perror("Error en la función connect");
        exit(EXIT_FAILURE);
    }

//   printf("Duermo 2 segundos\n");
//   sleep(2);
//   printf("Despierto\n");

    long numBytesRecibidos;
    char mensajeRecibido[K_MAX_TAMANHO_MENSAJE+1];
    if ((numBytesRecibidos = recv(socketConexion, mensajeRecibido, K_MAX_TAMANHO_MENSAJE, 0)) < 0)
    {               // Con recv recuperamos el mensaje recibido y el número de bytes que ocupa
        perror("Error en la función recv");
        exit(EXIT_FAILURE);
    }

    mensajeRecibido[numBytesRecibidos] = '\0';                     // Añadimos un '\0' al final del mensaje para evitar que aparezcan caracteres extraños

    printf("Mensaje recibido: %s\n", mensajeRecibido);                      // Imprimimos el mensaje y el número de bytes que ocupa este
    printf("Bytes recibidos: %ld\n", numBytesRecibidos);

    close(socketConexion);                // Antes de salir cerramos el socket

    return (EXIT_SUCCESS);
}
