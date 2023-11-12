//
// Created by imarc on 01/11/2023.
//
#include <stdlib.h>
#include <stdio.h>
#include "../ETSEMaps.h"

int main()
{
    grafo G;
    crear_grafo(&G);

    if(leerArchivo(NOMBRE_ARCHIVO_MAPA_NOROESTE, &G) == false)
    {
        printf("Error al leer el archivo\n");
        return -1;
    }

    system("clear");
    imprimir_grafo(G);
    borrar_grafo(&G);
    return 0;
}
