#include <stdio.h>

#include "backtracking.h"
#include "backtrackingConUsadas.h"

int main(int argc, char *argv[])
{


/*
     B    0    1    2
     0 |  4 |  9 |  1 |
     1 |  7 |  2 |  3 |
     2 |  6 |  3 |  5 |
*/

/*
  int matrizB0[n][n] = {
            {4, 9, 1},
            {7, 2, 3},
            {6, 3, 5}
    };
*/


/*
     B2    0    1    2
     0 | 11 | 17 |  8 |
     1 |  9 |  7 |  6 |
     2 | 13 | 15 | 16 |
*/

#if n == 2
    int matrizB[n][n] = {
            {11, 17},
            {9,  7}
    };
#elif n == 35
    int matrizB[n][n] = {
            {11, 17, 8},
            {9,  7,  6},
            {13, 15, 16}
#elif n == 3
    int matrizB[n][n] = {
            {4,9,1},
            {7,2,3},
            {6,3,5}
    };
#elif n == 4
    int matrizB[n][n] = {
            {11, 17, 8,  16},
            {9,  7,  6,  12},
            {13, 15, 16, 12},
            {21, 24, 28, 17}
    };
#elif n == 5
    int matrizB[n][n] = {
            {11, 17, 8,  16, 20},
            {9,  7,  6,  12, 15},
            {13, 15, 16, 12, 16},
            {21, 24, 28, 17, 26},
            {10, 14, 12, 11, 15}
    };
#elif n == 6
    int matrizB[n][n] = {
            {11, 17, 8,  16, 20, 14},
            {9,  7,  6,  12, 15, 18},
            {13, 15, 16, 12, 16, 18},
            {21, 24, 28, 17, 26, 20},
            {10, 14, 12, 11, 15, 13},
            {12, 20, 19, 13, 22, 17}
    };
#endif

    int solucion[n];

    // ------------------------- SIN USADAS ----------------------------------- //


    int valorOptimo = BackTracking(matrizB, solucion);

    printf("El valor óptimo (sin usadas) es: %d\n", valorOptimo);

    printf("La solucion optima (sin usadas) es: \n");
    // Cada solucion[i] indica la tarea (valor entre 0 y n-1) asignada a la persona i (valor entre 0 y n-1)
    for (int persona = 0; persona < n; persona++)
    {
        printf("\tLa persona %d realizará la tarea %d, con un beneficio de %2d\n", persona + 1, solucion[persona] + 1, matrizB[persona][solucion[persona]]);
    }

    printf("\n");

    printf("Nodos generados:            %5d (los que cumplen el criterio)\n", estadisticasBacktracking.nodosArbolGenerados);
    printf("Soluciones comprobadas:     %5d (nodos hoja del árbol)\n\n", estadisticasBacktracking.solucionesComprobadas);

    printf("Pasos función backtracking: %5d\n", estadisticasBacktracking.pasosFuncionBacktracking);
    printf("Pasos función criterio:     %5d\n", estadisticasBacktracking.pasosFuncionCriterio);
    printf("Pasos función solución:     %5d\n", estadisticasBacktracking.pasosFuncionSolucion);
    printf("Pasos función generar:      %5d\n", estadisticasBacktracking.pasosFuncionGenerar);
    printf("Pasos función más hermanos: %5d\n", estadisticasBacktracking.pasosFuncionMasHermanos);
    printf("Pasos función retroceder:   %5d\n\n", estadisticasBacktracking.pasosFuncionRetroceder);

    printf("Pasos totales:              %5d\n", estadisticasBacktracking.pasosTotales);


    printf("\n\n");

    // ------------------------- CON USADAS ----------------------------------- //


    valorOptimo = BackTrackingConUsadas(matrizB, solucion);

    printf("El valor óptimo (con usadas) es: %d\n", valorOptimo);

    printf("La solucion optima (con usadas) es: \n");
    // Cada solucion[i] indica la tarea (valor entre 0 y n-1) asignada a la persona i (valor entre 0 y n-1)
    for (int persona = 0; persona < n; persona++)
    {
        printf("\tLa persona %d realizará la tarea %d, con un beneficio de %2d\n", persona + 1, solucion[persona] + 1, matrizB[persona][solucion[persona]]);
    }

    printf("\n");

    printf("Nodos generados:            %5d (los que cumplen el criterio)\n", estadisticasBacktrackingConUsadas.nodosArbolGenerados);
    printf("Soluciones comprobadas:     %5d (nodos hoja del árbol)\n\n", estadisticasBacktrackingConUsadas.solucionesComprobadas);

    printf("Pasos función backtracking: %5d\n", estadisticasBacktrackingConUsadas.pasosFuncionBacktracking);
    printf("Pasos función criterio:     %5d\n", estadisticasBacktrackingConUsadas.pasosFuncionCriterio);
    printf("Pasos función solución:     %5d\n", estadisticasBacktrackingConUsadas.pasosFuncionSolucion);
    printf("Pasos función generar:      %5d\n", estadisticasBacktrackingConUsadas.pasosFuncionGenerar);
    printf("Pasos función más hermanos: %5d\n", estadisticasBacktrackingConUsadas.pasosFuncionMasHermanos);
    printf("Pasos función retroceder:   %5d\n\n", estadisticasBacktrackingConUsadas.pasosFuncionRetroceder);

    printf("Pasos totales:              %5d\n", estadisticasBacktrackingConUsadas.pasosTotales);

    return 0;
}
