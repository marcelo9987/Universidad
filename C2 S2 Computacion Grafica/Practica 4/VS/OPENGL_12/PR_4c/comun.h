#pragma once

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include <glut.h>       //Inclusión de GLUT
#include <GL/gl.h>      //Inclusión de GL
#include <GL/glu.h>

#include <windows.h>    //Inclusión de variables de windows

#define _USE_MATH_DEFINES
#include <math.h>       //Inclusión de librerías auxiliares


#include "controles.h"

/**
* @brief pasa de radianes a grados
* @param[in] x en radianes
* @return x en grados
*/
#define radianesAGrados(x) (x * 180.0 / M_PI)

/**
* @brief pasa de grados a radianes
* @param[in] x en grados
* @return x en radianes
*/
#define gradosARadianes(x) (x * M_PI / 180.0)

/**
* @brief Realiza la operación coseno de un ángulo en grados
* @param[in] x ángulo en grados
* @return cos(x) en radianes
*/
#define cosf360(x) cosf(gradosARadianes(x))

/**
* @brief Realiza la operación seno de un ángulo en grados
* @param[in] x ángulo en grados
* @return sin(x) en radianes
*/
#define sinf360(x) sinf(gradosARadianes(x))
