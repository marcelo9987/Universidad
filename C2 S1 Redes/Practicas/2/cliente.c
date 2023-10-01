//
// Created by usuario_base on 29/09/23.
//
#include <sys/socket.h>
#include <netinet/in.h>
#include <stdio.h>


int main()
{
    int i_numeroSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (i_numeroSocket == -1)
    {
        perror("Error al crear el socket");
        return 1;
    }

    struct sockaddr_in direccion;
    direccion.sin_family = AF_INET;
    direccion.sin_addr.s_addr = htonl(16777343);
    direccion.sin_port = htons(2023);

    struct sockaddr_in direccionServidor;

    inet_pton(AF_INET, "127.0.0.1", &direccionServidor.sin_addr);
    direccionServidor.sin_family = AF_INET;
    direccionServidor.sin_port = htons(2025);
    if(connect(i_numeroSocket, (struct sockaddr *) &direccionServidor, sizeof(struct sockaddr_in)) < 0)
    {
        perror("Error al conectar con el servidor");
        return 3;
    }

    char c_buffer[1000];
    int i_bytesRecibidos = recv(i_numeroSocket, c_buffer, 1000, 0);
    if (i_bytesRecibidos < 0)
    {
        perror("Error al recibir datos");
        return 4;
    }

    fprintf(stdout, "El servidor envio el mensaje: %s\n", c_buffer);

}
