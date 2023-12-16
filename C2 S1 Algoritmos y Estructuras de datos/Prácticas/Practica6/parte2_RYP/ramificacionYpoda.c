#include <stdio.h>
#include "ramificacionYpoda.h"


//beneficio estimado trivial-precisa
void BE(NODO *x)
{
    x->beneficioEstimado = (x->cotaInferior + x->cotaSuperior) / 2.0;
}


// INICIO FUNCIONES NECESARIAS PARA PROCEDIMIENTO DE RyP

//determina si x es solución (D80)
inline bool Solucion(const NODO *const x)
{
    return x->nivel == N - 1;
}

//Devuelve nodo según estrategia MB-LIFO
TPOSICION Seleccionar(TLISTA *l)
{
    TPOSICION nodoDeMayorBeneficio;
    double max_beneficio = -1;

    TPOSICION nodo = primeroLista(*l);

    while (nodo != finLista(*l))
    {
        TIPOELEMENTO datosNodo;
        recuperarElementoLista(*l, nodo, &datosNodo);
        // todo: comprobar si esto es correcto
        // Los nodos se insertan siempre desde el principio de la lista, por lo que nos quedamos con el primer nodo con máximo beneficio
        if (datosNodo.beneficioEstimado > max_beneficio)
        {
            max_beneficio = datosNodo.beneficioEstimado;
            nodoDeMayorBeneficio = nodo;
        }
        nodo = siguienteLista(*l, nodo);

    }

    return nodoDeMayorBeneficio;
}

void _imprimeInfoNodo(const char *const textoInicial, const NODO *const nodo)
{
#ifdef DEBUG
    printf("%-20s - Nodo: %4d <- %4d  nivel: %2d  CI: %3d  BE: %5.1f  CS: %3d  BA: %3d\n",textoInicial, nodo->numNodo,nodo->numNodoPadre, nodo->nivel, nodo->cotaInferior, nodo->beneficioEstimado, nodo->cotaSuperior, nodo->beneficioActual);
#endif
}

void _insertarEnLaLista(TLISTA *listaDeNodosVivos, NODO *nodo)
{
    insertarElementoLista(listaDeNodosVivos, primeroLista(*listaDeNodosVivos), *nodo);

    _imprimeInfoNodo("NODO INSERTADO", nodo);
}

void _seleccionarYeliminarDeLaLista(TLISTA *listaDeNodosVivos, NODO *nodo)
{
    TPOSICION seleccionada = Seleccionar(listaDeNodosVivos);
    recuperarElementoLista((*listaDeNodosVivos), seleccionada, nodo);
    suprimirElementoLista(listaDeNodosVivos, seleccionada);

    _imprimeInfoNodo("NODO EXTRAIDO ", nodo);
}

void clonaNodos(NODO *const destino, const NODO *const origen, const bool completo)
{
    for (int pos = 0; pos < N; pos++)
    {
        destino->tupla[pos] = origen->tupla[pos];
        destino->usadas[pos] = origen->usadas[pos];
    }

    if (completo)
    {
        destino->nivel = origen->nivel;
        destino->beneficioActual = origen->beneficioActual;
        destino->cotaInferior = origen->cotaInferior;
        destino->cotaSuperior = origen->cotaSuperior;
        destino->beneficioEstimado = origen->beneficioEstimado;
        destino->numNodo = origen->numNodo;
        destino->numNodoPadre = origen->numNodoPadre;
    }
}
