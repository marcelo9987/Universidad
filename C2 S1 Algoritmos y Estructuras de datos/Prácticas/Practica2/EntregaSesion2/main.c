#include "FuncionesExpresion.h"
#include "recorridos.h"
#include <stdio.h>

int main()
{
    abin A = NULL;
    A = arbolExpresion("A+B+C/D");
    inorden(A);
    printf("\n");
    preorden(A);
    printf("\n");
    postorden(A);
    printf("\n");
    destruir(&A);
    return 0;
}
