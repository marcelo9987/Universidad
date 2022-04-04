//
// Created by progrii on 29/3/22.
//
#include <time.h>

#include <stdio.h>
#include "matrices.h"

void crearMatriz(matriz** matrizVacia, short f, short c)
{
    * matrizVacia = (matriz*) malloc(1 * sizeof(matriz));
    (* matrizVacia)->elems = (long*) malloc(f * c * sizeof(long));
    (* matrizVacia)->col = c;
    (* matrizVacia)->fil = f;
}

void asignarMatriz(matriz** Matriz)
{


    for (int i = 0; i < (* Matriz)->fil * (* Matriz)->col; i++)
    {
        * ((* Matriz)->elems + i) = rand()%5;
        //printf("Elem: %i: %li \n", i, * ((* Matriz)->elems + i));
    }
}

long GetElem(matriz* matriz1,short f,short c)
{
    return *(matriz1->elems+f*matriz1->fil+c);
}

matriz* sumaMatrices(matriz* A, matriz* B)
{
    if (A->col != B->col || A->fil != B->fil)
    {
        printf("A y B han de tener las mismas dimensiones");
        return NULL;
    } else
    {
        matriz* salida;
        crearMatriz(& salida, A->col, A->fil);
        for (int i = 0; i < A->fil * A->col;i++)
        {
            * ((salida)->elems + i) = * (A->elems + i) + * (B->elems + i);
        }
        return salida;
    }
}


matriz* multiplicaMatrices(matriz* A, matriz* B)
{
    if(A->fil!=B->col)
    {
        return 0;
    }else
    {

        matriz* salida;
        crearMatriz(&salida,A->fil,B->col);
        for(int i =0;i < A->fil;i++)
        {
            long pdto=0;
            for (int j = 0; j < B->col; ++j)
            {
               pdto += *(A->elems+i*A->fil+j) * *(B->elems+i*B->col);
            }
        }
    }
}
void destruirMatriz(matriz** Matriz)
{
    free((* Matriz)->elems);
    free(* Matriz);
}

/*** DEBUG***/
void ipmt(matriz* m)
{
    for(int fils =0;fils< m->fil;fils++)
    {
        for(int cols=0;cols < m->col;cols++)
        {
            fprintf(stdout, " %li", *(m->elems +fils*2+cols ));
        }
        printf("\n");

    }
}


