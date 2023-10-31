#include <stdio.h>
#include <stdlib.h>
#include "ETSEMaps.h"
#include "grafo.h"

#if defined(DEBUG)
int main(int argc, char** argv)
{
    //voy a leer el archivo
    FILE *archivoLectura;
    grafo G;

    //abro el archivo
    archivoLectura = fopen("../archivoArcos.data", "r");
    if (archivoLectura == NULL)
    {
        printf("Error al abrir el archivo EN EL MAIN\n");
        return -1;
    }

    //llamo a la función que lee el archivo
    leerArchivo(archivoLectura, &G);

    //Al salir, liberamos la memoria del TAD, lo destruimos
    borrar_grafo(&G);

    return (EXIT_SUCCESS);
}

/*
 * Programa que muestra el uso del TAD grafo de números enteros
 */
#elif !defined(DEBUG)
int main(int argc, char** argv) {
    //Grafo de números enteros
    grafo G; //grafo

    //voy a leer el archivo
    FILE *archivoLectura;

    crear_grafo(&G);
    //abro el archivo
    archivoLectura = fopen("../archivoArcos.data", "r");
    if (archivoLectura == NULL)
    {
        printf("Error al abrir el archivo EN EL MAIN\n");
        return -1;
    }

    //llamo a la función que lee el archivo
    leerArchivo(archivoLectura, &G);

    char opcion;

    do {
        printf("\n\na. Insertar nuevo vertice\n");
        printf("b. Eliminar vertice\n");
        printf("c. Crear arco\n");
        printf("d. Eliminar arco\n");
        printf("i. Imprimir grafo\n");
        printf("j. Imprimir infraestructura mínima para la conexión de todas las ciudades\n");
        printf("s. Salir\n");

        printf("Opción: ");
        scanf(" %c", &opcion); 

        switch (opcion) {
            case 'a':case'A':
                introducir_vertice(&G);
                break;
            case 'b':case 'B':
                eliminar_vertice(&G);
                break;
            case 'c': case 'C':
                nuevo_arco(&G);
                break;
            case 'd': case 'D':
                eliminar_arco(&G);
                break;
            case 'i': case 'I':
                imprimir_grafo(G);
                break;
            case 'j': case 'J':
                prim(G);
                break;
            case 's': case 'S':
                opcion='s';
                break;
            default:
                printf("Opción equivocada\n");
        }
    } while (opcion != 's');

    //Al salir, liberamos la memoria del TAD, lo destruimos
    borrar_grafo(&G);

    return (EXIT_SUCCESS);
}
#endif

