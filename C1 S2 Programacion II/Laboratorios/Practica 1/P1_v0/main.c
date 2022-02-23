#define FALSE 0
#define TRUE 1
#include <stdio.h>
#include "vectordinamico.h"
#include <stdbool.h>

void imprimir(vectorD vector);
vectorD sumaEscalar(vectorD vector, TELEMENTO escalar);


int main(int argc, char **argv) {
    vectorD vector;/*declaramos el vector*/
    short longitud, i;/*variables tamaño y recorrido*/
    TELEMENTO valor;/*valor a introducir en el vector*/
    char opcion;/*Variable del menu*/
    bool liberado=1;
    char k;
    TELEMENTO escalar;

    void imprimir(vectorD vector);

    do {
        printf("\n----------------\n");
        printf("\na)Crear vector v");
        printf("\nb)Liberar vector");
        printf("\nc)Imprimir vector");
        printf("\ncd)Sumar vector a escalar");
        printf("\ns)Salir");
        printf("\n----------------\n");
        printf("\nOpcion: ");
        scanf(" %c", &opcion);//OJO: espacio antes de %c para vaciar el buffer de teclado
        switch (opcion) {
            case 'a': //Crear Vector
            if(liberado==FALSE)
            {
                liberarVector(vector);
            }
                printf("Longitud del vector v: ");
                scanf("%hd", &longitud);
                crear(&vector, longitud);
                /*Asignar valores a v*/
                for (i = 0; i < longitud; i++) {
                    printf("vector(%hd): ", i+1);
                    scanf("%f", &valor);
                    asignar(&vector, i, valor);
                }
                liberado=FALSE;
                break;
            case 'b':
                liberarVector(vector);
                liberado=TRUE;
                break;
            case 'c':
                imprimir(vector);
                break;
            case 'd':

                printf("\n Introduzca el escalar: ");
                scanf("%f",escalar);
                vector=sumaEscalar(vector,escalar);
                imprimir(vector);
            case 's':
                printf("Saliendo del programa");
                break;

            default:
                printf("ERR, opcion incorrecta");
        }
    } while (opcion != 's');
    return (0);
}

void imprimir(vectorD vector)
{
    short longitud = longitudVector(vector);
    printf("Los elementos del vector son: [");
    for(short i =0;i<longitud;i++)
    {
        printf("%f ", recuperar(vector,i));

    }
}

vectorD sumaEscalar(vectorD vector, TELEMENTO escalar)
{
    short longitud = longitudVector(vector);
    short aux;
    vectorD vectorSalida;
    crear(&vectorSalida,longitud);
    for(short i =0;i<longitud;i++)
    {
        aux=recuperar(vector,i)+escalar;
        asignar(vectorSalida,i,aux);
    }
    return vectorSalida;
}