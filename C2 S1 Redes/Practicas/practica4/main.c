#include <stdio.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <string.h>

#define tamanho_linea 25

void imprimir_ayuda(char *nombreArchivo)
{
    printf("Uso:\n");
    printf("%s <archivoTablas> <IP>\n",nombreArchivo);
    printf("Opción\t\t\tsignificado\n");
    printf("archivoTablas\t\tArchivo en el que se guardan las tablas con las direcciones ip, máscaras e interfaces\n");
    printf("IP\t\t\tIP que será redireccionada\n");
}

int main(int argc, char *argv[])
{
    FILE *fp;

    struct in_addr mired, miredSolucion;
    mired.s_addr = 0;

    struct in_addr miip;
    int sufijo, sufijoFinal=0;

    char linea [tamanho_linea];
    char *direccionTabla, *interfaz;
    char ip[INET_ADDRSTRLEN];

    char red_text [INET_ADDRSTRLEN+3];
    char interfazFinal[INET_ADDRSTRLEN];
    char direccionFinal[INET_ADDRSTRLEN];

    char direccionDefecto[INET_ADDRSTRLEN];
    int sufijoDefecto;

    int flag = 0; //Bandera para ver si coincide con alguna dirección.

    /* Argumentos de programa:
     * Nome do arquivo que contén a tabla de reenvío (.txt)
     * IP */

    if (argc != 3)
    {
        printf("Número de parámetros introducidos erróneo.\n");
        imprimir_ayuda(argv[0]);
        exit(EXIT_FAILURE);
    }


    fp = fopen(argv[1],"rt");
    if (fp == NULL)
    {
        perror("Error al abrir el archivo:");
        exit(EXIT_FAILURE);
    }

    strcpy(ip, argv[2]); // Copiamos
    printf("IP proporcionada: %s\n", ip);

    if (inet_pton(AF_INET, ip, (void *) &miip) != 1)
        { //pasamos la ip a binario
            fprintf(stderr, "Formato de direccion incorrecto.\n");
            fclose(fp);
            exit(EXIT_FAILURE);
       }

    while( fgets(linea,tamanho_linea,fp) != NULL )
    {
        direccionTabla = strtok(linea, ","); // Dirección de la tabla hasta el delimitador
        interfaz = strtok(NULL, ","); // Interfaz

        mired.s_addr = 0;
        if ((sufijo = inet_net_pton(AF_INET, direccionTabla, (void *) &mired, sizeof(struct in_addr))) < 0)
        {
            fprintf(stderr, "Formato de direccion incorrecto.\n");
            fclose(fp);
            exit(EXIT_FAILURE);
        }

        if(atoi(interfaz)==0)
        { //Ver si la interfaz es la de por defecto
            strcpy(direccionDefecto, direccionTabla);
            sufijoDefecto=sufijo;
        }

        //pasamos la ip con el sufijo de la red a texto
        if(inet_net_ntop (AF_INET , (void *) &miip , sufijo , red_text , INET_ADDRSTRLEN+3) == NULL)
        {
            printf("Formato de direccion incorrecto.\n");
            fclose(fp);
            exit(EXIT_FAILURE);
        }

        miredSolucion.s_addr = 0;
        //pasamos de texto a binario para ver si es igual a la direccion de la tabla
        if ((inet_net_pton(AF_INET, red_text, (void *) &miredSolucion, sizeof(struct in_addr))) < 0)
        {
            fprintf(stderr, "Formato de direccion incorrecto.\n");
            fclose(fp);
            exit(EXIT_FAILURE);
        }

        //Comprobamos para tomar el prefijo más largo
        if( (mired.s_addr == miredSolucion.s_addr) & (sufijo>sufijoFinal) ) //si mired y miredSolucion son iguales, y sufijo es mayor
        {
            sufijoFinal=sufijo;
            strcpy(interfazFinal, interfaz);
            strcpy(direccionFinal, direccionTabla);
            flag=1; //si coincide actualizamos bandera
        }
    }

    fclose(fp);

    if(flag)
    {
        printf("Direccion de la tabla que coincide con la direccion base: %s\n", direccionFinal);
        printf("Numero de bits del prefijo correspondiente a la interfaz: %d\n", sufijoFinal);
        printf("Interfaz de salida: %s\n", interfazFinal);
        return 0;
    }

    printf("Direccion de la tabla que coincide con la direccion base: %s\n", direccionDefecto);
    printf("Numero de bits del prefijo correspondiente a la interfaz: %d\n", sufijoDefecto);
    printf("Interfaz de salida: 0\n"); //interfaz por defecto

    return 0;
}
