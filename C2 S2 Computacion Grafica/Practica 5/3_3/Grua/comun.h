#pragma once

#define _USE_MATH_DEFINES
#include <math.h>       //Inclusión de libreróas auxiliares

#include <glad.h>
#include <glfw3.h>

//Movimiento
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>


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

typedef struct {
    float px, py, pz;           //posicion inicial
    float angulo_trans;         //anguloPlano giro x
    float angulo_trans_2;       //anguloPlano giro z
    float sx, sy, sz;           //escalado en los ejes
    unsigned int listarender;   //VAO
    float colx, coly, colz;     //Color
    int articulacion;
    unsigned int textura;
    int isbase;
} ElementoGrua;


// --

// Texturas
extern unsigned int texturaPiscina[16];
extern unsigned int texturaSuelo;
extern unsigned int texturaEstadio;

// Animacion piscia
extern int piscina_instante;
extern int piscina_contador;

// Elementos de la grúa
extern ElementoGrua base;
extern ElementoGrua baseA1;
extern ElementoGrua base1;
extern ElementoGrua baseA2;
extern ElementoGrua base2;
extern ElementoGrua foco;

// Settings
extern unsigned int SCR_WIDTH;
extern unsigned int SCR_HEIGHT;

// My Shader
extern GLuint myShaderProgram;

//Angulo plano
extern float anguloPlano;

//VAOs
extern unsigned int VAO;
extern unsigned int VAOEsfera;
extern unsigned int VAOCubo;
extern unsigned int VAOCuboDestapado;
extern unsigned int VAOCuadrado;

//Variables para el control de la cámara
extern int camaraSeleccionada;

//Variables para el moviminto de la grúa
extern float velocidadGrua;
// extern float anguloGiroGrua;
extern float gradosSpotCutoff;
