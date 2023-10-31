//
// Created by imarc on 30/10/2023.
//

#include "prim.c"
#include <assert.h>


int main(int argc, char** argv) {
    grafo G;
    crear_grafo(&G);
    FILE *archivoLectura;
    archivoLectura = fopen("../archivoArcos.data", "r");
    if (archivoLectura == NULL) {
        printf("Error al abrir el archivo EN EL MAIN\n");
        return -1;
    }
    leerArchivo(archivoLectura, &G);
    int resultado = prim(G);
    assert(resultado==0);
    return (EXIT_SUCCESS);
}


