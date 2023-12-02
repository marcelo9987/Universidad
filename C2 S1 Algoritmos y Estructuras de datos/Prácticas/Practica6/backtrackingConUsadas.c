//
// Created by imarc on 02/12/2023.
//

#include <limits.h>
#include "backtrackingConUsadas.h"


void GenerarConUsadas(const int matrizB[n][n], const short nivel, int solucion[], int *const beneficioActual, int usadas[])
{
    if (solucion[nivel] != ASIGNACION_NO_VALIDA)
    {
        usadas[solucion[nivel]]--;
    }

    solucion[nivel]++;// Solucion[nivel] +1 es el valor de la siguiente tarea a probar.

    usadas[solucion[nivel]]++;

    *beneficioActual += matrizB[nivel][solucion[nivel]];

    if (solucion[nivel] > 0)// No es la primera tarea que pruebo
    {
        // Resto lo que asigné en la prueba anterior
        *beneficioActual -= matrizB[nivel][solucion[nivel] - 1];
    }

}


bool CriterioConUsadas(const short nivel, const int solucion[], const int usadas[])
{
    return usadas[solucion[nivel]] == 1;
}

bool SolucionConUsadas(const short nivel, const int solucion[], const int usadas[])
{
    return (nivel == (n - 1) && CriterioConUsadas(nivel, solucion, usadas));
}

bool MasHermanosConUsadas(const short nivel, const int solucion[])
{
    return solucion[nivel] < (n - 1);
}


void RetrocederConUsadas(const int matrizB[n][n], short *const nivel, int solucion[], int *const beneficioActual, int usadas[])
{
    *beneficioActual -= matrizB[*nivel][solucion[*nivel]];

    usadas[solucion[*nivel]]--;

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

int BackTrackingConUsadas(const int matrizB[n][n], int *const solucion)
{
    short nivel = 0;

    // Cada solucion[i] indica la tarea (valor entre 0 y n-1) asignada a la persona i (valor entre 0 y n-1)
    // Hay que inicializarla a un valor adecuado. Por ejemplo, -1 (Un valor no válido como asignación).
    for (int i = 0; i < n; i++)
    {
        solucion[i] = ASIGNACION_NO_VALIDA;
    }

    int valorOptimoActual = INT_MIN;

    int usadas[n];
    for (int i = 0; i < n; i++)
    {
        usadas[i] = 0;
    }

    int solucionOptimaActual[n]; // Solución óptima actual
    for (int i = 0; i < n; i++)
    {
        solucionOptimaActual[i] = INT_MIN;
    }

    // Beneficio de la solución actual
    int beneficioActual = 0;

//    int nodosGenerados = 0;

    do
    {
        GenerarConUsadas(matrizB, nivel, solucion, &beneficioActual, usadas);
//        nodosGenerados++;
        if (SolucionConUsadas(nivel, solucion, usadas) && (beneficioActual > valorOptimoActual))
        {
            valorOptimoActual = beneficioActual;

            for (int i = 0; i < n; i++)
            {
                solucionOptimaActual[i] = solucion[i];
            }
        }

        if (CriterioConUsadas(nivel, solucion, usadas) && (nivel < (n - 1)))
        {
            nivel++;
        }

        while (!MasHermanosConUsadas(nivel, solucion) && (nivel >= 0))
        {
            RetrocederConUsadas(matrizB, &nivel, solucion, &beneficioActual, usadas);
        }
    } while (nivel != -1);

    for (int i = 0; i < n; i++)
    {
        solucion[i] = solucionOptimaActual[i];
    }

    return valorOptimoActual;
}
