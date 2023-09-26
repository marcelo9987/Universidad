#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "abin.h"
#include "pilaOperandos.h"
#include "pilaOperadores.h"

//Devuelve la prioridad del operador dentro de la pila.
//Prioridad('(')=0
int prioridadDentro(char op)
{
    int prior;
    switch (op)
    {
        case '^':
            prior = 3;
            break;
        case '*':
        case '/':
            prior = 2;
            break;
        case '+':
        case '-':
            prior = 1;
            break;
        case '(':
            prior = 0; //nunca va a entrar en la pila, provoca vaciado
            break;
    }
    return prior;
}

//Devuelve la prioridad del operador fuera de la pila.
//Prioridad('(')=4
int prioridadFuera(char op)
{
    int prior;
    switch (op)
    {
        case '^':
            prior = 3;
            break;
        case '*':
        case '/':
            prior = 2;
            break;
        case '+':
        case '-':
            prior = 1;
            break;
        case '(':
            prior = 4; //para que SIEMPRE entre en la pila
            break;
    }
    return prior;
}

//Devuelve 1 si c es un operador: +, -, /, *, ^, ()
unsigned esOperador(char c)
{
    unsigned ope;
    switch (c)
    {
        case '^':
        case '*':
        case '/':
        case '+':
        case '-':
        case '(':
            ope = 1;
            break;
        default:
            ope = 0;
    }
    return ope;
}

//Devuelve 1 si c es un operando: mayúsculas y minúsculas
//completar para caracteres 0 a 9
unsigned esOperando(char c)
{
    if ((c >= '0' && c <= '9') || (c >= 65 && c <= 90) || (c >= 97 && c <= 122))
    {
        return 1;
    } else
    {
        return 0;
    }
}

//Recibe una cadena de caracteres y devuelve el arbol de expresion
//DEBES ESCRIBIR ESTA FUNCIÓN
abin arbolExpresion(char *expr_infija)
{
    // Creo las pilas de operadores y operandos
    pilaOperadores pOperadores;
    pilaOperandos pOperandos;

    crearPilaOperadores(&pOperadores);
    crearPilaOperandos(&pOperandos);

    // Creo el arbol
    abin arbolSalida;
    crear(&arbolSalida);

    if (expr_infija == NULL || expr_infija[0] == '\0')
    {
        fprintf(stdout, "INFO: La expresion infija esta vacia, DEVOLVIENDO ARBOL VACIO\n");
        return arbolSalida;
    }

    // Recorro la expresion infija
    int i = 0;
    while (expr_infija[i] != '\0')
    {
        char caracterActual = expr_infija[i];

        if (esOperando(caracterActual))
        {
            // De ser un operando, creo un arbol con este mismo
            abin arbolOperandoAuxiliar = NULL;
            crear(&arbolOperandoAuxiliar);

            insizq(&arbolOperandoAuxiliar, caracterActual);

            // Ahora, lo meto en la pila de operandos
            pushOperandos(&pOperandos, arbolOperandoAuxiliar);

        }else if(esOperador(caracterActual))
        {
            // Mientras que la pila de operadores no este vacía y que la prioridad_fuera del operador sea <= que la prioridad_dentro tope pila:
            while(!esVaciaPilaOperadores(pOperadores) && prioridadFuera(caracterActual)<= prioridadDentro(topeOperadores(pOperadores)))
            {

                char caracterTemporal = topeOperadores(pOperadores);
                popOperadores(&pOperadores);

                abin arbolDesapilado = NULL;
                crear(&arbolDesapilado);

                insder(&arbolDesapilado, caracterTemporal);

                insArbolder(&arbolDesapilado, topeOperandos(pOperandos));
                popOperandos(&pOperandos);

                insArbolizq(&arbolDesapilado, topeOperandos(pOperandos));
                popOperandos(&pOperandos);

                pushOperandos(&pOperandos, arbolDesapilado);
            }
            // Meto el operador en la pila de operandos
            pushOperadores(&pOperadores, caracterActual);

        }else if(caracterActual==')')
        {
            // Mientras que el tope de la pila de operadores no sea '(':
            while(topeOperadores(pOperadores)!='(')
            {

                char caracterTemporal = topeOperadores(pOperadores);
                popOperadores(&pOperadores);

                abin arbolDesapilado = NULL;
                crear(&arbolDesapilado);
                insder(&arbolDesapilado, caracterTemporal);

                insArbolder(&arbolDesapilado, topeOperandos(pOperandos));
                popOperandos(&pOperandos);

                insArbolizq(&arbolDesapilado, topeOperandos(pOperandos));
                popOperandos(&pOperandos);

                pushOperandos(&pOperandos, arbolDesapilado);
            }
            // Desapilo el parentesis
            popOperadores(&pOperadores);
        }
        i++;
    }

    //Ahora que he terminado de recorrer la cadena, vacio la pila de operadoresç
    while(!esVaciaPilaOperadores(pOperadores))
    {

        char caracterTemporal = topeOperadores(pOperadores);
        popOperadores(&pOperadores);
        //
        abin arbolDesapilado = NULL;
        crear(&arbolDesapilado);
        insizq(&arbolDesapilado, caracterTemporal);

        insArbolder(&arbolDesapilado, topeOperandos(pOperandos));
        popOperandos(&pOperandos);

        insArbolizq(&arbolDesapilado, topeOperandos(pOperandos));
        popOperandos(&pOperandos);

        pushOperandos(&pOperandos, arbolDesapilado);
    }


    destruirPilaOperadores(&pOperadores);

    insArbolizq(&arbolSalida, topeOperandos(pOperandos));
    destruirPilaOperandos(&pOperandos);

    return arbolSalida;
}

