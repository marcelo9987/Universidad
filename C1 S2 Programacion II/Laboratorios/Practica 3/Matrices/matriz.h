#ifndef PRACTICA_3_MATRIZ_H
#define PRACTICA_3_MATRIZ_H

#define compilameDebug 0

typedef struct
{
    long* elems;
    long int fil, col;
} Matriz;

void iniciarMatriz(Matriz* matrizVacia, long int numFilas, long int numColumnas);

void asignarValoresAleatoriosMatriz(Matriz* matriz);

long getElem(Matriz* matriz, long int f, long int c);

void setElem(Matriz* matriz, long int f, long int c, long elem);

void sumaMatrices(Matriz* dest, Matriz* A, Matriz* B);

void multiplicaMatrices(Matriz* dest, Matriz* A, Matriz* B);

void destruirMatriz(Matriz* matriz);

/*** DEBUG ***/
#if(compilameDebug)
void ipmt(Matriz m);
#endif

#endif //PRACTICA_3_MATRIZ_H
