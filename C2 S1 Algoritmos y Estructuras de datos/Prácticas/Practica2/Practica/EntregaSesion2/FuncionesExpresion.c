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
    if ((c >= 48 && c <= 57) || (c >= 65 && c <= 90) || (c >= 97 && c <= 122))
    {
        return 1;
    } else
    {
        return 0;
    }
}

//Recibe una cadena de caracteres y devuelve el árbol de expresión
//DEBES ESCRIBIR ESTA FUNCIÓN
/**
 * @brief Función que recibe una expresión infija y devuelve un árbol de expresión
 * @param expr_infija Cadena de caracteres que contiene la expresión infija
 * @return Árbol de expresión generado a partir de la expresión infija
 */
abin arbolExpresion(char *expr_infija)
{
    // Creo las pilas de operadores y operandos
    pilaOperadores pOperadores;
    pilaOperandos pOperandos;

    // Las inicializo
    crearPilaOperadores(&pOperadores);
    crearPilaOperandos(&pOperandos);

    // Creo el árbol
    abin arbolSalida;

    // Si la expresión infija es NULL o está vacía, devuelvo un árbol vacío
    if (expr_infija == NULL || expr_infija[0] == '\0')
    {
        fprintf(stdout, "INFO: La expresion infija esta vacia, DEVOLVIENDO ARBOL VACIO\n");
        crear(&arbolSalida);
        return arbolSalida;
    }

    // Recorro la expresión infija
    int i = 0;
    while (expr_infija[i] != '\0')
    {
        char caracterActual = expr_infija[i];

        // SI c es un operando
        if (esOperando(caracterActual))
        {
            // creo un árbol aux
            // introduzco c como información (insertando a izquierda o derecha, da igual puesto que será la raíz de ese árbol)
            // y meto dicho árbol aux en pilaOperandos

            // De ser un operando, creo un árbol con este mismo
            abin arbolOperandoAuxiliar;
            crear(&arbolOperandoAuxiliar);

            insizq(&arbolOperandoAuxiliar, caracterActual);

            // Ahora, lo meto en la pila de operandos
            pushOperandos(&pOperandos, arbolOperandoAuxiliar);

        } else if (esOperador(caracterActual)) // SINOSI c es un operador
        {
            // Mientras que la pila de operadores no esté vacía y que la prioridad_fuera del operador sea <= que la prioridad_dentro tope pila:
            while (!esVaciaPilaOperadores(pOperadores) && prioridadFuera(caracterActual) <= prioridadDentro(topeOperadores(pOperadores)))
            {
                // Desapilo tope de pilaOperadores y lo guardo en caux
                char caracterTemporal = topeOperadores(pOperadores);
                popOperadores(&pOperadores);

                //Creo un árbol aux, introduzco caux como información (insertando a izquierda o derecha, puesto que será la raíz del árbol aux)
                abin subArbol;
                crear(&subArbol);

                insder(&subArbol, caracterTemporal);

                // e inserto a la derecha (con la nueva función insArbolder() el tope de pilaOperandos, desapilándolo.
                insArbolder(&subArbol, topeOperandos(pOperandos));
                popOperandos(&pOperandos);

                // Inserto a la izquierda (con la nueva función insArbolizq() el tope de pilaOperandos, desapilándolo.
                insArbolizq(&subArbol, topeOperandos(pOperandos));
                popOperandos(&pOperandos);

                // Inserto el árbol aux en pilaOperandos
                pushOperandos(&pOperandos, subArbol);
            }

            // Apilo el operador en la pila de operandores
            pushOperadores(&pOperadores, caracterActual);

        } else if (caracterActual == ')') //SINOSI c es el paréntesis derecho )
        {
            // Mientras que el tope de la pila de operadores no sea '(':
            while (topeOperadores(pOperadores) != '(')
            {

                // Desapilo tope de pilaOperadores y lo guardo en caux
                char caracterTemporal = topeOperadores(pOperadores);
                popOperadores(&pOperadores);

                // Creo un árbol aux, introduzco caux como información (insertando a izquierda o derecha, puesto que será la raíz del árbol aux)
                abin subArbol;
                crear(&subArbol);
                insder(&subArbol, caracterTemporal);

                // e inserto a la derecha (con la nueva función insArbolder() el tope de pilaOperandos, desapilándolo.
                insArbolder(&subArbol, topeOperandos(pOperandos));
                popOperandos(&pOperandos);

                // Inserto a la izquierda (con la nueva función insArbolizq() el tope de pilaOperandos, desapilándolo.
                insArbolizq(&subArbol, topeOperandos(pOperandos));
                popOperandos(&pOperandos);

                // Inserto el árbol aux en pilaOperandos
                pushOperandos(&pOperandos, subArbol);
            }

            // Desapilo paréntesis izquierdo (
            popOperadores(&pOperadores);
        }
        i++;
    }

    // Ahora que he terminado de recorrer la cadena, vacío la pila de operadores
    while (!esVaciaPilaOperadores(pOperadores))
    {
        // Desapilo tope de pilaOperadores y lo guardo en caux
        char caracterTemporal = topeOperadores(pOperadores);
        popOperadores(&pOperadores);

        // Creo un árbol aux, introduzco caux como información (insertando a izquierda o derecha, puesto que será la raíz del árbol aux)
        abin subArbol;
        crear(&subArbol);
        insizq(&subArbol, caracterTemporal);

        // e inserto a la derecha (con la nueva función insArbolder() el tope de pilaOperandos, desapilándolo.
        insArbolder(&subArbol, topeOperandos(pOperandos));
        popOperandos(&pOperandos);

        // Inserto a la izquierda (con la nueva función insArbolizq() el tope de pilaOperandos, desapilándolo.
        insArbolizq(&subArbol, topeOperandos(pOperandos));
        popOperandos(&pOperandos);

        // Inserto el árbol aux en pilaOperandos
        pushOperandos(&pOperandos, subArbol);
    }

    // Creo el árbol a devolver
    crear(&arbolSalida);

    // DESTRUYO LA PILA DE OPERADORES
    destruirPilaOperadores(&pOperadores);

    // ASIGNO A UNA VARIABLE DE TIPO abin (la que creé al principio de la función) EL TOPE DE LA PILA DE OPERANDOS
    insArbolizq(&arbolSalida, topeOperandos(pOperandos));
//    arbolSalida = topeOperandos(pOperandos);

    // DESAPILAR EL TOPE DE LA PILA DE OPERANDOS
    popOperandos(&pOperandos);

    //DESTRUYO LA PILA DE OPERANDOS
    destruirPilaOperandos(&pOperandos);

    // DEVUELVO EL ARBOL DE EXPRESION
    return arbolSalida;
}

