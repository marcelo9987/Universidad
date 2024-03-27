#pragma once

#include <stdbool.h>

typedef struct
{
    float alpha;            // Izquierda y derecha (Ángulos en radianes)
    float beta;             // Arriba y abajo (Ángulos en radianes)
    float distanciaCamara;   // Distancia de la cámara al origen;

} ConfiguracionCamara;

#define K_VELOCIDAD_SPD_ARRAY_SIZE 5

extern const float K_VELOCIDAD_SPD_ARRAY[K_VELOCIDAD_SPD_ARRAY_SIZE];


typedef struct
{
    int window_width;
    int window_height;
    bool mostrarOrbitas;

    float chronos_diaActualmenteSimulado;
    int chronos_segundosRealesPorDiaSimulado_posicionSeleccionada;
    float chronos_framesPorSegundo;
    
    float factorEscaladoCuerposCelestes;
    float factorEscaladoDistancias;
    ConfiguracionCamara camaraPrincipal;
} ConfiguracionSistema;

extern ConfiguracionSistema cs;


void inicializaConfiguracionCamara();

void myCamara(char* detalleAccion);

void myTeclado(unsigned char tras, int x, int y);

void myTeclasEspeciales(int cursor, int x, int y);

void iniciaMenu();
