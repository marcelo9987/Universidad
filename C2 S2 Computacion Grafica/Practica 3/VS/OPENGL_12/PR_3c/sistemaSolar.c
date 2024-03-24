#include "sistemaSolar.h"

#define _USE_MATH_DEFINES

#include <math.h>
#include <stdio.h>

typedef struct
{
    float factorEscaladoCuerposCelestes;
    float factorEscaladoDistancias;
} ConfiguracionSistema;

ConfiguracionSistema configuracionSistema;

void inicializaConfiguracionSistema()
{
    configuracionSistema.factorEscaladoCuerposCelestes = 10.0f;
    configuracionSistema.factorEscaladoDistancias = 20.0f;
}

// --

CuerpoCeleste sol =
{ "Sol",        /**/109.00, /*  */ 0.00, /*  */ 0.00, /*    */ 0.00, /**/ {1.0, 1.0, 0.0}, /**/ 0.0,    /**/ 0.0 };


CuerpoCeleste planetas[9] = {
    //                                   distancia    periodo     periodo                          anguloRota  anguloTrasla
    //   nombre               radio    MaximaAlSol   Rotacion   Translacion            color       cionActual   cionActual
        {"Mercurio",    /* */ 0.38, /*  */ 0.39, /* */ 58.65, /*   */ 87.97, /**/ {0.7, 0.7, 0.7}, /**/ 0.0,    /**/ 0.0 },
        {"Venus",       /* */ 0.95, /*  */ 0.72, /**/ 243.02, /*  */ 224.70, /**/ {0.7, 0.7, 1.0}, /**/ 0.0,    /**/ 0.0 },
        {"Tierra",      /* */ 1.00, /*  */ 1.00, /*  */ 1.00, /*  */ 365.26, /**/ {0.0, 0.0, 1.0}, /**/ 0.0,    /**/ 0.0 },
        {"Marte",       /* */ 0.53, /*  */ 1.52, /*  */ 1.03, /*  */ 686.98, /**/ {1.0, 0.0, 0.0}, /**/ 0.0,    /**/ 0.0 },
        {"Jupiter",     /**/ 11.21, /*  */ 5.20, /*  */ 0.41, /* */ 4332.59, /**/ {0.7, 0.7, 0.0}, /**/ 0.0,    /**/ 0.0 },
        {"Saturno",     /* */ 9.45, /*  */ 9.58, /*  */ 0.45, /**/ 10759.22, /**/ {0.0, 0.0, 1.0}, /**/ 0.0,    /**/ 0.0 },
        {"Urano",       /* */ 4.01, /* */ 19.22, /*  */ 0.72, /**/ 30685.40, /**/ {0.0, 0.0, 1.0}, /**/ 0.0,    /**/ 0.0 },
        {"Neptuno",     /* */ 3.88, /* */ 30.05, /*  */ 0.67, /**/ 60189.00, /**/ {0.0, 0.0, 1.0}, /**/ 0.0,    /**/ 0.0 },
        {"Pluton",      /* */ 0.18, /* */ 39.48, /*  */ 6.39, /**/ 90560.00, /**/ {0.0, 0.0, 1.0}, /**/ 0.0,    /**/ 0.0 }
};

CuerpoCeleste satelitesTerrestres[] = {
        {"Luna",        /* */ 0.27, /* */  0.00257,/**/ 27.32,/*   */ 27.32, /**/ {0.7, 0.7, 0.7}, /**/ 0.0,    /**/ 0.0 },
        {"ISS",         /* */ 0.10, /* */  0.0,  /*  */  0.0, /*    */ 0.0,  /**/ {0.7, 0.7, 0.7}, /**/ 0.0,    /**/ 0.0 }
};

// --

extern float fAngulo;

int myEsfera();

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

void actualizaDatosSol(CuerpoCeleste* sol)
{
    /*
    sol->anguloTaslacionActual += 365.0f / sol->periodoTraslacion;

    if (unPlaneta->anguloTaslacionActual > 360.0f)
    {
        unPlaneta->anguloTaslacionActual -= 360.0f;
    }
    */
}

