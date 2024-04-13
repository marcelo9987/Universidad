#pragma once

#include "comun.h"

enum TipoCuerpoCeleste
{
    tccNoEsUnCuerpoCeleste = 0,
    tccBovedaCelestial = 1,
    tccSol = 2,
    tccPlaneta = 3,
    tccSatelite = 4,
    tccAnillos = 10
};

enum EnumCuerpoCeleste
{
    VISTA_GENERAL_CENITAL = -2,
    VISTA_GENERAL = -1,

    // Planetas
    MERCURIO = 0,
    VENUS,
    TIERRA,
    MARTE,
    JUPITER,
    SATURNO,
    URANO,
    NEPTUNO,
    PLUTON,

    // El Sol
    SOL = 100,
    
    // La Bóveda celestial
    BOVEDA_CELESTIAL = 150,

    // Orbitan alrededor de la Tierra
    LUNA = 200,
    ISS,

    // Otras vistas
    LUNA_DESDE_LA_TIERRA = 300,
    ISS_DESDE_LA_TIERRA,
   
};

typedef struct PosicionCuerpoCeleste
{
    float radio;                // En unidades "normales"
    float distanciaAlPadre;     // En unidades "normales"
    float anguloRotacion;       // En grados sexagesimales
    float anguloTraslacion;     // En grados sexagesimales

    float posX;
    float posY;
    float posZ;

    GLuint numTexturaObjeto;    // Dato generado por glGenTextures(), a utilizar para cargar una textura con glBindTexture()
    GLuint numListaObjeto;      // Dato generado por glGenLists(), a utilizar para dibujar el objeto con glCallList()
} PosicionCuerpoCeleste;

typedef struct CuerpoCeleste
{
    enum EnumCuerpoCeleste quienSoy;
    char nombre[50];
    float radio;                // Comparado con el de la Tierra
    float distanciaMaximaAlSol; // En Unidades Astronómicas
    float periodoRotacion;      // Días terrestres
    float periodoTraslacion;    // Días terrestres
    char* rutaTextura;          // Ruta de la textura que aplicaremos a este cuperpo celeste, en caso de tenerla
    float color[3];             // RGB [0.0f, 1.0f]
    bool tieneAnillos;
    PosicionCuerpoCeleste* posicion;
    int numHijos;
    struct CuerpoCeleste* hijos;
} CuerpoCeleste;


#define K_NUM_PLANETAS 9
#define K_NUM_SATELITES_TERRESTRES 2


// --

extern CuerpoCeleste bovedaCelestial[1];

extern CuerpoCeleste sol[1];

extern CuerpoCeleste planetas[K_NUM_PLANETAS];

extern CuerpoCeleste satelitesTerrestres[K_NUM_SATELITES_TERRESTRES];

// --


// void actualizaDatosSol(CuerpoCeleste* sol);

/**
* @brief Actualiza los datos de un cuerpo celeste
* @param[in/out] cuerpoCeleste Cuerpo celeste a actualizar
*/
void actualizaCuerpoCeleste(CuerpoCeleste* cuerpoCeleste);

//void representaSol(CuerpoCeleste* sol, bool imprimirDatos);

/**
* @brief Representa un cuerpo celeste
* @param[in] cuerpoCeleste Cuerpo celeste a representar
*/
//void iluminaCuerpoCeleste(CuerpoCeleste* cuerpoCeleste, enum TipoCuerpoCeleste tipoCuerpoCeleste);
void representaCuerpoCeleste(CuerpoCeleste* cuerpoCeleste, enum TipoCuerpoCeleste tipoCuerpoCeleste);

//void representaSateliteTerrestre(CuerpoCeleste* unSateliteTerrestre, bool imprimirDatos);
