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


#define radianesAGrados(x) (x * 180.0 / M_PI)
#define gradosARadianes(x) (x * M_PI / 180.0)


extern ConfiguracionSistema cs;
