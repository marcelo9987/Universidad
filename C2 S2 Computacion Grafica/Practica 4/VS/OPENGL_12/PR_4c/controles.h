#pragma once

#include "comun.h"

typedef struct
{
    float alpha;            // Izquierda y derecha (Ángulos en radianes)
    float beta;             // Arriba y abajo (Ángulos en radianes)
    float distanciaCamara;  // Distancia de la cámara al origen;
    
    bool mostrarOrbitas;
} ConfiguracionCamara;

#define K_VELOCIDAD_SPD_ARRAY_SIZE 5

extern const float K_VELOCIDAD_SPD_ARRAY[K_VELOCIDAD_SPD_ARRAY_SIZE];


typedef struct
{
    int window_width;
    int window_height;
//    bool mostrarOrbitas;

    float chronos_diaActualmenteSimulado;
    int chronos_segundosRealesPorDiaSimulado_posicionSeleccionada;
    float chronos_framesPorSegundo;
    
    float factorEscaladoCuerposCelestes;
    float factorEscaladoDistancias;

    enum EnumCuerpoCeleste visualizacionPrincipal;

    ConfiguracionCamara camaraPrincipal;
} ConfiguracionSistema;

extern ConfiguracionSistema cs;



void inicializaConfiguracionCamara();

void myChangeSize(GLint newWidth, GLint newHeight);

void myCamaraVistaGeneral(char* detalleAccion);
void myCamaraDesdeLaTierraHaciaElSol(char* detalleAccion);
void myCamaraDesdeLaTierraHaciaOtroPlaneta(char* detalleAccion, enum EnumCuerpoCeleste haciaQueCuerpoCeleste);
void myCamaraHaciaLaTierra(char* detalleAccion, enum EnumCuerpoCeleste desdeQueCuerpoCeleste);
void myCamaraHaciaUnSateliteTerrestre(char* detalleAccion, enum EnumCuerpoCeleste haciaQueCuerpoCeleste);

//void myCamaras(char* detalleAccion);

void myTeclado(unsigned char tras, int x, int y);

void myTeclasEspeciales(int cursor, int x, int y);

void iniciaMenu();
