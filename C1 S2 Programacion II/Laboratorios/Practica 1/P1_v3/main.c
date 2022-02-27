#include <stdio.h>
#include <stdlib.h>
#include "vectordinamico.h"

void imprimir(vectorD vector);

vectorD sumaEscalar(vectorD vector, TELEMENTO escalar);

int main(int argc, char **argv)
{
    vectorD vector = NULL;/*declaramos el vector*/
    vectorD vectSuma = NULL;
    short longitud, i;/*variables tamaño y recorrido*/
    TELEMENTO valor;/*valor a introducir en el vector*/
    char opcion;/*Variable del menu*/
    TELEMENTO escalar;

    if (argc > 1)
    {
        longitud = (short) (argc - 1);
        crear(&vector, longitud);

        for (i = 0; i < longitud; i++)
        {
            asignar(&vector, i, (TELEMENTO) atof(argv[i + 1]));
            //printf("Pos %i Val: %f \n", i, (TELEMENTO) atof(argv[i + 1]));
        }
    }


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
                if (vector != NULL)
                {
                    liberar(&vector);
                    printf("DEBUG (48) :: Liberado\n");
                }
                printf("Longitud del vector v: ");
                scanf("%hd", &longitud);
                crear(&vector, longitud);
                /*Asignar valores a v*/
                for (i = 0; i < longitud; i++)
                {
                    printf("vector(%hd): ", i);
                    scanf("%f", &valor);
                    asignar(&vector, i, valor);
                }
                break;
            case 'b':
                liberar(&vector);
                break;
            case 'c':

                printf("Los elementos del vector son ");
                imprimir(vector);
                printf("\n");
                break;
            case 'd':
                printf("\n Introduzca el escalar: ");
                scanf("%f", &escalar);
                vectSuma = sumaEscalar(vector, escalar);

                printf("Los elementos del vector son ");
                imprimir(vectSuma);
                printf("\n");

                liberar(&vectSuma);

                break;
            case 's':
                printf("Saliendo del programa\n");
                break;

            default:
                printf("ERR, opcion incorrecta\n");
        }
    } while (opcion != 's');
    if (vector != NULL)
    {
        liberar(&vector);
        printf("DEBUG (93) :: Liberado\n");
    }
    return (EXIT_SUCCESS);
}


void imprimir(vectorD vector)
{
    short longitud = longitudVector(vector);
    printf("[");
    for (short i = 0; i < longitud; i++)
    {
        printf("%f ", recuperar(vector, i));
    }
    printf("]");
}

vectorD sumaEscalar(vectorD vector, TELEMENTO escalar)
{
    vectorD vctSalida = NULL;
    if (vector != NULL)
    {
        short longitud = longitudVector(vector);
        TELEMENTO aux;

        crear(&vctSalida, longitud);
        for (short i = 0; i < longitud; i++)
        {
            aux = recuperar(vector, i) + escalar;
            asignar(&vctSalida, i, aux);
        }
    }
    return vctSalida;
}


/*
 * Registro de errores
 * Error 1: Fallo en asignación de vector
 * Error 2: Fallo en asignación de elementos
 */