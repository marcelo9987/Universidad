//
// Created by imarc on 13/12/2023.
//

#include <stdbool.h>
#include <stdio.h>
#include <limits.h>
#include "estimacionesTriviales.h"
#include "ramificacionYpoda.h"

struct Estadisticas_ryp estadisticasRyPTriviales = {
        .nodosArbolGenerados = 0,
        .nodosInsertadosEnLaLista = 0,
        .nodosExtraidosDeLaLista = 0,
        .nodosQueCumplenCriterio = 0,
        .nodosVorazAdicionales = 0,

        .solucionesComprobadas = 0
};

// INICIO Funciones cálculo cotas

int _maximoMatriz(const int B[N][N])
{
    int beneficioMaximo = INT_MIN;

    for (int persona = 0; persona < N; persona++)
    {
        for (int tarea = 0; tarea < N; tarea++)
        {
            if (B[persona][tarea] > beneficioMaximo)
            {
                beneficioMaximo = B[persona][tarea];
            }
        }
    }

    return beneficioMaximo;
}

/*int _minimoMatriz(const int B[N][N])
{
    int beneficioMinimo = INT_MAX;

    for (int persona = 0; persona < N; persona++)
    {
        for (int tarea = 0; tarea < N; tarea++)
        {
            if (B[persona][tarea] < beneficioMinimo)
            {
                beneficioMinimo = B[persona][tarea];
            }
        }
    }

    return beneficioMinimo;
}*/

//##


//cota inferior estimación trivial (D81)
void CI_trivial(NODO *const nodo, const int B[N][N])
{
    nodo->cotaInferior = nodo->beneficioActual;
}

//cota superior estimación trivial (D81)
void CS_trivial(NODO *nodo, const int B[N][N], const int maxMatriz)
{
//    printf("%s - Nivel: %2d, BA: %3d, factor: %d\n", __FUNCTION__, nodo->nivel, nodo->beneficioActual, N - (nodo->nivel + 1));
    nodo->cotaSuperior = nodo->beneficioActual + (N - (nodo->nivel + 1)) * maxMatriz;
}

void _calculaCotasTriviales(NODO *const nodo, const int B[N][N], int maxMatriz)
{
    CI_trivial(nodo, B);// Cota inferior precisa de este nodo
    CS_trivial(nodo, B, maxMatriz);// Cota superior precisa de este nodo
    BE(nodo);// Beneficio estimado de este nodo
}

// FIN Funciones cálculo cotas

int AsignacionTrivial(const int B[N][N], NODO *const solucion)
{
    /////////////////////////////////////////////////////////////////////////////////
    // INICIO INICIALIZACIONES
    /////////////////////////////////////////////////////////////////////////////////

    NODO nodoRaiz;//Nodo raíz

    //Inicialización nodo raíz (diapositiva 79)
    for (int i = 0; i < N; i++)
    {
        nodoRaiz.tupla[i] = ASIGNACION_NO_VALIDA; // tupla de solución sin tareas asignadas
        nodoRaiz.usadas[i] = false; // todas las tareas están sin usar
    }

    nodoRaiz.nivel = -1; // Primer nivel del árbol
    nodoRaiz.beneficioActual = 0; // No hay asignaciones. Beneficio acumulado es 0

    estadisticasRyPTriviales.nodosArbolGenerados++;

    nodoRaiz.numNodo = estadisticasRyPTriviales.nodosArbolGenerados;
    nodoRaiz.numNodoPadre = -1;

    int maxMatriz = _maximoMatriz(B);

    _calculaCotasTriviales(&nodoRaiz, B, maxMatriz);

    //Inicialización variable de poda (diapositiva 86)
    // Almacenará el valor de las cotas superiores hasta ese momento o de alguna solución final
    int Cota = nodoRaiz.cotaSuperior; // valor inicial de la variable de poda

    printf("Cota inicial: %3d\n", Cota);

    TLISTA listaDeNodosVivos; // Lista de nodos vivos
    // Inicialización de la lista de nodos vivos (diapositiva 86)
    crearLista(&listaDeNodosVivos);

    // Guardo el nodo raíz en la lista de nodos vivos
    _insertarEnLaLista(&listaDeNodosVivos, &nodoRaiz);

    estadisticasRyPTriviales.nodosInsertadosEnLaLista++;

//    _imprimeInfoNodo(&nodoRaiz);

    /////////////////////////////////////////////////////////////////////////////////
    // FIN INICIALIZACIONES
    /////////////////////////////////////////////////////////////////////////////////


    // mientras LNV!= 0
    while (!esListaVacia(listaDeNodosVivos))
    {
        NODO nodoSeleccionadoX; // Nodo seleccionado (x)
        _seleccionarYeliminarDeLaLista(&listaDeNodosVivos, &nodoSeleccionadoX);

        estadisticasRyPTriviales.nodosExtraidosDeLaLista++;

        if (nodoSeleccionadoX.cotaInferior < Cota)
        {
            for (int tarea = 0; tarea < N; tarea++)
            {
                NODO nodoHijoY; // Nodo hijo de x (y)

                nodoHijoY.nivel = nodoSeleccionadoX.nivel + 1; //y.nivel <- x.nivel + 1

                clonaNodos(&nodoHijoY, &nodoSeleccionadoX, false);

                if (!nodoHijoY.usadas[tarea])
                {
                    estadisticasRyPTriviales.nodosArbolGenerados++;
                    estadisticasRyPTriviales.nodosQueCumplenCriterio++;

                    nodoHijoY.numNodo = estadisticasRyPTriviales.nodosArbolGenerados;
                    nodoHijoY.numNodoPadre = nodoSeleccionadoX.numNodo;

                    nodoHijoY.tupla[nodoHijoY.nivel] = tarea;
                    nodoHijoY.usadas[tarea] = true;
                    nodoHijoY.beneficioActual = nodoSeleccionadoX.beneficioActual + B[nodoHijoY.nivel][tarea];

                    _calculaCotasTriviales(&nodoHijoY, B, maxMatriz);

                    _imprimeInfoNodo("Nuevo Hijo", &nodoHijoY);

                    //--

                    //--

                    if (Solucion(&nodoHijoY))
                    {
                        estadisticasRyPTriviales.solucionesComprobadas++;

                        if (nodoHijoY.beneficioActual < solucion->beneficioActual)
                        {
                            clonaNodos(solucion, &nodoHijoY, true);

                            _imprimeInfoNodo("actualizada solución", solucion);

                            if (nodoHijoY.beneficioActual < Cota)
                            {
                                Cota = nodoHijoY.beneficioActual;

                                printf("Cota <- Beneficio Actual: %3d\n", Cota);
                            }
                        }
                    } else if (nodoHijoY.cotaInferior < Cota)
                    {
                        _insertarEnLaLista(&listaDeNodosVivos, &nodoHijoY); // inserto por el principio (LIFO)

                        estadisticasRyPTriviales.nodosInsertadosEnLaLista++;

                        if (nodoHijoY.cotaSuperior < Cota)
                        {
                            Cota = nodoHijoY.cotaSuperior;

                            printf("Cota <- Cota Inferior: %3d\n", Cota);
                        }
                    } else
                    {
                        _imprimeInfoNodo("Nodo Y descartado (poda)", &nodoHijoY);
                    }
                }
            }
        } else
        {
            _imprimeInfoNodo("Nodo X descartado (poda)", &nodoSeleccionadoX);
        }

    }

    destruirLista(&listaDeNodosVivos);

    return solucion->beneficioActual;
}
