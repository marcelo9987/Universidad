//
// Created by imarc on 13/12/2023.
//

#include <stdbool.h>
#include <stdio.h>
#include <limits.h>
#include "estimacionesPrecisas.h"
#include "ramificacionYpoda.h"

struct Estadisticas_ryp estadisticasRyPPrecisas = {
        .nodosArbolGenerados = 0,
        .nodosInsertadosEnLaLista = 0,
        .nodosExtraidosDeLaLista = 0,
        .nodosQueCumplenCriterio = 0,
        .nodosVorazAdicionales = 0,

        .solucionesComprobadas = 0
};

//--



int _getTareaBeneficioMinimo(int persona, const bool usadas[N], const int B[N][N])
{
    int beneficioMinimo = INT_MAX; // Para cada fila, beneficio mínimo entre las tareas no usadas
    int tareaBeneficioMinimo = -1; // Para cada nivel, tarea no usada de menor beneficio

    for (int tarea = 0; tarea < N; tarea++)
    {
        if (!usadas[tarea] && B[persona][tarea] < beneficioMinimo)
        {
            beneficioMinimo = B[persona][tarea];
            tareaBeneficioMinimo = tarea;
        }
    }

    return tareaBeneficioMinimo;
}

//==
//==

// Función privada necesaria para calcular la solución voraz cuando CI==CS
void _SolAsignacionVoraz(NODO *const nodo, const int B[N][N])
{
//    printf("%s: INICIO\n", __FUNCTION__);

    for (int persona = nodo->nivel + 1; persona < N; persona++)
    {
        int tareaBeneficioMinimo = _getTareaBeneficioMinimo(persona, nodo->usadas, B);

        nodo->tupla[persona] = tareaBeneficioMinimo;

        nodo->beneficioActual += B[persona][tareaBeneficioMinimo];

        nodo->usadas[tareaBeneficioMinimo] = true;

        estadisticasRyPPrecisas.nodosArbolGenerados++;
        estadisticasRyPPrecisas.nodosQueCumplenCriterio++;

        _imprimeInfoNodo("_SolAsignacionVoraz", nodo);

    }

    nodo->nivel = N - 1;


//    printf("El nodo salida (nivel) en la función %s, linea %d es %d\n", __FUNCTION__, __LINE__, nodo->nivel);
//    printf("%s: FIN\n", __FUNCTION__);

}

// INICIO Funciones cálculo cotas

int _AsignacionVoraz(const NODO *const nodo, const int B[N][N])
{
    int beneficioActualAcumulado = 0;

    bool usadas[N];
    for (int tarea = 0; tarea < N; tarea++)
    {
        usadas[tarea] = nodo->usadas[tarea];
    }

    for (int persona = nodo->nivel + 1; persona < N; persona++)
    {
        int tareaBeneficioMinimo = _getTareaBeneficioMinimo(persona, usadas, B);

        beneficioActualAcumulado += B[persona][tareaBeneficioMinimo];

        usadas[tareaBeneficioMinimo] = true;

        estadisticasRyPPrecisas.nodosVorazAdicionales++;

    }

    return beneficioActualAcumulado;
}

int _MinimoTareas(const NODO *const nodo, const int B[N][N])
{
    int beneficioActualAcumulado = 0;

    //--

    for (int persona = nodo->nivel + 1; persona < N; persona++)
    {
        int tareaBeneficioMinimo = _getTareaBeneficioMinimo(persona, nodo->usadas, B);

        beneficioActualAcumulado += B[persona][tareaBeneficioMinimo];

        estadisticasRyPPrecisas.nodosVorazAdicionales++;

    }

    return beneficioActualAcumulado;
}

//##


//cota inferior estimación precisa (D82)
void CI_precisa(NODO *nodo, const int B[N][N])
{
    nodo->cotaInferior = nodo->beneficioActual + _MinimoTareas(nodo, B);
}

//cota superior estimación precisa (D83)
void CS_precisa(NODO *nodo, const int B[N][N])
{
    nodo->cotaSuperior = nodo->beneficioActual + _AsignacionVoraz(nodo, B);
}

void _calculaCotasPrecisas(NODO *const nodo, const int B[N][N])
{
    CI_precisa(nodo, B); // Cota inferior precisa de este nodo
    CS_precisa(nodo, B); // Cota superior precisa de este nodo
    BE(nodo); // Beneficio estimado de este nodo
}

// FIN Funciones cálculo cotas

