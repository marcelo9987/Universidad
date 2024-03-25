#include "controles.h"

#include "sistemaSolar.h"

#define _USE_MATH_DEFINES

#include <math.h>
#include <stdio.h>


const float K_VELOCIDAD_SPD_ARRAY[K_VELOCIDAD_SPD_ARRAY_SIZE] = {
    INFINITY,       // detenido
    24.0f,          // 1 hora por segundo
    1.0f,           // 1 día por segundo
    1.0f / 7.0f,    // 1 semana por segundo
    12.0f / 365.26f // 1 mes por segundo
};


void inicializaConfiguracionSistema()
{
    cs.window_width = 1200;
    cs.window_height = 800;
    cs.velocidad_segundosPorDia_posicionSeleccionada = 1;
    cs.velocidad_framesPorSegundo = 24.0f;
    cs.factorEscaladoCuerposCelestes = 10.0f;
    cs.factorEscaladoDistancias = 20.0f;
}

// --

CuerpoCeleste satelitesTerrestres[K_NUM_SATELITES_TERRESTRES] = {
{"Luna",              0.27, /* */  0.00257,/**/  27.32,/*   */ 27.32,       /**/ {0.7, 0.7, 0.7}, /**/ 0.0,    /**/ 0.0, /**/                         0, /**/ NULL                  /**/ },
{"ISS",         /* */ 0.10, /* */   0.00001,  /*  */  0.0f, /**/  1.0f / 24.0f,       /**/ {0.0, 0.1, 0.0}, /**/ 0.0,    /**/ 0.0, /**/                         0, /**/ NULL                  /**/ }
};

CuerpoCeleste planetas[K_NUM_PLANETAS] = {
    //                                 distancia      periodo        periodo                          anguloRota  anguloTrasla
    // nombre            radio       MaximaAlSol     Rotacion      Translacion            color       cionActual   cionActual                         numHijos  hijos
    {"Mercurio",    /* */ 0.38, /*  */   0.39, /* */   58.65, /*   */ 87.97,    /**/ {0.7, 0.7, 0.7}, /**/ 0.0,    /**/ 0.0, /**/                          0, /**/ NULL                  /**/ },
    {"Venus",       /* */ 0.95, /*  */   0.72, /**/    243.02, /*  */ 224.70,   /**/ {0.7, 0.7, 1.0}, /**/ 0.0,    /**/ 0.0, /**/                          0, /**/ NULL                  /**/ },
    {"Tierra",      /* */ 1.00, /*  */   1.00, /*  */  1.00, /*  */   365.26,   /**/ {0.0, 0.0, 1.0}, /**/ 0.0,    /**/ 0.0, /**/ K_NUM_SATELITES_TERRESTRES, /**/ satelitesTerrestres   /**/ },
    {"Marte",       /* */ 0.53, /*  */   1.52, /*  */  1.03, /*  */   686.98,   /**/ {1.0, 0.0, 0.0}, /**/ 0.0,    /**/ 0.0, /**/                          0, /**/ NULL                  /**/ },
    {"Jupiter",     /**/  11.21, /*  */  5.20, /*  */  0.41, /* */    4332.59,  /**/ {0.7, 0.7, 0.0}, /**/ 0.0,    /**/ 0.0, /**/                          0, /**/ NULL                  /**/ },
    {"Saturno",     /* */ 9.45, /*  */   9.58, /*  */  0.45, /**/     10759.22, /**/ {0.0, 0.0, 1.0}, /**/ 0.0,    /**/ 0.0, /**/                          0, /**/ NULL                  /**/ },
    {"Urano",       /* */ 4.01, /* */    19.22, /*  */ 0.72, /**/     30685.40, /**/ {0.0, 0.0, 1.0}, /**/ 0.0,    /**/ 0.0, /**/                          0, /**/ NULL                  /**/ },
    {"Neptuno",     /* */ 3.88, /* */    30.05, /*  */ 0.67, /**/     60189.00, /**/ {0.0, 0.0, 1.0}, /**/ 0.0,    /**/ 0.0, /**/                          0, /**/ NULL                  /**/ },
    {"Pluton",      /* */ 0.18, /* */    39.48, /*  */ 6.39, /**/     90560.00, /**/ {0.0, 0.0, 1.0}, /**/ 0.0,    /**/ 0.0, /**/                          0, /**/ NULL                  /**/ }
};

