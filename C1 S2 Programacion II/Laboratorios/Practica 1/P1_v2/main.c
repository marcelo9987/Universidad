#include <stdio.h>
#include <stdlib.h>
#include "vectordinamico.h"


int main(int argc, char **argv)
{
    vectorD vector;/*declaramos el vector*/
    short longitud, i;/*variables tamaño y recorrido*/
    TELEMENTO valor;/*valor a introducir en el vector*/
    char opcion;/*Variable del menu*/

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
        printf("\ns)Salir");
        printf("\n----------------\n");
        printf("\nOpcion: ");
        scanf(" %c", &opcion);//OJO: espacio antes de %c para vaciar el buffer de teclado
        switch (opcion)
        {
            case 'a': //Crear Vector
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

            case 's':
                printf("Saliendo del programa\n");
                break;

            default:
                printf("ERR, opcion incorrecta");
        }
    } while (opcion != 's');
    return (EXIT_SUCCESS);
}

/*
 * Registro de errores
 * Error 1: Fallo en asignación de vector
 * Error 2: Fallo en asignación de elementos
 */