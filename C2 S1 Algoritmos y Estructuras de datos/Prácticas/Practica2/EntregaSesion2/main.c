#include "FuncionesExpresion.h"
#include "recorridos.h"
#include <stdio.h>

int main()
{
    char expr_infija[100];

    fprintf(stdout,"Introduzca la expresión infija:");
    fscanf(stdin,"%s",expr_infija);

    abin A = NULL;
    A = arbolExpresion(expr_infija);
    fprintf(stdout,"Expresión en forma prefija: ");
    preorden(A);

    fprintf(stdout,"\nExpresión en forma postfija: ");
    postorden(A);

    destruir(&A);
    return 0;
}