CuerpoCeleste sol =
{ "Sol",        /**/109.00, /*  */   0.0, /*  */  0.0, /*    */   0.0,        /**/ {1.0, 1.0, 0.0}, /**/ 0.0,    /**/ 0.0, /**/             K_NUM_PLANETAS, /* */ planetas             /**/ };


// --

extern float fAngulo;

int myEsfera();

// --

void myEjes()
{
    // Eje X
    glColor3f(1.0f, 0.0f, 0.0f);    // Red
    //  glColor3f(0.0f, 0.0f, 1.0f);    // Blue
    glBegin(GL_LINES);
    {
        glVertex3f(0.0f, 0.0f, 0.0f);
        glVertex3f(10.0f, 0.0f, 0.0f);
    }
    glEnd();

    // Eje Y
    glColor3f(0.0f, 1.0f, 0.0f);    // Green
    //  glColor3f(1.0f, 0.0f, 0.0f);    // Red
    glBegin(GL_LINES);
    {
        glVertex3f(0.0f, 0.0f, 0.0f);
        glVertex3f(0.0f, 10.0f, 0.0f);
    }
    glEnd();

    // Eje Z
    glColor3f(0.0f, 0.0f, 1.0f);    // Blue
    //  glColor3f(0.0f, 1.0f, 0.0f);    // Green
    glBegin(GL_LINES);
    {
        glVertex3f(0.0f, 0.0f, 0.0f);
        glVertex3f(0.0f, 0.0f, 10.0f);
    }
    glEnd();

    // Diagonal - segmento (0,0,0) - (1,1,1)
    glColor3f(1.0f, 1.0f, 1.0f);    // White
    glBegin(GL_LINES);
    {
        glVertex3f(0.0f, 0.0f, 0.0f);
        glVertex3f(0.35f, 0.35f, 0.35f);
    }
    glEnd();
}

// --

void myEllipse(float cx, float cy, float rx, float ry, int num_segments)
{
    float theta = 2.0 * M_PI / (float)num_segments;
    float c = cosf(theta);//precalculate the sine and cosine
    float s = sinf(theta);
    float t;

    float x = 1.0;//we start at angle = 0 
    float y = 0.0;

    // https://www.mathwarehouse.com/ellipse/focus-of-ellipse.php
    float focus1 = sqrt(rx * rx - ry * ry);

    glBegin(GL_LINE_LOOP);
    for (int ii = 0; ii < num_segments; ii++)
    {
        //apply radius and offset
        glVertex3f(x * rx + cx + focus1 / 2.0, 0.0, y * ry + cy);//output vertex 

        //apply the rotation matrix
        t = x;
        x = c * x - s * y;
        y = s * t + c * y;
    }
    glEnd();
}

// --

//void actualizaDatosSol(CuerpoCeleste* sol)
//{
//    /*
//    sol->anguloTaslacionActual += 365.0f / sol->periodoTraslacion;
//
//    if (cuerpoCeleste->anguloTaslacionActual > 360.0f)
//    {
//        cuerpoCeleste->anguloTaslacionActual -= 360.0f;
//    }
//    */
//}

void actualizaDatosCuerpoCeleste(CuerpoCeleste* cuerpoCeleste)
{
    float velocidad_segundosPorDia = K_VELOCIDAD_SPD_ARRAY[cs.velocidad_segundosPorDia_posicionSeleccionada];

    if (cuerpoCeleste->periodoTraslacion > 0.0f && cs.velocidad_segundosPorDia_posicionSeleccionada != 0)
    {

        float deltaTraslacion = 360.0f / (cuerpoCeleste->periodoTraslacion * velocidad_segundosPorDia * cs.velocidad_framesPorSegundo);

        cuerpoCeleste->anguloTraslacionActual += deltaTraslacion;

        if (cuerpoCeleste->anguloTraslacionActual > 360.0f)
        {
            cuerpoCeleste->anguloTraslacionActual -= 360.0f;
        }

    }

    // --

    if (cuerpoCeleste->periodoRotacion > 0.0f && cs.velocidad_segundosPorDia_posicionSeleccionada != 0)
    {

        float deltaRotacion = 360.0f / (cuerpoCeleste->periodoRotacion * velocidad_segundosPorDia * cs.velocidad_framesPorSegundo);

        cuerpoCeleste->anguloRotacionActual += deltaRotacion;

        if (cuerpoCeleste->anguloRotacionActual > 360.0f)
        {
            cuerpoCeleste->anguloRotacionActual -= 360.0f;
        }

    }

    if (cuerpoCeleste->numHijos > 0)
    {

        for (int pos = 0; pos < cuerpoCeleste->numHijos; pos++)
        {
            actualizaDatosCuerpoCeleste(&cuerpoCeleste->hijos[pos]);
        }
    }

}

