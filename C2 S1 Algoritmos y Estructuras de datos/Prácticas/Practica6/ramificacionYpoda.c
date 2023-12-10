//
// Created by imarc on 04/12/2023.
//

#include "ramificacionYpoda.h"
#include <stdlib.h>
#include <stdio.h>

// INICIO Funciones privadas necesarias para CI_precisa() y CS_precisa()

int _AsignacionVoraz(NODO *X, int B[][N])
{
    int beneficioActualAcumulado = 0;
    for (int i = X->nivel + 1; i < N; i++)
    {
        int max = 0;
        int indiceMax = 0;
        for (int j = 0; j < N; j++)
        {
            if (B[i][j] > max && X->usadas[j] == false)
            {
                max = B[i][j];
                indiceMax = j;
            }
        }
        X->usadas[indiceMax] = true;
        X->tupla[i] = indiceMax;
        beneficioActualAcumulado += max;
    }
    return beneficioActualAcumulado;
}

int _MaximoTareas(NODO *X, int B[][N])
{
    int max = 0;
    for (int i = X->nivel + 1; i < N; i++)
    {
        int maxFila = 0;
        for (int j = 0; j < N; j++)
        {
            if (B[i][j] > maxFila)
            {
                maxFila = B[i][j];
            }
        }
        max += maxFila;
    }
    return max;
}

// FIN Funciones privadas necesarias para CI_precisa() y CS_precisa()

// INICIO Función privada necesaria para calcular la solución voraz cuando CI==CS
NODO _SolAsignacionVoraz(NODO *X, int B[][N])
{
    int Bmax; // Para cada fila, beneficio máximo entre las tareas no usadas
    int tmax; // Para cada nivel, tarea no usada de mayor beneficio
    for (int i = X->nivel + 1; i < N; i++)
    {
        Bmax = -1;
        for (int j = 0; j < N; j++)
        {
            if (X->usadas[j] == false && B[i][j] > Bmax)
            {
                Bmax = B[i][j];
                tmax = j;
            }
        }
        X->tupla[i] = tmax;
        X->usadas[tmax] = true;
        X->beneficioActual += Bmax;
    }
    X->nivel = N - 1;
    return *X;
}

// FIN Función privada necesaria para calcular la solución voraz cuando CI==CS

// INICIO FUNCIONES PARA CALCULAR COTAS Y BENEFICIO

//beneficio estimado trivial-precisa
void BE(NODO *x)
{
    x->beneficioEstimado = (x->cotaInferior + x->cotaSuperior) / 2;
}

//cota inferior estimación trivial (D81)
void CI_trivial(NODO *x, int B[N][N])
{
    x->cotaInferior = x->beneficioActual;
}

//cota superior estimación trivial (D81)
void CS_trivial(NODO *x, const int B[][N])
{
    int max = 0;

//    for (int i = x->nivel + 1; i < N; i++)
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            if (B[i][j] > max)
            {
                max = B[i][j];
            }
        }
    }

    x->cotaSuperior = x->beneficioActual + (N - x->nivel) * max;
}

//cota inferior estimación precisa (D82)
void CI_precisa(NODO *x, int M[][N])
{
    x->cotaInferior = x->beneficioActual + _AsignacionVoraz(x, M);
}

//cota superior estimación precisa (D83)
void CS_precisa(NODO *x, int M[][N])
{
    x->cotaSuperior = x->beneficioActual + _MaximoTareas(x, M);
}

// FIN FUNCIONES PARA CALCULAR COTAS Y BENEFICIO

// INICIO FUNCIONES NECESARIAS PARA PROCEDIMIENTO DE RyP

//determina si x es solución (D80)
inline bool Solucion(const NODO x)
{
    return x.nivel == N-1;
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
        if (datosNodo.beneficioEstimado > max_beneficio)
        {
            max_beneficio = datosNodo.beneficioEstimado;
            nodoDeMayorBeneficio = nodo;
        }
        nodo = siguienteLista(*l, nodo);

    }

    return nodoDeMayorBeneficio;

}

// FIN FUNCIONES NECESARIAS PARA PROCEDIMIENTO DE RyP

