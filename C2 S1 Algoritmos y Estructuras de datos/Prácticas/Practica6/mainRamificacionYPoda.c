//
// Created by imarc on 04/12/2023.
//

#include "ramificacionYpoda.h"
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>

int B[3][3] = {
        {4, 9, 1},
        {7, 2, 3},
        {6, 3, 5}
};

int main()
{
    int nNodos = 0;

    NODO solucion;

    for (int i = 0; i < N; i++)
    {
        solucion.tupla[i] = ASIGNACION_NO_VALIDA;
        solucion.usadas[i] = false;
    }

    solucion.nivel = -1;
    solucion.beneficioActual = 0;
    solucion.cotaInferior = 0;
    solucion.cotaSuperior = 0;
    solucion.beneficioEstimado = 0;


//  int solucion[N];


    AsignacionTrivial(B, &solucion, &nNodos);
    printf("Asignacion trivial: \n");
    for (int i = 0; i < N; i++)
    {
        printf("%d ", solucion.tupla[i]);
//        printf("%d ", solucion[i]);
    }

    return 0;
}