void actualizaDatosPlaneta(CuerpoCeleste* unPlaneta)
{
    float deltaTraslacion = 360.0f / unPlaneta->periodoTraslacion;

    unPlaneta->anguloTraslacionActual += deltaTraslacion;

    if (unPlaneta->anguloTraslacionActual > 360.0f)
    {
        unPlaneta->anguloTraslacionActual -= 360.0f;
    }

    // --
    
    float deltaRotacion = 360.0f / unPlaneta->periodoRotacion;
    
    unPlaneta->anguloRotacionActual += deltaRotacion;

    if (unPlaneta->anguloRotacionActual > 360.0f)
    {
        unPlaneta->anguloRotacionActual -= 360.0f;
    }

}

void representaSol(CuerpoCeleste* cuerpoCeleste, bool imprimirDatos)
{
    float radioCuepoCeleste = log10(configuracionSistema.factorEscaladoCuerposCelestes * cuerpoCeleste->radio);

    float distanciaAlCentro = 0.0f;

    glPushMatrix();

    {
        glColor3f(cuerpoCeleste->color[0], cuerpoCeleste->color[1], cuerpoCeleste->color[2]);


        // Lo hago más pequeño
        // glScalef(radioCuepoCeleste, radioCuepoCeleste, radioCuepoCeleste);

        //      glTranslatef(0.0f, 0.0f, 0.0f);

                // myEsfera();
        glutWireCube(radioCuepoCeleste);
        //glutSolidSphere(radioCuepoCeleste, 20, 20);
        // glutWireSphere(radioCuepoCeleste, 20, 20);

    }

    glPopMatrix();


    if (imprimirDatos)
    {
        printf("%20s - tamaño: %2.5f - distancia al centro: %2.5f\n", cuerpoCeleste->nombre, radioCuepoCeleste, distanciaAlCentro);
    }
}

void representaPlaneta(CuerpoCeleste* unPlaneta, bool imprimirDatos)
{
    float radioCuepoCeleste = log10(configuracionSistema.factorEscaladoCuerposCelestes * unPlaneta->radio);

    float distanciaAlCentro = configuracionSistema.factorEscaladoDistancias * sqrt(unPlaneta->distanciaMaximaAlSol);

    glColor3f(unPlaneta->color[0], unPlaneta->color[1], unPlaneta->color[2]);

    //  glutSolidTorus(radio, radio+0.1, 10, 10);
    //  myEllipse(0.0f, 0.0f, distanciaAlCentro, distanciaAlCentro / 2.0, 100);
    myEllipse(0.0f, 0.0f, distanciaAlCentro, distanciaAlCentro, 100);

    glPushMatrix();

    {

        //        glRotatef(unPlaneta->anguloTraslacionActual, 0.0f, 5.0f, 0.0);
                //   glRotatef(fAngulo, 0.0f, 5.0f, 0.0);

                //if(factorEscaladoPlaneta < 0.01)
                //{
                //    factorEscaladoPlaneta = 0.01;
                //}
                //else if(factorEscaladoPlaneta > 0.1)
                //{
                //    factorEscaladoPlaneta = 0.1;
                //}

                //La hago mas pequeña
                // glScalef(factorEscalado, factorEscalado, factorEscalado);

                //glTranslatef(sqrt(unPlaneta->distanciaMaximaAlSol)*10.0f, 0.0f, 0.0f);
        glTranslatef(distanciaAlCentro, 0.0f, 0.0f);

        glRotatef(unPlaneta->anguloRotacionActual, 0.0f, 5.0f, 0.0);

        glutWireCube(radioCuepoCeleste);
        //myEsfera();
        //glutSolidSphere(radioCuepoCeleste, 20, 20);
        // glutWireSphere(radioCuepoCeleste, 20, 20);

    }

    glPopMatrix();


    if (imprimirDatos)
    {
        printf("%20s - tamaño: %2.5f - distancia al centro: %2.5f\n", unPlaneta->nombre, radioCuepoCeleste, distanciaAlCentro);
    }

}
