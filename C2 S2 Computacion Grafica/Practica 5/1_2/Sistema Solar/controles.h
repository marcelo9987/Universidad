#pragma once

#include "comun.h"
#include "camaras.h"


#define K_VELOCIDAD_SPD_ARRAY_SIZE 9

extern const struct ConfiguracionVelocidadSimulacion K_VELOCIDAD_SPD_ARRAY[K_VELOCIDAD_SPD_ARRAY_SIZE];

/**
* @brief aplica cambios para el reescalado de la ventana
* @param[in] newWidth nuevo ancho
* @param[in] newHeight nuevo alto
*/
void myChangeSize(GLint newWidth, GLint newHeight);

void myTeclado(unsigned char tras, int x, int y);

void myTeclasEspeciales(int cursor, int x, int y);

void iniciaMenu();

void imprimeTexto(int x, int y, float r, float g, float b, void* font, char* texto);