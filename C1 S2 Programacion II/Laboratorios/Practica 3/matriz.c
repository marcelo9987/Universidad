//
// Created by progrii on 29/3/22.
//
#define compilameDebug 0

#include <stdlib.h>
#include <limits.h>
#include <stdio.h>

#include "matriz.h"

void iniciarMatriz(Matriz* matrizVacia, long int f, long int c)
{
    if (f <= 0 || c <= 0)
    {
        fprintf(stderr, "Filas y/o columnas han de ser mayores que 0");
        return;
    }
    if (matrizVacia == NULL)
    {
        fprintf(stderr, "Se ha recibido un puntero a NULL \n");
        return;
    }
    
    matrizVacia->elems = (long*) malloc(f * c * sizeof(long));
    
    if (matrizVacia->elems == NULL)
    {
        perror("Error al reservar memoria");
    }
    
    matrizVacia->col = c;
    matrizVacia->fil = f;
    
    for (long fil = 0; fil < f; fil++)
    {
        for (long col = 0; col < c; col++)
        {
            setElem(matrizVacia,fil,col,0);
        }
    }
}

void asignarValoresAleatoriosMatriz(Matriz* matriz)
{
    if (matriz == NULL)
    {
        fprintf(stderr, "Se ha recibido un puntero a NULL \n");
        return;
    }
    
    for (long int f = 0; f < matriz->fil; f++)
    {
        for (long int c = 0; c < matriz->col; c++)
        {
            setElem(matriz, f, c, rand());
        }
    }
}

long getElem(Matriz* matriz, long int f, long int c)
{
    if (matriz == NULL)
    {
        fprintf(stderr, "Se ha recibido un puntero a NULL \n");
        return LONG_MIN;
    }
    
    if ((f < 0 || f > matriz->fil) || (c < 0 || c > matriz->col))
    {
        fprintf(stderr, "Ese elemento no existe\n");
        return LONG_MIN;
    }
    //return *(matriz.elems + f * matriz.fil + c);
    return matriz->elems[ f * matriz->col + c ];
}

void setElem(Matriz* matriz, long int f, long int c, long elem)
{
    matriz->elems[ f * matriz->fil + c ] = elem;
}

void sumaMatrices(Matriz* dest, Matriz* A, Matriz* B)
{
    if (dest == NULL || A == NULL || B == NULL)
    {
        fprintf(stderr, "Se ha recibido un puntero a NULL \n");
        return;
    }
    
    if (A->fil != B->fil || A->col != B->col || dest->fil != A->fil || dest->col != A->col)
    {
        fprintf(stderr, "dest, A y B han de tener las mismas dimensiones.\n");
        //exit(255);//
        return;
    }
    //Matriz SUMA;
    //iniciarMatriz(&SUMA, A->fil, A->col);
    
    /*for (long int i = 0; i < A->fil * A->col; i++)
    {
        *((salida).elems + i) = *(A->elems + i) + *(B->elems + i);
        dest->elems[ i ] =A->elems[ i ] + B->elems[ i ];
    } */
    for (long int f = 0; f < A->fil; f++)
    {
        for (long int c = 0; c < B->col; c++)
        {
            setElem(dest, f, c, getElem(A, f, c) + getElem(B, f, c));
        }
        //*((salida).elems + i) = *(A->elems + i) + *(B->elems + i);
        
    }
}

void multiplicaMatrices(Matriz* dest, Matriz* M1, Matriz* M2)
{
    
    if (dest == NULL || M1 == NULL || M2 == NULL)
    {
        fprintf(stderr, "Se ha recibido un puntero a NULL \n");
        return;
    }
    
    if (M1->col != M2->fil)
    {
        fprintf(stderr, "El número de columnas de la primera Matriz y de filas de la segunda Matriz deben ser iguales.\n");
        return;
    }
    
    if (dest->fil != M1->fil || dest->col != M2->col)
    {
        fprintf(stderr, "Matriz destino incompatible.\n");
        return;
    }
    
    //iniciarMatriz(&aux, M1->fil, M2->col);
    for (long f = 0; f < dest->fil; f++)
    {
        if (f % 10 == 0)
        {
            fprintf(stdout, ".");
            fflush(stdout);
        }
        for (long c = 0; c < dest->col; c++)
        {
            //*(dest->elems + f * M2->col + c) = 0;
            long elem = 0;
            dest->elems[ f * dest->col + c ] = 0;
            
            for (long l = 0; l < M1->col; l++)
            {
                //*(dest->elems + f * M2->col + c) += *(M1->elems + f * M1->col + l) * *(M2->elems + l * M2->col + c);
                /*dest->elems[ f * dest->col + c ]*/
                elem += getElem(M1, f, l)/*M1->elems[ f * M1->col + l ]*/ * getElem(M2, l, c);/*M2->elems[ l * M2->col + c ];*/
            }
            setElem(dest, f, c, elem);
        }
    }
    fprintf(stdout, "\n");
}

void destruirMatriz(Matriz* matriz)
{
    if (matriz == NULL)
    {
        fprintf(stderr, "Se ha recibido un puntero a NULL \n");
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

#warning comenta las 2 lineas de abajo para usar la función
#error ESTE CODIGO HA SIDO COMPILADO
    
    printf(stdout, "ESTA FUNCIÓN ES SOLAMENTE DE DEPURACIÓN");
    for (long int f = 0; f < m.fil; f++)
    {
        for (long int c = 0; c < m.col; c++)
        {
            fprintf(stdout, " %5li", m.elems[ f * m.col + c ]);
        }
        
        printf(" \n");
    }
    
    fprintf(stdout, "\n\n");
    
}

#endif

