#include <stdlib.h>
#include <limits.h>
#include <stdio.h>

#include "matriz.h"

void iniciarMatriz(Matriz* matrizVacia, long int numFilas, long int numColumnas)
{
    if (matrizVacia == NULL)
    {
        fprintf(stderr, "Se ha recibido un puntero a NULL.\n");
        return;
    }
    
    if (numFilas <= 0 || numColumnas <= 0)
    {
        fprintf(stderr, "Filas y/o columnas han de ser mayores que 0");
        return;
    }
    
    matrizVacia->elems = (long*) malloc(numFilas * numColumnas * sizeof(long));
    
    if (matrizVacia->elems == NULL)
    {
        perror("Error al reservar memoria");
    }
    
    matrizVacia->fil = numFilas;
    matrizVacia->col = numColumnas;
    
    for (long fil = 0; fil < numFilas; fil++)
    {
        for (long col = 0; col < numColumnas; col++)
        {
            setElem(matrizVacia, fil, col, 0);
        }
    }
}

void asignarValoresAleatoriosMatriz(Matriz* matriz)
{
    if (matriz == NULL || matriz->elems == NULL)
    {
        fprintf(stderr, "Se ha recibido un puntero a NULL.\n");
        return;
    }
    
    for (long int fil = 0; fil < matriz->fil; fil++)
    {
        for (long int col = 0; col < matriz->col; col++)
        {
            setElem(matriz, fil, col, rand()%20-10);
        }
    }
}

long getElem(Matriz* matriz, long int f, long int c)
{
    if (matriz == NULL || matriz->elems == NULL)
    {
        fprintf(stderr, "Se ha recibido un puntero a NULL.\n");
        return LONG_MIN;
    }
    
    if ((f < 0 || f >= matriz->fil) || (c < 0 || c >= matriz->col))
    {
        fprintf(stderr, "Ese elemento no existe\n");
        return LONG_MIN;
    }
    //return *(matriz.elems + f * matriz.fil + c);
    return matriz->elems[ f * matriz->col + c ];
}

void setElem(Matriz* matriz, long int f, long int c, long elem)
{
    if (matriz == NULL || matriz->elems == NULL)
    {
        fprintf(stderr, "Se ha recibido un puntero a NULL.\n");
        return;
    }
    if ((f < 0 || f >= matriz->fil) || (c < 0 || c >= matriz->col))
    {
        fprintf(stderr, "Ese elemento no existe\n");
        return;
    }
    matriz->elems[ f * matriz->fil + c ] = elem;
}

void sumaMatrices(Matriz* dest, Matriz* A, Matriz* B)
{
    if ((dest == NULL || dest->elems == NULL)
        || (A == NULL || A->elems == NULL)
        || (B == NULL || B->elems == NULL))
    {
        fprintf(stderr, "Se ha recibido un puntero a NULL.\n");
        return;
    }
    
    if (A->fil != B->fil || A->col != B->col
        || dest->fil != A->fil || dest->col != A->col)
    {
        fprintf(stderr, "dest, A y B han de tener las mismas dimensiones.\n");
        return;
    }
    
    for (long int fil = 0; fil < A->fil; fil++)
    {
        for (long int col = 0; col < B->col; col++)
        {
            setElem(dest, fil, col, getElem(A, fil, col) + getElem(B, fil, col));
        }
    }
}

void multiplicaMatrices(Matriz* dest, Matriz* A, Matriz* B)
{
    
    if (dest == NULL || A == NULL || B == NULL)
    {
        fprintf(stderr, "Se ha recibido un puntero a NULL.\n");
        return;
    }
    
    if (A->col != B->fil)
    {
        fprintf(stderr, "El número de columnas de la primera Matriz y de filas de la segunda Matriz deben ser iguales.\n");
        return;
    }
    
    if (dest->fil != A->fil || dest->col != B->col)
    {
        fprintf(stderr, "Matriz destino incompatible.\n");
        return;
    }
    
    //iniciarMatriz(&aux, A->fil, B->col);
    for (long fil = 0; fil < dest->fil; fil++)
    {
        if (fil % 10 == 0)
        {
            fprintf(stdout, ".");
            fflush(stdout);
        }
        
        for (long col = 0; col < dest->col; col++)
        {
            long resultado = 0;
            
            for (long pos = 0; pos < A->col; pos++)
            {
                resultado += getElem(A, fil, pos) * getElem(B, pos, col);
            }
            setElem(dest, fil, col, resultado);
        }
    }
    
    fprintf(stdout, "\n");
}

void destruirMatriz(Matriz* matriz)
{
    if (matriz == NULL || matriz->elems == NULL)
    {
        fprintf(stderr, "Se ha recibido un puntero a NULL.\n");
        return;
    }
    
    free(matriz->elems);
    matriz->elems = NULL;
    matriz->fil = 0;
    matriz->col = 0;
}

/*** DEBUG***/
#if(compilameDebug)

void ipmt(Matriz m)
{

//#warning comenta las 2 lineas de abajo para usar la función
//#error ESTE CODIGO HA SIDO COMPILADO
    
    //printf(stdout, "ESTA FUNCIÓN ES SOLAMENTE DE DEPURACIÓN");
    for (long int fil = 0; fil < m.fil; fil++)
    {
        for (long int col = 0; col < m.col; col++)
        {
            fprintf(stdout, " %5li", m.elems[ fil * m.col + col ]);
        }
        
        printf("\n");
    }
    
    fprintf(stdout, "\n\n");
    
}

#endif
