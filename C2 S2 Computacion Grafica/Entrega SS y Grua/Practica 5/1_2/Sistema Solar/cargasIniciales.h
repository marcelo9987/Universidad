#pragma once

#include "comun.h"
#include "sistemaSolar.h"



/**
* @brief Inicializa la configuraci�n de un cuerpo celeste
* @param[in] cuerpoCeleste Cuerpo celeste a inicializar
*/
void inicializaCuerpoCeleste(CuerpoCeleste* cuerpoCeleste);

/**
* @brief Inicializa la configuraci�n del sistema solar
*/
void inicializaConfiguracionSistema(bool primeraVez);

/**
* @brief Inicializa la configuraci�n de la c�mara
* @param[in] cuerpoCeleste Cuerpo celeste a inicializar
*/
void inicializaConfiguracionCamaras();

