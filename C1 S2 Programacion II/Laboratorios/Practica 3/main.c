#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "matrices.h"

int main()
{
    clock_t inicio[2];
    clock_t fin[2];
    srand(time(0));
    for(long tamanho = 100;tamanho<100000;tamanho+=100)
    {
       
       
       matriz m1;
       matriz m2;
        crearMatriz(&m1,tamanho,tamanho);
        crearMatriz(&m2,tamanho,tamanho);
        inicio[0]=clock();
        matriz m3 =sumaMatrices(m1,m2);
        fin[0] = clock();
        inicio[1]=clock();
        matriz m4 = multiplicaMatrices(m1,m2);
        fin[1] = clock();
        destruirMatriz(&m1);
        destruirMatriz(&m2);
        destruirMatriz(&m3);
        destruirMatriz(&m4);
        fprintf(stdout,"Tiempo de suma: %i",fin[0]-inicio[0]);
        fprintf(stdout,"  Tiempo de multiplicacion: %i\n",fin[1]-inicio[1]);
        
    }
    printf("fin");
    return 0;
}