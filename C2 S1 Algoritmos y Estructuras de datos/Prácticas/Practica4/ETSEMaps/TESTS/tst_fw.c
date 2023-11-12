//
// Created by imarc on 31/10/2023.
//


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../grafo.h"
#include "../ETSEMaps.h"


int main(int argc, char *argv[])
{
    grafo G;
    crear_grafo(&G);
    FILE *archivoLectura;
    archivoLectura = fopen("../archivoArcos.data", "r");
    if (archivoLectura == NULL)
    {
        printf("Error al abrir el archivo EN EL MAIN\n");
        return -1;
    }
    leerArchivo(archivoLectura, &G);
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
    getc(stdin);

    borrar_grafo(&G);
    return (0);

}
