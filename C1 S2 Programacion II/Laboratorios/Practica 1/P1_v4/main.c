#define FALSE 0
#define TRUE 1

#include <stdio.h>
#include "vectordinamico.h"
#include <stdbool.h>
#include <stdlib.h>

void imprimir(vectorD vector);


vectorD sumaEscalar(vectorD vector, TELEMENTO escalar);


int main(int argc, char** argv)
{
    vectorD vector = NULL;/*declaramos el vector*/
    vectorD vectSuma = NULL;
    short longitud, i;/*variables tamaño y recorrido*/
    TELEMENTO valor;/*valor a introducir en el vector*/
    char opcion;/*Variable del menu*/
    bool liberado = 1;
    
    
    if (argc > 1)
    {
        longitud = (short) (argc - 1);
        crear(&vector, longitud);
        
        for (int n = 0; n != longitud; n++)
        {
            asignar(&vector, (short)n, (TELEMENTO)atol(argv[ n + 1 ]));
            
        }
    }
    
    
    TELEMENTO escalar;
    
    do
    {
        printf("\n----------------\n");
        printf("\na)Crear vector v");
        printf("\nb)Liberar vector");
        printf("\nc)Imprimir vector");
        printf("\nd)Sumar vector a escalar");
        printf("\ns)Salir");
        printf("\n----------------\n");
        printf("\nOpcion: ");
        scanf(" %c", &opcion);//OJO: espacio antes de %c para vaciar el buffer de teclado
        switch (opcion)
        {
            case 'a': //Crear Vector
                if (liberado == FALSE)
                {
                    liberar(&vector);
                    
                }
                printf("Longitud del vector v: ");
                scanf("%hd", &longitud);
                crear(&vector, longitud);
                /*Asignar valores a v*/
                for (i = 0; i < longitud; i++)
                {
                    printf("vector(%i): ", i + 1);
                    scanf("%f", &valor);
                    asignar(&vector, i, valor);
                }
                liberado = FALSE;
                break;
            case 'b':
                liberar(&vector);
                liberado = TRUE;
                break;
            case 'c':
                imprimir(vector);
                break;
            case 'd':
                printf("\n Introduzca el escalar: ");
                scanf("%f", &escalar);
                vectSuma=sumaEscalar(vector, escalar);
                imprimir(vectSuma);
                liberar(&vectSuma);
                break;
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
    short longitud = (short) longitudVector(vector);
    printf("Los elementos del vector son: [");
    for (short i = 0; i < longitud; i++)
    {
        printf("%f ", recuperar(vector, i));
    }
    printf("]\n");
}

vectorD sumaEscalar(vectorD vector, TELEMENTO escalar)
{
    vectorD vctSalida=NULL;
    short longitud = (short) longitudVector(vector);
    float aux;
    crear(&vctSalida, longitud);
    for (short i = 0; i < longitud; i++)
    {
        aux = recuperar(vector, i) + escalar;
        asignar(&vctSalida, i, aux);
    }
    return vctSalida;
}

/*
 * Registro de errores
 * Error 1: Fallo en asignación de vector
 * Error 2: Fallo en asignación de elementos
 * Error 3: Fallo de liberación
 */