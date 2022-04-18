//
// Created by progrii on 29/3/22.
//
#ifndef PRACTICA_3_MATRIZ_H
#define PRACTICA_3_MATRIZ_H

//#include <stdlib.h>

typedef struct
{
    long* elems;
    long int fil, col;
} Matriz;

void iniciarMatriz(Matriz* matrizVacia, long int f, long int c);

void asignarValoresAleatoriosMatriz(Matriz* matriz);

long getElem(Matriz* matriz, long int f, long int c);

void setElem(Matriz* matriz,long int f,long int c,long elem);

void sumaMatrices(Matriz* dest,Matriz* A, Matriz* B);

void multiplicaMatrices(Matriz* dest,Matriz* M1, Matriz* M2);

void destruirMatriz(Matriz* matriz);

/*** DEBUG ***/
void ipmt(Matriz m);

#endif //PRACTICA_3_MATRIZ_H
