#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include "ETSEMaps.h"
#include "grafo.h"



int main()
{
    //Grafo de números enteros
    grafo G; //grafo
    crear_grafo(&G);


    char opcion = '\0';

    do
    {
        printf("\n\n====================== MENÚ ======================\n\n");


        printf("\n\nGestión archivos:\n");
        printf("m. Cargar desde archivo el mapa del noroeste de la peninsula (especificado en el enunciado)\n");
        printf("l. Cargar otro mapa desde archivo\n");
        printf("g. Guardar mapa en archivo\n");

        printf("\n\nGestión grafo:\n");
        printf("1. Insertar nuevo vértice\n");
        printf("2. Eliminar vértice\n");
        printf("3. Crear arco\n");
        printf("4. Eliminar arco\n");
        printf("5. Imprimir grafo\n");
        printf("6. Borrar grafo (crea nuevo grafo)\n");

        printf("\n\nAlgoritmos:\n");
        printf("c. Imprimir la ruta más corta entre dos ciudades\n");
        printf("t. Imprimir la ruta de menor tiempo entre dos ciudades\n");
        printf("e. Imprimir la ruta más económica entre dos ciudades\n");
        printf("i. Imprimir infraestructura mínima para la conexión de todas las ciudades\n");


        printf("\n\nOtros:\n");
        printf("s. Salir\n\n");

        printf("Opción: ");
        scanf(" %c", &opcion);
        while (getchar() != '\n');

        printf("\n\n============================================\n\n");

        switch (tolower(opcion))
        {
            case 'm':
                //llamo a la función que lee el archivo
                leerArchivo(NOMBRE_ARCHIVO_MAPA_NOROESTE, &G);
                break;
            case 'l':
            {
                //llamo a la función que lee el archivo
                printf("Introduce el nombre del archivo: ");
                char nombreArchivo[1024];
                scanf("%1023[^\n]s", nombreArchivo);

                leerArchivo(nombreArchivo, &G);
            }
                break;
            case 'g':
            {
                //llamo a la función que guarda el archivo
                printf("Introduce el nombre del archivo: ");
                char nombreArchivo[1024];
                scanf("%1023[^\n]s", nombreArchivo);

                guardarArchivo(nombreArchivo, G);
            }
                break;


            case '1':
                introducir_vertice(&G);
                break;
            case '2':
                eliminar_vertice(&G);
                break;
            case '3':
                nuevo_arco(&G);
                break;
            case '4':
                eliminar_arco(&G);
                break;
            case '5':
                imprimir_grafo(G);
                break;
            case '6':
                borrar_grafo(&G);
                crear_grafo(&G);
                break;


            case 'c':
                floydWarshall(G, DISTANCIA);
                break;
            case 't':
                floydWarshall(G, TIEMPO);
                break;
            case 'e':
                floydWarshall(G, DINERO);
                break;
            case 'i':
                prim(G);
                break;


            case 's':
                break;
            default:
                printf("Opción equivocada\n");
        }

    } while (tolower(opcion) != 's');

    //Al salir, liberamos la memoria del TAD, lo destruimos
    borrar_grafo(&G);

    return (EXIT_SUCCESS);
}