int AsignacionPrecisa(const int B[N][N], NODO *const solucion)
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

    estadisticasRyPPrecisas.nodosArbolGenerados++;

    nodoRaiz.numNodo = estadisticasRyPPrecisas.nodosArbolGenerados;
    nodoRaiz.numNodoPadre = -1;

    _calculaCotasPrecisas(&nodoRaiz, B);

    //Inicialización variable de poda (diapositiva 86)
    // Almacenará el valor de las cotas superiores hasta ese momento o de alguna solución final
    int Cota = nodoRaiz.cotaSuperior; // valor inicial de la variable de poda

    printf("Cota inicial: %3d\n", Cota);

    TLISTA listaDeNodosVivos; // Lista de nodos vivos
    // Inicialización de la lista de nodos vivos (diapositiva 86)
    crearLista(&listaDeNodosVivos);

    // Guardo el nodo raíz en la lista de nodos vivos
    _insertarEnLaLista(&listaDeNodosVivos, &nodoRaiz);

    estadisticasRyPPrecisas.nodosInsertadosEnLaLista++;

//    _imprimeInfoNodo(&nodoRaiz);

    /////////////////////////////////////////////////////////////////////////////////
    // FIN INICIALIZACIONES
    /////////////////////////////////////////////////////////////////////////////////


    // mientras LNV!= 0
    while (!esListaVacia(listaDeNodosVivos))
    {
        NODO nodoSeleccionadoX; // Nodo seleccionado (x)
        _seleccionarYeliminarDeLaLista(&listaDeNodosVivos, &nodoSeleccionadoX);

        estadisticasRyPPrecisas.nodosExtraidosDeLaLista++;

        if (nodoSeleccionadoX.cotaInferior < Cota)
        {
            for (int tarea = 0; tarea < N; tarea++)
            {
                NODO nodoHijoY; // Nodo hijo de x (y)

                nodoHijoY.nivel = nodoSeleccionadoX.nivel + 1; //y.nivel <- x.nivel + 1

                clonaNodos(&nodoHijoY, &nodoSeleccionadoX, false);

                if (!nodoHijoY.usadas[tarea])
                {
                    estadisticasRyPPrecisas.nodosArbolGenerados++;
                    estadisticasRyPPrecisas.nodosQueCumplenCriterio++;

                    nodoHijoY.numNodo = estadisticasRyPPrecisas.nodosArbolGenerados;
                    nodoHijoY.numNodoPadre = nodoSeleccionadoX.numNodo;

                    nodoHijoY.tupla[nodoHijoY.nivel] = tarea;
                    nodoHijoY.usadas[tarea] = true;
                    nodoHijoY.beneficioActual = nodoSeleccionadoX.beneficioActual + B[nodoHijoY.nivel][tarea];

                    _calculaCotasPrecisas(&nodoHijoY, B);

                    _imprimeInfoNodo("Nuevo Hijo", &nodoHijoY);

                    //--

                    if (!Solucion(&nodoHijoY) && nodoHijoY.cotaInferior <= Cota && nodoHijoY.cotaSuperior == nodoHijoY.cotaInferior)
                    {
                        clonaNodos(solucion, &nodoHijoY, true);
                        _SolAsignacionVoraz(solucion, B);

//                        estadisticasRyPPrecisas.solucionesComprobadas++;

                        _imprimeInfoNodo("sol voraz arriba", solucion);


//                        destruirLista(&listaDeNodosVivos);
//
//                        return solucion->beneficioActual; //Terminé la búsqueda, ya no analizo los demás hermanos
                    }

                    //--

                    if (Solucion(&nodoHijoY))
                    {
                        estadisticasRyPPrecisas.solucionesComprobadas++;

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

                        estadisticasRyPPrecisas.nodosInsertadosEnLaLista++;

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
        } else if (nodoSeleccionadoX.cotaInferior == Cota && nodoSeleccionadoX.cotaSuperior == nodoSeleccionadoX.cotaInferior)
        {
            clonaNodos(solucion, &nodoSeleccionadoX, true);
            _SolAsignacionVoraz(solucion, B);

            estadisticasRyPPrecisas.solucionesComprobadas++;

            _imprimeInfoNodo("sol voraz abajo", solucion);

        } else
        {
            _imprimeInfoNodo("Nodo X descartado (poda)", &nodoSeleccionadoX);
        }
    }

    destruirLista(&listaDeNodosVivos);

    return solucion->beneficioActual;
}
