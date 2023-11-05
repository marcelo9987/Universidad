//
// Created by imarc on 30/10/2023.
//

#include "../ETSEMaps.h"
#include <math.h>

#define resultadoEsperado 9.91

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
    double resultado = prim(G);
    printf("Resultado: %lf esperado %lf distancia %lf epsilon %.50lf\n", resultado, resultadoEsperado, 1 - resultado / resultadoEsperado, DBL_EPSILON);
    borrar_grafo(&G);
    return(EXIT_SUCCESS);
}


