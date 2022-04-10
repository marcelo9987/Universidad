#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "matrices.h"

int main()
{
    clock_t inicio[] ={0,0};
    clock_t fin[] = {0,0};
    srand(time(0));
    for(long tamanho = 1000;tamanho<100000;tamanho+=1000)
    {
       
       
       matriz m1;
       matriz m2;
        crearMatriz(&m1,tamanho,tamanho);
        crearMatriz(&m2,tamanho,tamanho);
        inicio[0]=clock();
        matriz m3 =sumaMatrices(m1,m2);
        fprintf(stdout,"He sumado");
        fin[0] = clock();
        inicio[1]=clock();
        matriz m4 = multiplicaMatrices(m1,m2);
        fprintf(stdout,"He multiplicado");
        fin[1] = clock();
        destruirMatriz(&m1);
        destruirMatriz(&m2);
        destruirMatriz(&m3);
        destruirMatriz(&m4);
        fprintf(stdout,"Tiempo de suma: %i\n",(int) ((fin[0]-inicio[0])/CLOCKS_PER_SEC));
        fprintf(stdout,"Tiempo de multiplicación: %i\n\n",(int) ((fin[1]-inicio[1])/CLOCKS_PER_SEC));
        
    }
    fprintf(stdout,"fin");
    return 0;
}
//Conclusiones a 08/04/2022: La suma es mas rapida; la división es carísima a nivel computacional: ¿ mejorar algoitmo ?