void AsignacionTrivial(int B[N][N], NODO *const solucion, int *const nNodos)
//void AsignacionTrivial(int B[N][N], int solucion[N], int *const nNodos)
{

    /////////////////////////////////////////////////////////////////////////////////
    // INICIO INICIALIZACIONES
    /////////////////////////////////////////////////////////////////////////////////
    TLISTA listaDeNodosVivos; // Lista de nodos vivos

    NODO nodoRaiz;   //Nodo raíz
    NODO nodoSeleccionadoX; // nodo seleccionado (x)
    NODO nodoHijoY;   // nodo hijo de x (y)

    double Cota; // Variable de poda


    //Inicialización nodo raíz (diapositiva 79)
    for (int i = 0; i < N; i++)
    {
        nodoRaiz.tupla[i] = ASIGNACION_NO_VALIDA; // tupla de solución sin tareas asignadas
        nodoRaiz.usadas[i] = false; // todas las tareas están sin usar
    }

    nodoRaiz.nivel = -1; // Primer nivel del árbol
    nodoRaiz.beneficioActual = 0; // No hay asignaciones. Beneficio acumulado es 0


    CI_trivial(&nodoRaiz, B); // Cota inferior de la raíz trivial
    CS_trivial(&nodoRaiz, B); // Cota superior de la raíz trivial
    BE(&nodoRaiz); // Beneficio estimado de la raíz

    //Inicialización variable de poda (diapositiva 86)
    Cota = nodoRaiz.cotaInferior; // valor inicial de la variable de poda

    // Inicialización de la lista de nodos vivos (diapositiva 86)
    crearLista(&listaDeNodosVivos);

    // Guardo raíz como primer elemento de LNV
    insertarElementoLista(&listaDeNodosVivos, primeroLista(listaDeNodosVivos), nodoRaiz);

    /////////////////////////////////////////////////////////////////////////////////
    // FIN INICIALIZACIONES
    /////////////////////////////////////////////////////////////////////////////////

    // mientras LNV!= 0
    while (!esListaVacia(listaDeNodosVivos))
    {
        recuperarElementoLista(listaDeNodosVivos, Seleccionar(&listaDeNodosVivos), &nodoSeleccionadoX);
//        nodoActual = Seleccionar(&listaDeNodosVivos);
        suprimirElementoLista(&listaDeNodosVivos, Seleccionar(&listaDeNodosVivos));

        if (nodoSeleccionadoX.cotaSuperior > Cota)
        {
            //////////
            printf("Pasando por el nodo...\n");
            //////////

            for (int i = 0; i < N; i++)
            {
                nodoHijoY.nivel = nodoSeleccionadoX.nivel + 1; //y.nivel <- x.nivel + 1

                for (int j = 0; j < N; j++)
                {
                    nodoHijoY.tupla[j] = nodoSeleccionadoX.tupla[j];
                    nodoHijoY.usadas[j] = nodoSeleccionadoX.usadas[j];

                    /////////
                    printf("%d ", nodoHijoY.tupla[j]);
                    /////////

                }

                /////////
                printf("\n");
                /////////


                if (nodoHijoY.usadas[i] == false)
                {
                    nodoHijoY.tupla[nodoHijoY.nivel] = i;
                    nodoHijoY.usadas[i] = true;
                    nodoHijoY.beneficioActual = nodoSeleccionadoX.beneficioActual + B[nodoHijoY.nivel][i];

                    CI_trivial(&nodoHijoY,B);
                    CS_trivial(&nodoHijoY, B);
                    BE(&nodoHijoY);

                    if (Solucion(nodoHijoY) && nodoHijoY.beneficioActual > solucion->beneficioActual)
                    {
                        ////////
                        printf("Solucion encontrada: \n");
                        ////////



                        for (int j = 0; j < N; j++)
                        {
                            solucion->tupla[j] = nodoHijoY.tupla[j];
                            solucion->usadas[j] = nodoHijoY.usadas[j];
                            printf("%d ", solucion->tupla[j]);
                        }

                        solucion->nivel = nodoHijoY.nivel;
                        solucion->beneficioActual = nodoHijoY.beneficioActual;
                        solucion->cotaInferior = nodoHijoY.cotaInferior;
                        solucion->cotaSuperior = nodoHijoY.cotaSuperior;
                        solucion->beneficioEstimado = nodoHijoY.beneficioEstimado;



                        Cota = (Cota > solucion->beneficioActual) ? Cota : solucion->beneficioActual;
                    } else if (Solucion(nodoHijoY) == false && nodoHijoY.cotaSuperior > Cota)
                    {
                        insertarElementoLista(&listaDeNodosVivos, finLista(listaDeNodosVivos), nodoHijoY);
                        Cota = (Cota > nodoHijoY.cotaInferior) ? Cota : nodoHijoY.cotaInferior;
                    }
                }
            }
        }

    }
}


