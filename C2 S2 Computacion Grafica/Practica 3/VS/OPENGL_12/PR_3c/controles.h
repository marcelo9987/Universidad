#pragma once

#include <stdbool.h>

typedef struct
{
    float alpha;            // Izquierda y derecha (Ángulos en radianes)
    float beta;             // Arriba y abajo (Ángulos en radianes)
    float distanciaCamara;   // Distancia de la cámara al origen;

} ConfiguracionCamara;

#define K_VELOCIDAD_SPD_ARRAY_SIZE 5


typedef struct
{
    int window_width;
    int window_height;
    int velocidad_segundosPorDia_posicionSeleccionada;
    bool mostrarOrbitas;
    float velocidad_framesPorSegundo;
    float factorEscaladoCuerposCelestes;
    float factorEscaladoDistancias;
    ConfiguracionCamara camaraPrincipal;
} ConfiguracionSistema;

extern ConfiguracionSistema cs;


void inicializaConfiguracionCamara();

void myCamara(char* detalleAccion);

void myTeclado(unsigned char tras, int x, int y);

void myTeclasEspeciales(int cursor, int x, int y);
