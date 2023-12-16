#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <sys/unistd.h>

#include "ramificacionYpoda.h"
#include "estimacionesTriviales.h"
#include "estimacionesPrecisas.h"

#define usarAleatorios true

void inicializar_solucion(NODO *const solucion)
{
    for (int i = 0; i < N; i++)
    {
        solucion->tupla[i] = ASIGNACION_NO_VALIDA;
        solucion->usadas[i] = false;
    }

    solucion->nivel = -1;
    solucion->beneficioActual = 0;
    solucion->cotaInferior = 0;
    solucion->cotaSuperior = 0;
    solucion->beneficioEstimado = 0;
}

int main()
{


#if n == 2
    int matrizB[n][n] = {
                {11, 17},
                {9,  7}
        };
#elif n == -3
    int matrizB[n][n] ={
            {11, 17, 8},
            {9,  7,  6},
            {13, 15, 16}
    };
#elif n == -3
    int matrizB[n][n] = {
            {4, 9, 1},
            {7, 2, 3},
            {6, 3, 5}
    };
#elif n == 3
    int matrizB[n][n] = {
            {24, 27, 3},
            {28, 19, 19},
            {21, 0,  7}
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
#elif n == -6
    int matrizB[n][n] = {
            {19, 25, 23,  3, 22,  1 },
            {26, 25,  1, 15,  1, 20 },
            {20,  9, 24,  9, 27, 21 },
            {13,  1,  3, 26, 23, 24 },
            {23, 10,  7, 10, 26,  9 },
            { 8,  7, 26, 23, 10, 18 }
    };
#endif

    if (usarAleatorios)
    {
        srand(getpid());
        for (int persona = 0; persona < n; persona++)
        {
            printf("{");
            for (int tarea = 0; tarea < n; tarea++)
            {
                matrizB[persona][tarea] = rand() % 30;
                printf("%2d, ", matrizB[persona][tarea]);
            }
            printf("}\n");
        }

    }

    NODO solucionTrivial;

    inicializar_solucion(&solucionTrivial);


    int nNodosTrivial = AsignacionTrivial(matrizB, &solucionTrivial);
    printf("Asignación trivial: \n");

//    printf("  Número de nodos: %d\n", nNodosTrivial);

    /*
     *     printf("\n");

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
     */

    printf("  Nodos generados: %d\n", estadisticasRyPTriviales.nodosArbolGenerados);
    printf("  Nodos que cumplen criterio: %d\n", estadisticasRyPTriviales.nodosQueCumplenCriterio);
    printf("  Nodos insertados en la lista: %d\n", estadisticasRyPTriviales.nodosInsertadosEnLaLista);
    printf("  Nodos extraídos de la lista: %d\n", estadisticasRyPTriviales.nodosExtraidosDeLaLista);
    printf("  Soluciones comprobadas: %d\n", estadisticasRyPTriviales.solucionesComprobadas);
    printf("  Nodos voraces adicionales: %d\n", estadisticasRyPTriviales.nodosVorazAdicionales);
    printf("\n");


    int sumaBeneficioTrivial = 0;


    for (int persona = 0; persona < n; persona++)
    {
        printf("\tLa persona %d realizará la tarea %d, con un beneficio de %2d\n", persona, solucionTrivial.tupla[persona], matrizB[persona][solucionTrivial.tupla[persona]]);
        sumaBeneficioTrivial += matrizB[persona][solucionTrivial.tupla[persona]];
    }

    printf("\n");
    printf("\tBeneficio total: %d\n", sumaBeneficioTrivial);
    printf("\n\n");


    NODO solucionPrecisa;

    inicializar_solucion(&solucionPrecisa);

    int nNodosPrecisa = AsignacionPrecisa(matrizB, &solucionPrecisa);

    printf("Asignación precisa: \n");

//    printf("  Número de nodos: %d\n", nNodosPrecisa);

    printf("  Nodos generados: %d\n", estadisticasRyPPrecisas.nodosArbolGenerados);
    printf("  Nodos que cumplen criterio: %d\n", estadisticasRyPPrecisas.nodosQueCumplenCriterio);
    printf("  Nodos insertados en la lista: %d\n", estadisticasRyPPrecisas.nodosInsertadosEnLaLista);
    printf("  Nodos extraídos de la lista: %d\n", estadisticasRyPPrecisas.nodosExtraidosDeLaLista);
    printf("  Soluciones comprobadas: %d\n", estadisticasRyPPrecisas.solucionesComprobadas);
    printf("  Nodos voraces adicionales: %d\n", estadisticasRyPPrecisas.nodosVorazAdicionales);
    printf("\n");


    int sumaBeneficioPrecisa = 0;

    for (int persona = 0; persona < n; persona++)
    {
        printf("\tLa persona %d realizará la tarea %d, con un beneficio de %2d\n", persona, solucionPrecisa.tupla[persona], matrizB[persona][solucionPrecisa.tupla[persona]]);
        sumaBeneficioPrecisa += matrizB[persona][solucionPrecisa.tupla[persona]];
    }
    printf("\n");
    printf("\tBeneficio total: %d\n", sumaBeneficioPrecisa);
    printf("\n");


    return 0;
}



