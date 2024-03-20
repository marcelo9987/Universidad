#pragma once

#include <glut.h>
#include <GL/gl.h>
#include <GL/glu.h>

typedef struct
{
    char nombre[50];
    float radio;
    float distanciaMaximaAlSol;
    float periodoRotacion;
    float periodoTranslacion;
    float anguloTaslacionActual;
    float color[3];
} planeta;

void actualizaDatosUnPlaneta(planeta* unPlaneta);

void representaUnPlaneta(planeta* unPlaneta);

