//
// Created by imarc on 30/11/2023.
//

#include <stdio.h>
#include <malloc.h>
#include <limits.h>
#include "backtracking.h"


struct Estadisticas estadisticasBacktracking = {
        .nodosArbolGenerados = 0,
        .solucionesComprobadas = 0,
        .pasosTotales = 0,
        .pasosFuncionBacktracking = 0,
        .pasosFuncionGenerar = 0,
        .pasosFuncionCriterio = 0,
        .pasosFuncionSolucion = 0,
        .pasosFuncionMasHermanos = 0,
        .pasosFuncionRetroceder = 0
};

void Generar(const int matrizB[n][n], const short nivel, int solucion[], int *const beneficioActual)
{
    estadisticasBacktracking.pasosFuncionGenerar++;
    estadisticasBacktracking.pasosTotales++;

    //--

    solucion[nivel]++;// Solucion[nivel] +1 es el valor de la siguiente tarea a probar.


    *beneficioActual += matrizB[nivel][solucion[nivel]];

    if (solucion[nivel] > 0)// No es la primera tarea que pruebo
    {
        // Resto lo que asigné en la prueba anterior
        *beneficioActual -= matrizB[nivel][solucion[nivel] - 1];
    }
}


bool Criterio(const short nivel, const int solucion[])
{
    for (int i = 0; i < nivel; i++)
    {
        estadisticasBacktracking.pasosFuncionCriterio++;
        estadisticasBacktracking.pasosTotales++;

        //--

        if (solucion[nivel] == solucion[i])
        {
            return false;
        }
    }

    return true;
}

bool Solucion(const short nivel, const int solucion[])
{
    estadisticasBacktracking.pasosFuncionSolucion++;
    estadisticasBacktracking.pasosTotales++;

    //--

    return (nivel == (n - 1) && Criterio(nivel, solucion));
}

bool MasHermanos(const short nivel, const int solucion[])
{
    estadisticasBacktracking.pasosFuncionMasHermanos++;
    estadisticasBacktracking.pasosTotales++;

    //--

    return solucion[nivel] < (n - 1);
}

void Retroceder(const int matrizB[n][n], short *const nivel, int solucion[], int *const beneficioActual)
{
    estadisticasBacktracking.pasosFuncionRetroceder++;
    estadisticasBacktracking.pasosTotales++;

    //--

    *beneficioActual -= matrizB[*nivel][solucion[*nivel]];

    solucion[*nivel] = ASIGNACION_NO_VALIDA;

    (*nivel)--;
}

/*
 int Valor(const int solucion[])
{
    int valor = 0;
    for (int i = 0; i < n; i++)
    {
        valor += solucion[i];
    }
    return valor;
    }
*/

//--

int BackTracking(const int matrizB[n][n], int *const solucion)
{
    short nivel = 0;

    // Cada solucion[i] indica la tarea (valor entre 0 y n-1) asignada a la persona i (valor entre 0 y n-1)
    // Hay que inicializarla a un valor adecuado. Por ejemplo, -1 (Un valor no válido como asignación).
    for (int i = 0; i < n; i++)
    {
        solucion[i] = ASIGNACION_NO_VALIDA;
    }

    int valorOptimoActual = INT_MIN;

    int solucionOptimaActual[n]; // Solución óptima actual
    for (int i = 0; i < n; i++)
    {
        solucionOptimaActual[i] = INT_MIN;
    }

    // Beneficio de la solución actual
    int beneficioActual = 0;

    estadisticasBacktracking.nodosArbolGenerados++;// Nodo raíz del árbol permutacional

    do
    {
        estadisticasBacktracking.pasosFuncionBacktracking++;
        estadisticasBacktracking.pasosTotales++;
//        estadisticasBacktracking.solucionesComprobadas++;

        //--

        Generar(matrizB, nivel, solucion, &beneficioActual);

        if (Solucion(nivel, solucion))
        {

            estadisticasBacktracking.nodosArbolGenerados++;//Nodo hoja (válido)
            estadisticasBacktracking.solucionesComprobadas++; //Nodo hoja (posible solución)

            if (beneficioActual > valorOptimoActual)
            {
                valorOptimoActual = beneficioActual;

                for (int i = 0; i < n; i++)
                {
                    solucionOptimaActual[i] = solucion[i];
                }
            }
        }

        if (Criterio(nivel, solucion) && (nivel < (n - 1)))
        {
            estadisticasBacktracking.nodosArbolGenerados++; //Nodo intermedio (válido)

            nivel++;
        }

        while (!MasHermanos(nivel, solucion) && (nivel >= 0))
        {
            Retroceder(matrizB, &nivel, solucion, &beneficioActual);
        }
    } while (nivel != -1);

    for (int i = 0; i < n; i++)
    {
        solucion[i] = solucionOptimaActual[i];
    }

    return valorOptimoActual;
}
