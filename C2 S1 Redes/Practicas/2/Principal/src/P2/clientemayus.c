#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>
#include <ctype.h>

#define K_MAX_TAMANHO_LINEA 1000

int main(int argc, char *argv[])
{
    if (argc != 4 && argc != 5)
    {
        printf("Es necesario introducir el nombre del archivo, la dirección IP y el número de puerto por línea de comandos.\n");
        printf("Uso: .\\%s ARCHIVO IP PUERTO [opcional SEGUNDOS]\n", argv[0]);
        printf("\t SEGUNDOS: Tiempo de espera entre el envío de cada línea (para poder hacer el punto 3).\n");

        // Ponemos un código de error en el caso de que el usuario no introduzca el número de parámetros esperados
        exit(EXIT_FAILURE);
    }

    // --

    // Pasamos el puerto de un string a un unsigned int de 16 bits
    // Como el puerto es de 16b y el strtol devuelve un long, comprobamos si el valor es aceptable para un posible uso en sockets.
    long _numPuertoServidor = strtol(argv[3], NULL, 10);
    if (_numPuertoServidor <= 0 || _numPuertoServidor > 65535)
    {
        printf("Error: El puerto debe ser un número entre 1 y 65535\n");
        exit(EXIT_FAILURE);
    }

    u_int16_t numPuertoServidor = (u_int16_t) _numPuertoServidor;

    // --

    long segundosEspera = 0;
    if (argc == 5)
    {
        segundosEspera = strtol(argv[4], NULL, 10);
        if (segundosEspera > 0)
        {
            printf("\nAviso: Se esperarán %ld segundos entre el envío de cada línea.\n\n", segundosEspera);
        }
    }

    // --

    char *nombre_archivo = argv[1];

    // Abrimos el archivo y ponemos un código de error en caso de que no se abra correctamente
    FILE *fEntrada = fopen(nombre_archivo, "r");

    if (fEntrada == NULL)
    {
        perror("Error abriendo el archivo de entrada");
        exit(EXIT_FAILURE);
    }

    // --

    // Pasamos el nombre del archivo a mayúsculas
    char *nombreArchivoMayus = malloc((strlen(nombre_archivo) + 1) * sizeof(char));
    if (nombreArchivoMayus == NULL)
    {
        perror("Error en la función malloc");
        fclose(fEntrada);
        exit(EXIT_FAILURE);
    }

    int pos;
    for (pos = 0; nombre_archivo[pos] != '\0'; pos++)
    {
        nombreArchivoMayus[pos] = toupper(nombre_archivo[pos]);
    }

    // Añadimos un '\0' ya que las cadenas en C tienen que terminar en '\0'
    nombreArchivoMayus[pos] = '\0';

    // --

    // Abrimos el archivo con el nombre en maýusculas en modo escritura y ponemos un código de error en caso de que no se abra correctamente
    FILE *fSalida = fopen(nombreArchivoMayus, "w");
    if (fSalida == NULL)
    {
        perror("Error abriendo el archivo de fSalida");
        fclose(fEntrada);
        free(nombreArchivoMayus);
        exit(EXIT_FAILURE);
    }

    free(nombreArchivoMayus);
    nombreArchivoMayus = NULL;

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
    char *dir_ip = argv[2];

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

    char lineaOriginal[K_MAX_TAMANHO_LINEA];
    char lineaRecibida[K_MAX_TAMANHO_LINEA];

    // Con el while recorremos el archivo línea a línea
    while (fgets(lineaOriginal, K_MAX_TAMANHO_LINEA, fEntrada) != NULL) {
        size_t lenLineaOriginal = (strlen(lineaOriginal) + 1) * sizeof(char); // 1 carácter adicional para el '\0'

        // Mandamos una línea al servidor
        if (send(socketConexion, lineaOriginal, lenLineaOriginal, 0) < 0) {
            perror("Error en la función send");
            exit(EXIT_FAILURE);
        }

        //Imprimimos la línea original y el número de carácteres que contiene
        fprintf(stdout, "Linea enviada:  <%s> (%ld caracteres)\n", lineaOriginal, lenLineaOriginal);

        // --

        // Con recv recuperamos la línea ya pasada a mayúsculas
        if (recv(socketConexion, lineaRecibida, K_MAX_TAMANHO_LINEA, 0) < 0) {
            perror("Error en la función recv");
            exit(EXIT_FAILURE);
        }

        size_t lenLineaRecibida = strlen(lineaRecibida);

        //Imprimimos la línea recibida y el número de carácteres que contiene
        fprintf(stdout, "Linea RECIBIDA: <%s> (%ld caracteres)\n\n", lineaRecibida, lenLineaRecibida);

        //Escribimos la línea en el fichero de salida
        fputs(lineaRecibida, fSalida);

        // --

        if (segundosEspera > 0) {
            printf("\nDuermo %ld segundos\n", segundosEspera);
            sleep(segundosEspera);
            printf("Despierto\n\n");
        }

    }
    // --

    // Mandamos un último mensaje al servidor para que sepa que hemos finalizado.
    if (send(socketConexion, "", 1 * sizeof(char), 0) < 0)   //Una cadena vacía ocupa 1 carácter, por su '\0'
    {
        perror("Error en la función send");
        exit(EXIT_FAILURE);
    }

    // --

    // Cerramos el archivo del cual hemos leído el texto
    if (fclose(fEntrada) == EOF)
    {
        perror("Error en la función fclose para el archivo de entrada");
        exit(EXIT_FAILURE);
    }


    // Cerramos el archivo en donde hemos escrito el resultado
    if (fclose(fSalida) == EOF)
    {
        perror("Error en la función fclose para el archivo de salida");
        exit(EXIT_FAILURE);
    }

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
