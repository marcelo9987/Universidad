#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <string.h>

#define K_MAX_TAMANHO_MENSAJE 1000


int main(int argc, char *argv[])
{

    if (argc != 2)
    {
      // Ponemos un código de error en caso de que el usuario no introduzca el puerto por línea de comandos
        printf("Es necesario introducir el puerto por línea de comandos.\n");
        printf("Uso: .\\%s PUERTO\n", argv[0]);
        exit(EXIT_FAILURE);
    }

  // --- Creamos el socket por el que se va a escuchar ---
    int socketEscucha;
    // El 0 indica que se le deja al proveedor de servicios escoger el protocolo más adecuado
    if ((socketEscucha = socket(AF_INET, SOCK_STREAM, 0)) < 0)
    {
        perror("Error en la función socket");
        exit(EXIT_FAILURE);
    }

    uint16_t numPuertoEscucha = (u_int16_t) strtol(argv[1], NULL, 10);                 // Pasamos el puerto de un string a un int
    struct sockaddr_in ser;
    ser.sin_family = AF_INET;               // Introducimos el puerto en la estructura sockaddr_in
    ser.sin_addr.s_addr = htonl(INADDR_ANY);
    ser.sin_port = htons(numPuertoEscucha);

    if (bind(socketEscucha, (struct sockaddr *) &ser, sizeof(struct sockaddr_in)) < 0)
    {               // Asignamos la estructura sockaddr_in ser al socket
        perror("Error en la función bind");
        exit(EXIT_FAILURE);
    }

  // --- Ponemos el socket a la escucha ---
    if (listen(socketEscucha, 10) < 0)
    {
      // Con listen marcamos el socket como pasivo para atender e introducimos el número de peticiones de clientes que pueden estar en cola a la espera de ser atendidos
        perror("Error en la función listen");
        exit(EXIT_FAILURE);
    }


  // Ponemos un bucle que se repita mientras no se pulse Ctrl+C
    while (1)
    {
      // ---Esperamos a que se conecte un cliente y atendemos la conexión---
        int socketConexion;
        struct sockaddr_in cli;
        socklen_t tam_sockaddr_in = sizeof(struct sockaddr_in);
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

        uint16_t puertocliente = htons(cli.sin_port);                // Pasamos el puerto del cliente

        printf("IP del cliente: %s Puerto del cliente: %i\n", ipCliente, puertocliente);                 // Imprimimos IP y puerto de cada cliente que se conecte

      // ---Enviamos el mensaje al cliente---
        char mensaje[K_MAX_TAMANHO_MENSAJE] = "Saludos desde el servidor";
        if (send(socketConexion, mensaje, strlen(mensaje), 0) < 0)
        {
          // Enviamos el mensaje al cliente
            perror("Error en la función send");
            exit(EXIT_FAILURE);
        }

//       fflush(NULL);
//       printf("Primer mensaje enviado. Duermo 1 segundo\n");
//       sleep(2);
//       printf("Despierto\n");

      // ---- Enviamos el segundo mensaje al cliente ---
        char mensaje2[K_MAX_TAMANHO_MENSAJE] = "Este es mi segundo mensaje";
        if (send(socketConexion, mensaje2, strlen(mensaje2), 0) < 0)
        {
          // Enviamos el mensaje al cliente
            perror("Error en la función send");
            exit(EXIT_FAILURE);
        }

        printf("Segundo mensaje enviado.\n");


        close(socketConexion);            // Cerramos el socket de conexion
    }

    close(socketEscucha);              // Cerramos el socket pasivo de servidor antes de finalizar

    return (EXIT_SUCCESS);
}
