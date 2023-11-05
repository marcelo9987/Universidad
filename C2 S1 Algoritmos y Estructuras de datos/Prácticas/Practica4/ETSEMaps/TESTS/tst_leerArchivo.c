//
// Created by imarc on 01/11/2023.
//
#include <stdlib.h>
#include "../ETSEMaps.h"

int main(int argc, char* argv[])
{
    grafo G;
    crear_grafo(&G);
    FILE *archivoLectura;
    archivoLectura = fopen("../archivoArcos.data", "r");
    if (archivoLectura == NULL) {
        printf("Error al abrir el archivo EN EL MAIN\n");
        return -1;
    }
    leerArchivo(archivoLectura, &G);
    system("clear");
    imprimir_grafo(G);
    getc(stdin);

    return 0;
}
