//
// Created by imarc on 02/12/2023.
//
#pragma once


#define n 6

#define N n

#define ASIGNACION_NO_VALIDA (-1)


struct Estadisticas_backtracking
{
    int nodosArbolGenerados;
    int solucionesComprobadas;

    int pasosTotales;

    int pasosFuncionBacktracking;
    int pasosFuncionGenerar;
    int pasosFuncionCriterio;
    int pasosFuncionSolucion;
    int pasosFuncionMasHermanos;
    int pasosFuncionRetroceder;
};