//void representaSol(CuerpoCeleste *cuerpoCeleste, bool imprimirDatos)
//{
//    float radioCuepoCeleste = log10(cs.factorEscaladoCuerposCelestes * cuerpoCeleste->radio);
//
//    float distanciaAlCentro = 0.0f;
//
//    glPushMatrix();
//
//    {
//        glColor3f(cuerpoCeleste->color[0], cuerpoCeleste->color[1], cuerpoCeleste->color[2]);
//
//
//        // Lo hago más pequeño
//        // glScalef(radioCuepoCeleste, radioCuepoCeleste, radioCuepoCeleste);
//
//        //      glTranslatef(0.0f, 0.0f, 0.0f);
//
//        // myEsfera();
//        glutWireCube(radioCuepoCeleste);
//        //glutSolidSphere(radioCuepoCeleste, 20, 20);
//        // glutWireSphere(radioCuepoCeleste, 20, 20);
//
//    }
//
//    glPopMatrix();
//
//
//    if (imprimirDatos)
//    {
//        printf("%20s - tamaño: %2.5f - distancia al centro: %2.5f\n", cuerpoCeleste->nombre, radioCuepoCeleste, distanciaAlCentro);
//    }
//
//    if (cuerpoCeleste->numHijos > 0)
//    {
//
//        for (int pos = 0; pos < cuerpoCeleste->numHijos; pos++)
//        {
//            representaCuerpoCeleste(&cuerpoCeleste->hijos[pos], imprimirDatos);
//        }
//    }
//}

void representaCuerpoCeleste(CuerpoCeleste* cuerpoCeleste, bool imprimirDatos)
{
    float radioCuepoCeleste = log10(cs.factorEscaladoCuerposCelestes * cuerpoCeleste->radio);

    if (radioCuepoCeleste < 0.2f)
    {
        radioCuepoCeleste = 0.2f;
    }

    // --

    float distanciaAlCentro = 0.0f;

    if (cuerpoCeleste->distanciaMaximaAlSol > 0.0f)
    {

        distanciaAlCentro = cs.factorEscaladoDistancias * sqrt(cuerpoCeleste->distanciaMaximaAlSol);

        if (distanciaAlCentro < 0.2f)
        {
            distanciaAlCentro = 0.2f;
        }

    }

    // --

    glColor3f(cuerpoCeleste->color[0], cuerpoCeleste->color[1], cuerpoCeleste->color[2]);

    /*

    glPushMatrix();

    {
        glRotatef(90.0f, 1.0f, 0.0f, 0.0);

        glutWireTorus(radioCuepoCeleste/24.0f, distanciaAlCentro,  3, 360);

    }

    glPopMatrix();

    */

    // --

    glPushMatrix();

    {
        if (distanciaAlCentro > 0.0f)
        {
            //  myEllipse(0.0f, 0.0f, distanciaAlCentro, distanciaAlCentro / 2.0, 100);
            myEllipse(0.0f, 0.0f, distanciaAlCentro, distanciaAlCentro, 360);

        }

        if (cuerpoCeleste->periodoTraslacion > 0.0f)
        {
            glRotatef(cuerpoCeleste->anguloTraslacionActual, 0.0f, 1.0f, 0.0);
        }

        if (distanciaAlCentro > 0.0f)
        {
            glTranslatef(distanciaAlCentro, 0.0f, 0.0f);
        }

        if (cuerpoCeleste->periodoRotacion > 0.0f)
        {
            glRotatef(cuerpoCeleste->anguloRotacionActual, 0.0f, 5.0f, 0.0);
        }

        glutWireCube(radioCuepoCeleste);

        myEjes();

        //myEsfera();
        //glutSolidSphere(radioCuepoCeleste, 20, 20);
        // glutWireSphere(radioCuepoCeleste, 20, 20);

        if (cuerpoCeleste->numHijos > 0)
        {

            for (int pos = 0; pos < cuerpoCeleste->numHijos; pos++)
            {
                representaCuerpoCeleste(&cuerpoCeleste->hijos[pos], imprimirDatos);
            }
        }

    }

    glPopMatrix();


    if (imprimirDatos)
    {
        printf("%20s - tamaño: %2.5f - distancia al centro: %2.5f\n", cuerpoCeleste->nombre, radioCuepoCeleste, distanciaAlCentro);
    }

}
