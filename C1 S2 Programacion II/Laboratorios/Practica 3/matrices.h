//
// Created by progrii on 29/3/22.
//
#ifndef PRACTICA_3_MATRICES_H
#define PRACTICA_3_MATRICES_H

#include <stdlib.h>

typedef struct
{
    long* elems;
    long int fil, col;
} matriz;

void crearMatriz(matriz** matrizVacia, long int f, long int c);

void asignarMatriz(matriz** Matriz);

long GetElem(matriz*, long int, long int);

matriz* sumaMatrices(matriz* A, matriz* B);

matriz* multiplicaMatrices(matriz* A, matriz* B);
float obtenerElemento(long int fila, long int columna, matriz *M);
void destruirMatriz(matriz** Matriz);

/*** DEBUG ***/
void ipmt(matriz* m);

#endif //PRACTICA_3_MATRICES_H
