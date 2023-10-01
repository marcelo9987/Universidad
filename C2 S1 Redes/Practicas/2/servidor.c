#include <sys/socket.h>
#include <netinet/in.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        fprintf(stderr, "Uso: servidor <puerto>\n");
        return 1;
    }

    int i_numeroSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (i_numeroSocket < 0)
    {
        perror("Error al crear el socket");
        return 1;
    }

    struct sockaddr_in direccion;
    direccion.sin_family = AF_INET;
    direccion.sin_port = htons(atoi(argv[1]));
    direccion.sin_addr.s_addr = htonl(INADDR_ANY);

    if (bind(i_numeroSocket, (struct sockaddr *) &direccion, sizeof(struct sockaddr_in)) < 0)
    {
        perror("Error al asignar un nombre al socket");
        return 2;
    }

    if (listen(i_numeroSocket, 10) < 0)
    {
        perror("Error al poner a escuchar el socket");
        return 3;
    }

    struct sockaddr_in direccionClienteConectado;
    int tamanhoDireccionClienteConectado = sizeof(struct sockaddr_in);
    int i_identificadorClienteConectado = accept(i_numeroSocket, (struct sockaddr *) &direccionClienteConectado, &tamanhoDireccionClienteConectado);
    if (i_identificadorClienteConectado < 0)
    {
        perror("Error al aceptar la conexion");
        return 4;
    }

    fprintf(stdout, "Se conecto un cliente desde la IP: %d y el puerto: %d\n", direccionClienteConectado.sin_addr.s_addr, direccionClienteConectado.sin_port);

    if (send(i_identificadorClienteConectado, "Conexión aceptada\n",sizeof(char)*19, 0) < 0)
    {
        perror("Error al enviar datos");
        return 5;
    }



    if(close(i_numeroSocket) < 0)
    {
        perror("Error al cerrar el socket");
        return 6;
    }
    fprintf(stdout, "Se cerro la conexion con el cliente\n");
    return 0;
}