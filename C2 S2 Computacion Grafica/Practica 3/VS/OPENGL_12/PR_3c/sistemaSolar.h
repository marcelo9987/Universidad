#pragma once

#include <stdbool.h>

#include <glut.h>
#include <GL/gl.h>
#include <GL/glu.h>

// --

typedef struct CuerpoCeleste
{
    char nombre[50];
    float radio;                    // Comparado con el de la Tierra
    float distanciaMaximaAlSol;     // En Unidades Astronómicas
    float periodoRotacion;          // Días terrestres
    float periodoTraslacion;        // Días terrestres
    float color[3];                 // RGB [0.0f, 1.0f]
    float anguloRotacionActual;     // En grados sexagesimales
    float anguloTraslacionActual;   // En grados sexagesimales
    int numHijos;
    struct CuerpoCeleste *hijos;
} CuerpoCeleste;

#define K_NUM_PLANETAS 9
#define K_NUM_SATELITES_TERRESTRES 2

// --

extern CuerpoCeleste sol;

extern CuerpoCeleste planetas[K_NUM_PLANETAS];

extern CuerpoCeleste satelitesTerrestres[K_NUM_SATELITES_TERRESTRES];

// --

void inicializaConfiguracionSistema();

// void actualizaDatosSol(CuerpoCeleste* sol);

void actualizaDatosCuerpoCeleste(CuerpoCeleste* cuerpoCeleste);

//void representaSol(CuerpoCeleste* sol, bool imprimirDatos);

void representaCuerpoCeleste(CuerpoCeleste* cuerpoCeleste, bool imprimirDatos);

//void representaSateliteTerrestre(CuerpoCeleste* unSateliteTerrestre, bool imprimirDatos);
