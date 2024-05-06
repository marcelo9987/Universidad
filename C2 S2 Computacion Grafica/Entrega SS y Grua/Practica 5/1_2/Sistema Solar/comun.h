#pragma once

#include <stdbool.h>
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

#include <glut.h>       //Inclusión de GLUT
#include <gl.h>      //Inclusión de GL
#include <glu.h>

#include <windows.h>    //Inclusión de variables de windows

#define _USE_MATH_DEFINES
#include <math.h>       //Inclusión de libreróas auxiliares


#include "controles.h"

/**
* @brief pasa de radianes a grados
* @param[in] x en radianes
* @return x en grados
*/
inline double radianesAGrados(double x) {
    return (x * 180.0 / M_PI);
}

/**
* @brief pasa de grados a radianes
* @param[in] x en grados
* @return x en radianes
*/
inline double gradosARadianes(double x) {
    return (x * M_PI / 180.0);
}

/**
* @brief Realiza la operación coseno de un ángulo en grados
* @param[in] x ángulo en grados
* @return cos(x) en radianes
*/
inline double cos360(double x) {
    return cos(gradosARadianes(x));
}

/**
* @brief Realiza la operación seno de un ángulo en grados
* @param[in] x ángulo en grados
* @return sin(x) en radianes
*/
inline double sin360(double x) {
    return sin(gradosARadianes(x));
}

// --

typedef struct ConfiguracionCamara
{
    double alpha;            // Izquierda y derecha (ángulos en radianes)
    double beta;             // Arriba y abajo (ángulos en radianes)
    double zoomCamara;  // Distancia de la cámara al origen (algo así como la inversa del zoom)

    bool mostrarOrbitas;
} ConfiguracionCamara;

typedef struct
{
    int window_width;
    int window_height;

    double chronos_diaActualmenteSimulado;
    int chronos_segundosRealesPorDiaSimulado_posicionSeleccionada;
    double chronos_framesPorSegundo;

    double factorEscaladoCuerposCelestes;
    double factorEscaladoDistancias;

    enum EnumCuerpoCeleste visualizacionPrincipal;

    ConfiguracionCamara camaraPrincipal;
    ConfiguracionCamara camarasSecundarias[4];

    bool mostrarEasterEggs;
    bool mostrarEjes;
    bool mostrarMonitores;
    bool mostrarTextos;
    bool seMuestraAyuda;

    bool solEncendido;
    int potenciaIluminacion;

} ConfiguracionSistema;

extern ConfiguracionSistema cs;

//extern HANDLE mutexVelocidad;

typedef struct ConfiguracionVelocidadSimulacion
{
    double segundosRealesPorDiaSimulado;  // 24.0f
    char *nombreConfiguracion;          // 1 hora por segundo
} ConfiguracionVelocidadSimulacion;