void AsignacionPrecisa(int B[][N], NODO *s, int *const nNodos)
{
    TLISTA listaDeNodosVivos;
    NODO nodoRaiz;
    NODO nodoActual;
    NODO nodoHijo;
    double valorTemporal;

    // Inicialización del nodo raíz
    nodoRaiz.beneficioActual = 0;
    nodoRaiz.nivel = -1;

    for (int i = 0; i < N; i++)
    {
        nodoRaiz.tupla[i] = -1;
        nodoRaiz.usadas[i] = false;
    }

    CI_precisa(&nodoRaiz, B); // Cota inferior de la raíz
    CS_precisa(&nodoRaiz, B); // Cota superior de la raíz
    BE(&nodoRaiz); // Beneficio estimado de la raíz

    valorTemporal = nodoRaiz.cotaInferior; // valor inicial de la variable de poda

    // Inicialización de la lista de nodos vivos
    crearLista(&listaDeNodosVivos);

    // Guardo el nodo raíz en la lista de nodos vivos
    insertarElementoLista(&listaDeNodosVivos, primeroLista(listaDeNodosVivos), nodoRaiz);

    // mientras LNV!= 0
    while (!esListaVacia(listaDeNodosVivos))
    {
        recuperarElementoLista(listaDeNodosVivos, Seleccionar(&listaDeNodosVivos), &nodoActual);
        suprimirElementoLista(&listaDeNodosVivos, Seleccionar(&listaDeNodosVivos));

        if (nodoActual.cotaSuperior > valorTemporal)
        {
            for (int i = 0; i < N; i++)
            {
                nodoHijo.nivel = nodoActual.nivel + 1; //y.nivel <- x.nivel + 1
                for (int j = 0; j < N; j++)
                {
                    nodoHijo.tupla[j] = nodoActual.tupla[j];
                    nodoHijo.usadas[j] = nodoActual.usadas[j];
                }
                if (!nodoActual.usadas[i])
                {
                    nodoHijo.tupla[nodoHijo.nivel] = i;
                    nodoHijo.usadas[i] = true;
                    nodoHijo.beneficioActual = nodoActual.beneficioActual + B[nodoHijo.nivel][i];
                    CI_precisa(&nodoHijo, B);
                    CS_precisa(&nodoHijo, B);
                    BE(&nodoHijo);

                    if (!Solucion(nodoHijo) && nodoHijo.cotaSuperior >= valorTemporal && nodoHijo.cotaSuperior == nodoHijo.cotaInferior)
                    {
                        nodoHijo = _SolAsignacionVoraz(&nodoHijo, B);
                        break; //Terminé la búsqueda, ya no analizo los demás hermanos
                    }

                    if (Solucion(nodoHijo) && nodoHijo.beneficioActual > s->beneficioActual)
                    {
                        s->beneficioActual = nodoHijo.beneficioActual;
                        s->nivel = nodoHijo.nivel;
                        s->beneficioEstimado = nodoHijo.beneficioEstimado;
                        s->cotaSuperior = nodoHijo.cotaSuperior;
                        s->cotaInferior = nodoHijo.cotaInferior;
                        for (int j = 0; j < N; j++)
                        {
                            s->tupla[j] = nodoHijo.tupla[j];
                            s->usadas[j] = nodoHijo.usadas[j];
                        }

                        valorTemporal = valorTemporal > nodoHijo.cotaInferior ? valorTemporal : nodoHijo.cotaInferior;
                    } else if (!Solucion(nodoHijo) && nodoHijo.cotaSuperior > valorTemporal)
                    {
                        insertarElementoLista(&listaDeNodosVivos, primeroLista(listaDeNodosVivos), nodoHijo);
                        valorTemporal = valorTemporal > nodoHijo.cotaInferior ? valorTemporal : nodoHijo.cotaInferior;
                    }
                }
            }
        } else if (nodoActual.cotaSuperior == valorTemporal && nodoActual.cotaSuperior == nodoActual.cotaInferior)
        {
            nodoHijo = _SolAsignacionVoraz(&nodoActual, B);
        }
    }
}
