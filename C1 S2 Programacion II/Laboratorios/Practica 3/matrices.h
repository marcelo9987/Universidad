//
// Created by progrii on 29/3/22.
//
#ifndef PRACTICA_3_MATRICES_H
#define PRACTICA_3_MATRICES_H

#include <stdlib.h>

typedef struct
{
    long* elems;
    short fil, col;
} matriz;

void crearMatriz(matriz** matrizVacia, short f, short c);

void asignarMatriz(matriz** Matriz);

long GetElem(matriz*, short, short);

matriz* sumaMatrices(matriz* A, matriz* B);

matriz* multiplicaMatrices(matriz* A, matriz* B);

void destruirMatriz(matriz** Matriz);

/*** DEBUG ***/
void ipmt(matriz* m);

#endif //PRACTICA_3_MATRICES_H
