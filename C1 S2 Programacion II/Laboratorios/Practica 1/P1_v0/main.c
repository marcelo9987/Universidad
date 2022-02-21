#include <stdio.h>
#include "vectordinamico.h"

int main(int argc, char **argv)
{
    vectorD vector;/*declaramos el vector*/
    short longitud, i;/*variables tamaño y recorrido*/
    TELEMENTO valor;/*valor a introducir en el vector*/
    char opcion;/*Variable del menu*/
    char k;

    do
    {
        printf("\n----------------\n");
        printf("\na)Crear vector v")
        printf("\ns)Salir")
        printf("\n----------------\n");
        printf("\nOpcion: ");
        getc(&k);
        scanf(" %c",&opcion);//OJO

    } while (opcion != 's');
    return (0);
}
