#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "matrices.h"

int main()
{
    srand(time(0));
    long int fils = (rand() % 10)+5;
    long int cols = (rand() % 10)+5;
    long long int aux = rand() % 100000;
    long long int n = aux;
    matriz* matrVctor[n];
    for (long long int indice = 0; indice < n; indice++)
    {
        crearMatriz(&matrVctor[indice] , fils, cols);
    }
    for (long long int indice = 0; indice < n; indice++)
    {
        asignarMatriz(&matrVctor[indice]);
    }
    for (long long int indice = 0; indice < n; indice++)
    {
        ipmt(matrVctor[indice]);
        printf("He pasado:: vuelta: %li \n",indice);
    }
    for (long long int indice = 0; indice < n; indice++)
    {
        destruirMatriz(&matrVctor[n]);
    }
    printf("fin");
    return 0;
}