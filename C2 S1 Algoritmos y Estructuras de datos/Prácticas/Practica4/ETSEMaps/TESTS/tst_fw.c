//
// Created by imarc on 31/10/2023.
//


#include <stdio.h>
#include <stdlib.h>
#include "../grafo.h"
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
//    getc(stdin);

//    tipovertice origen;
////    strcpy(origen.nombre, "Santiago");
//    strcpy(origen.nombre, "Alicante");
//
//    tipovertice destino;
//    strcpy(destino.nombre, "Salamanca");


    floydWarshall(G,DISTANCIA);

//    floydWarshall(G, posicion(G,"Santiago"), posicion(G,"Barcelona"));
//    getc(stdin);

    borrar_grafo(&G);
    return (0);

}
