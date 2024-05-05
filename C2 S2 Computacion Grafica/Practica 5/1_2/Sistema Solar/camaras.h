#pragma once

#include "comun.h"

//Cámaras varias para el sistema solar

void myCamaraVistaGeneral(struct ConfiguracionCamara* configuracionCamara);

void myCamaraDesdeLaTierraHaciaElSol(struct ConfiguracionCamara* configuracionCamara);

void myCamaraDesdeLaTierraHaciaOtroPlaneta(struct ConfiguracionCamara* configuracionCamara, enum EnumCuerpoCeleste haciaQueCuerpoCeleste);

void myCamaraHaciaLaTierra(struct ConfiguracionCamara* configuracionCamara, enum EnumCuerpoCeleste desdeQueCuerpoCeleste);

void myCamaraHaciaUnSateliteTerrestre(struct ConfiguracionCamara* configuracionCamara, enum EnumCuerpoCeleste haciaQueCuerpoCeleste);

//void myCamaras();

struct ConfiguracionCamara;

void seleccionarVistaCamara(struct ConfiguracionCamara * configuracionCamara, enum EnumCuerpoCeleste visualizacionSeleccionada);

void seleccionadaDesdeMenuVistaCamaraVisualizacionPrincipal(int opcionSeleccionada);

void seleccionaCamara(struct ConfiguracionCamara* configuracionCamara, enum EnumCuerpoCeleste visualizacionSeleccionada);