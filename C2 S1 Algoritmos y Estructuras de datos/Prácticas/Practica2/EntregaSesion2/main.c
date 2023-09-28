#include "FuncionesExpresion.h"
#include "recorridos.h"
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv)
{
//    char expr_infija[100];
    char *expr_infija = NULL;

    if (argc > 1)
    {
        fprintf(stdout, "INFO: Se ha introducido la expresion infija como argumento del programa\n");
        fprintf(stdout, "INFO: La expresion infija introducida es: %s\n", argv[1]);
        expr_infija = argv[1];
    } else
    {
        expr_infija = (char *) malloc(sizeof(char) * 100);
        fprintf(stdout, "Introduzca la expresión infija:");
        fscanf(stdin, "%s", expr_infija);
    }

    abin arbolGenerado = arbolExpresion(expr_infija);

    fprintf(stdout, "Expresión en forma prefija: ");
    preorden(arbolGenerado);

    fprintf(stdout, "\nExpresión en forma postfija: ");
    postorden(arbolGenerado);
    fprintf(stdout, "\n");

    destruir(&arbolGenerado);

    if (argc == 1)
    {
        free(expr_infija);
    }

    return 0;
}
