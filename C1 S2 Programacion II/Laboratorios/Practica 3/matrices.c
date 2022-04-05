//
// Created by progrii on 29/3/22.
//
#include <time.h>
#include <math.h>
#include <stdio.h>
#include "matrices.h"

void crearMatriz(matriz* matrizVacia, long int f, long int c)
{
    
    matrizVacia->elems = (long*) malloc(f * c * sizeof(long));
    for(long i =0;i<f*c;i++)
    {
        *((matrizVacia)->elems+i) = 0;
    }
    matrizVacia->col = c;
    matrizVacia->fil = f;
}

void asignarMatriz(matriz* Matriz)
{
    
    
    for (long int i = 0; i < (Matriz)->fil * (Matriz)->col; i++)
    {
        *((Matriz)->elems + i) = rand() % 50;
        //printf("Elem: %i: %li \n", i, * ((* Matriz)->elems + i));
    }
}

long GetElem(matriz matriz1, long int f, long int c)
{
    return *(matriz1.elems + f * matriz1.fil + c);
}

matriz sumaMatrices(matriz A, matriz B)
{
    if (A.col != B.col || A.fil != B.fil)
    {
        printf("A y B han de tener las mismas dimensiones.\n");
        fprintf(stderr,"Error. ^");
    } else
    {
        matriz salida;
        crearMatriz(&salida, A.col, A.fil);
        for (long int i = 0; i < A.fil * A.col; i++)
        {
            *((salida).elems + i) = *(A.elems + i) + *(B.elems + i);
        }
        return salida;
    }
}


matriz multiplicaMatrices(matriz M1, matriz M2)
{
    matriz aux;
    long int i, k, l;
 
        if (M1.fil != M2.col)
        {
            printf("El número de columnas de la primera matriz y de filas de la segunda deben ser iguales\n");
            return aux;
        }
        
        crearMatriz(&aux, M1.fil, M2.col);
        for (i = 0; i < M1.fil; i++)
            for (k = 0; k < M2.col; k++)
            {
                *(aux.elems + i * M2.col + k) = 0;
                for (l = 0; l < M1.col; l++)
                {
                    *(aux.elems + i * M2.col + k) += *(M1.elems + i * M1.col + l) * *(M2.elems + l * M2.col + k);
                }
            }
        
        return aux;
        
    
}

void destruirMatriz(matriz* Matriz)
{
    if (Matriz != 0)
    {
        free((*Matriz).elems);
    } else
    {
        printf("La matriz esta vacía. Nada que eliminar.\n");
    }
}


float obtenerElemento(long int fila,long int columna, matriz *M) {
    float x;
    
    if (M != 0) {
        if ((fila < 0 || fila > M->fil) || (columna < 0 || columna > M->col)) {
            printf("Ese elemento no existe\n");
            return 0;
        }
        x = *((M->elems) + fila * M->col + columna);
        return x;
    } else
        printf("La matriz no existe\n");
    return NAN;
}

/*** DEBUG***/
void ipmt(matriz m)
{
    if (&m != NULL)
    {
        for ( long int fils = 0; fils < (m).fil; fils++)
        {
            for ( long int cols = 0; cols < (m).col; cols++)
            {
                fprintf(stdout," ||%li", *(m.elems + fils * 2 + cols));
            }
            
            
        }
        printf("\n");
    }else
    {
        printf("M es nula\n");
        return;
    }
    fprintf(stdout,"\n");
}

