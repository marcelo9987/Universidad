#pragma once

#include <stdbool.h>

#include <glut.h>
#include <GL/gl.h>
#include <GL/glu.h>

typedef struct
{
    char nombre[50];
    float radio;                    // Comparado con el de la Tierra
    float distanciaMaximaAlSol;     // En Unidades Astronómicas
    float periodoRotacion;          // Días terrestres
    float periodoTraslacion;        // Días terrestres
    float color[3];                 // RGB [0.0f, 1.0f]
    float anguloRotacionActual;     // En grados sexagesimales
    float anguloTraslacionActual;   // En grados sexagesimales
} CuerpoCeleste;


void inicializaConfiguracionSistema();

void actualizaDatosSol(CuerpoCeleste* sol);

void actualizaDatosPlaneta(CuerpoCeleste* unPlaneta);

void representaSol(CuerpoCeleste* sol, bool imprimirDatos);

void representaPlaneta(CuerpoCeleste* unPlaneta, bool imprimirDatos);

//void representaSateliteTerrestre(CuerpoCeleste* unSateliteTerrestre, bool imprimirDatos);
