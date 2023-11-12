//
// Created by imarc on 30/10/2023.
//

#include "../ETSEMaps.h"
//#include <math.h>
#include <stdlib.h>
#include <float.h>

#define resultadoEsperado 9.91

int main()
{
    grafo G;
    crear_grafo(&G);

    if (leerArchivo(NOMBRE_ARCHIVO_MAPA_NOROESTE, &G) == false)
    {
        printf("Error al leer el archivo\n");
        borrar_grafo(&G);
        return -1;
    }

    double resultado = prim(G);
    printf("Resultado: %lf esperado %lf distancia %lf epsilon %.50lf\n", resultado, resultadoEsperado, 1 - resultado / resultadoEsperado, DBL_EPSILON);
    borrar_grafo(&G);
    return (EXIT_SUCCESS);
}


