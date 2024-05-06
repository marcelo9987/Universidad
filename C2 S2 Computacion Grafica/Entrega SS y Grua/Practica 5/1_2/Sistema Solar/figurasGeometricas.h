#pragma once

//#define O_ORBITASOLAR 1
//
//#define O_ORBITAPLANETARIA 2
//
//#define O_ANILLOS 4


/**
* @brief Dibuja los ejes
*/
void myEjes();

/**
* @brief Dibuja una elipse
* @param[in] x coordenada x del centro
* @param[in] y coordenada y del centro
* @param[in] a semi-eje mayor
* @param[in] b semi-eje menor
* @param[in] segments número de segmentos
*/
void myElipse(GLfloat x, GLfloat y, GLfloat a, GLfloat b, int segments, enum TipoCuerpoCeleste tipoCuerpoCeleste /*, int32_t flags*/);

/**
* @brief Dibuja una estrella (puntual)
*/
//void myEstrella(GLfloat x, GLfloat y, GLfloat z);

void mySolidCube(GLdouble size);

void myReverseSolidCube(GLdouble size);

/**
* @brief Dibuja una esfera
*/
void myEsfera();

extern void myISS();
