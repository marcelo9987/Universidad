#include "controles.h"

#include "sistemaSolar.h"

#define STB_IMAGE_IMPLEMENTATION    
#include "stb_image.h"

#define _USE_MATH_DEFINES

#include <math.h>
#include <stdio.h>



int cargarTextura(char* nombre)
{
    int textura;
    glGenTextures(1, &textura);
    glBindTexture(GL_TEXTURE_2D, textura);

    int width, height, nrChannels;
    unsigned char* data = stbi_load("texturas/sol.bmp", &width, &height, &nrChannels, 0);
    if (data == NULL)
    {
        printf("Error al cargar la textura sol.bmp\n");
    }
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB,
        GL_UNSIGNED_BYTE, data);
    //Parametros
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    stbi_image_free(data);
    return (textura);
}


void inicializaConfiguracionSistema()
{
    cs.window_width = 1200;
    cs.window_height = 800;
    cs.mostrarOrbitas = true;

    cs.chronos_diaActualmenteSimulado = 0.0f;
    cs.chronos_segundosRealesPorDiaSimulado_posicionSeleccionada = 1;
    cs.chronos_framesPorSegundo = 24.0f;

    cs.factorEscaladoCuerposCelestes = 10.0f;
    cs.factorEscaladoDistancias = 20.0f;
}

// --

PosicionCuerpoCeleste posicionSatTerr[K_NUM_SATELITES_TERRESTRES];
PosicionCuerpoCeleste posicionPlanetas[K_NUM_PLANETAS];
PosicionCuerpoCeleste posicionSol; // = { 0.0f, 0.0f };


CuerpoCeleste satelitesTerrestres[K_NUM_SATELITES_TERRESTRES] = {
    {"Luna",        /**/  0.27, /**/   0.00257, /**/  27.32, /**/        27.32, /**/ {0.7, 0.7, 0.7}, /**/      false, /**/ &posicionSatTerr[0], /**/                          0, /**/ NULL                  /**/ },
    {"ISS",         /**/  0.10, /**/   0.00001, /**/   0.0f, /**/ 1.0f / 24.0f, /**/ {0.0, 0.1, 0.0}, /**/      false, /**/ &posicionSatTerr[1], /**/                          0, /**/ NULL                  /**/ }
};

CuerpoCeleste planetas[K_NUM_PLANETAS] = {
    //                                 distancia      periodo        periodo                                            
    // nombre            radio       MaximaAlSol     Rotacion      Translacion            color      tieneAnillos        posicionPlaneta                                    numHijos      hijos
    {"Mercurio",    /* */ 0.38, /*  */   0.39, /* */   58.65, /*   */ 87.97,    /**/ {0.7, 0.7, 0.7},   false,     /**/ &posicionPlanetas[0] /**/, /**/                          0, /**/ NULL                  /**/},
    {"Venus",       /* */ 0.95, /*  */   0.72, /**/    243.02, /*  */ 224.70,   /**/ {0.7, 0.7, 1.0},   false,     /**/ &posicionPlanetas[1] /**/, /**/                          0, /**/ NULL                  /**/},
    {"Tierra",      /* */ 1.00, /*  */   1.00, /*  */  1.00, /*  */   365.26,   /**/ {0.0, 0.0, 1.0},   false,     /**/ &posicionPlanetas[2] /**/, /**/ K_NUM_SATELITES_TERRESTRES, /**/ satelitesTerrestres   /**/},
    {"Marte",       /* */ 0.53, /*  */   1.52, /*  */  1.03, /*  */   686.98,   /**/ {1.0, 0.0, 0.0},   false,     /**/ &posicionPlanetas[3] /**/, /**/                          0, /**/ NULL                  /**/},
    {"Jupiter",     /**/  11.21, /*  */  5.20, /*  */  0.41, /* */    4332.59,  /**/ {0.7, 0.7, 0.0},   false,     /**/ &posicionPlanetas[4] /**/, /**/                          0, /**/ NULL                  /**/ },
    {"Saturno",     /* */ 9.45, /*  */   9.58, /*  */  0.45, /**/     10759.22, /**/ {0.0, 0.0, 1.0},    true,     /**/ &posicionPlanetas[5] /**/, /**/                          0, /**/ NULL                  /**/ },
    {"Urano",       /* */ 4.01, /* */    19.22, /*  */ 0.72, /**/     30685.40, /**/ {0.0, 0.0, 1.0},   false,     /**/ &posicionPlanetas[6] /**/, /**/                          0, /**/ NULL                  /**/ },
    {"Neptuno",     /* */ 3.88, /* */    30.05, /*  */ 0.67, /**/     60189.00, /**/ {0.0, 0.0, 1.0},   false,     /**/ &posicionPlanetas[7] /**/, /**/                          0, /**/ NULL                  /**/ },
    {"Pluton",      /* */ 0.18, /* */    39.48, /*  */ 6.39, /**/     90560.00, /**/ {0.0, 0.0, 1.0},   false,     /**/ &posicionPlanetas[8] /**/, /**/                          0, /**/ NULL                  /**/ }
};

CuerpoCeleste sol =
/**/{ "Sol",        /**/109.00, /**/   0.0,     /**/   0.0,  /**/         0.0,  /**/ {1.0, 1.0, 0.0}, /**/      false, /**/ &posicionSol,         /**/             K_NUM_PLANETAS, /**/ planetas              /**/ };


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


void actualizaDatosCuerpoCeleste( CuerpoCeleste* cuerpoCeleste)
{
    float chronos_segundosRealesPorDiaSimulado = K_VELOCIDAD_SPD_ARRAY[cs.chronos_segundosRealesPorDiaSimulado_posicionSeleccionada];

    if (cuerpoCeleste->periodoTraslacion > 0.0f && cs.chronos_segundosRealesPorDiaSimulado_posicionSeleccionada != 0)
    {

        /*
        float deltaTraslacion = 360.0f / (cuerpoCeleste->periodoTraslacion * chronos_segundosRealesPorDiaSimulado * cs.chronos_framesPorSegundo);

        cuerpoCeleste->posicion->anguloTraslacion += deltaTraslacion;

        if (cuerpoCeleste->posicion->anguloTraslacion > 360.0f)
        {
            cuerpoCeleste->posicion->anguloTraslacion -= 360.0f;
        }
        */

        cuerpoCeleste->posicion->anguloTraslacion = cs.chronos_diaActualmenteSimulado * (360.0 / cuerpoCeleste->periodoTraslacion);

        cuerpoCeleste->posicion->anguloTraslacion = fmod(cuerpoCeleste->posicion->anguloTraslacion, 360);

    }

    // --

    if (cuerpoCeleste->periodoRotacion > 0.0f && cs.chronos_segundosRealesPorDiaSimulado_posicionSeleccionada != 0)
    {
        /*
        float deltaRotacion = 360.0f / (cuerpoCeleste->periodoRotacion * chronos_segundosRealesPorDiaSimulado * cs.chronos_framesPorSegundo);

        cuerpoCeleste->posicion->anguloRotacion += deltaRotacion;

        if (cuerpoCeleste->posicion->anguloRotacion > 360.0f)
        {
            cuerpoCeleste->posicion->anguloRotacion -= 360.0f;
        }
        */

        cuerpoCeleste->posicion->anguloRotacion = cs.chronos_diaActualmenteSimulado * (360.0 / cuerpoCeleste->periodoRotacion);

        cuerpoCeleste->posicion->anguloRotacion = fmod(cuerpoCeleste->posicion->anguloRotacion, 360);

    }

    if (cuerpoCeleste->numHijos > 0)
    {

        for (int pos = 0; pos < cuerpoCeleste->numHijos; pos++)
        {
            actualizaDatosCuerpoCeleste(&cuerpoCeleste->hijos[pos]);
        }
    }

}

void inicializaPosicionCuerpoCeleste(CuerpoCeleste* cuerpoCeleste) {
    cuerpoCeleste->posicion->radio = log10(cs.factorEscaladoCuerposCelestes * cuerpoCeleste->radio);

    if (cuerpoCeleste->posicion->radio < 0.2f)
    {
        cuerpoCeleste->posicion->radio = 0.2f;
    }

    cuerpoCeleste->posicion->distanciaAlPadre = 0.0f;

    if (cuerpoCeleste->distanciaMaximaAlSol > 0.0f)
    {

        cuerpoCeleste->posicion->distanciaAlPadre = cs.factorEscaladoDistancias * sqrt(cuerpoCeleste->distanciaMaximaAlSol);

        if (cuerpoCeleste->posicion->distanciaAlPadre < 0.2f)
        {
            cuerpoCeleste->posicion->distanciaAlPadre = 0.2f;
        }

    }

    if(cuerpoCeleste->numHijos > 0)
    {
        for (int pos = 0; pos < cuerpoCeleste->numHijos; pos++)
        {
            inicializaPosicionCuerpoCeleste(&cuerpoCeleste->hijos[pos]);
        }
    }

}

void representaCuerpoCeleste(CuerpoCeleste* cuerpoCeleste, bool imprimirDatos)
{


    // --

    glColor3f(cuerpoCeleste->color[0], cuerpoCeleste->color[1], cuerpoCeleste->color[2]);

    /*

    glPushMatrix();

    {
        glRotatef(90.0f, 1.0f, 0.0f, 0.0);

        glutWireTorus(cuerpoCeleste->posicion->radio/24.0f, cuerpoCeleste->posicion->distanciaAlPadre,  3, 360);

    }

    glPopMatrix();

    */

    // --

    glPushMatrix();

    {
        int textura;
        if (strcmp(cuerpoCeleste->nombre, "Sol") == 0)
        {
            textura = cargarTextura("texturas/sol.bmp");
            glEnable(GL_TEXTURE_2D);
            glBindTexture(GL_TEXTURE_2D, textura);
        }




        if (cs.mostrarOrbitas && cuerpoCeleste->posicion->distanciaAlPadre > 0.0f)
        {
            //  myEllipse(0.0f, 0.0f, cuerpoCeleste->posicion->distanciaAlPadre, cuerpoCeleste->posicion->distanciaAlPadre / 2.0, 100);
            myEllipse(0.0f, 0.0f, cuerpoCeleste->posicion->distanciaAlPadre, cuerpoCeleste->posicion->distanciaAlPadre, 360);

        }

        if (cuerpoCeleste->periodoTraslacion > 0.0f)
        {
            glRotatef(cuerpoCeleste->posicion->anguloTraslacion, 0.0f, 1.0f, 0.0);
        }

        if (cuerpoCeleste->posicion->distanciaAlPadre > 0.0f)
        {
            glTranslatef(cuerpoCeleste->posicion->distanciaAlPadre, 0.0f, 0.0f);
        }

        if (cuerpoCeleste->periodoRotacion > 0.0f)
        {
            glRotatef(cuerpoCeleste->posicion->anguloRotacion, 0.0f, 5.0f, 0.0);
        }

        if (strcmp(cuerpoCeleste->nombre, "Sol") == 0)
        {
            glEnable(GL_TEXTURE_2D);
            glBindTexture(GL_TEXTURE_2D, textura);
            //glBegin(GL_QUADS);
            //{
            //    //Cara frontal
            //    /*glTexCoord2f(0.0, 0.0); glVertex3f(-cuerpoCeleste->posicion->radio, -cuerpoCeleste->posicion->radio, 0.0);
            //    glTexCoord2f(1.0, 0.0); glVertex3f(cuerpoCeleste->posicion->radio, -cuerpoCeleste->posicion->radio, 0.0);
            //    glTexCoord2f(1.0, 1.0); glVertex3f(cuerpoCeleste->posicion->radio, cuerpoCeleste->posicion->radio, 0.0);
            //    glTexCoord2f(0.0, 1.0); glVertex3f(-cuerpoCeleste->posicion->radio, cuerpoCeleste->posicion->radio, 0.0);*/

            //    //Cara Superior (en Z)
            //    glTexCoord2f(0.0, 0.0); glVertex3f(-cuerpoCeleste->posicion->radio, cuerpoCeleste->posicion->radio, -cuerpoCeleste->posicion->radio);

            //    glTexCoord2f(0.0, 1.0); glVertex3f(cuerpoCeleste->posicion->radio, cuerpoCeleste->posicion->radio, -cuerpoCeleste->posicion->radio);
            //    glTexCoord2f(1.0, 0.0); glVertex3f(-cuerpoCeleste->posicion->radio, cuerpoCeleste->posicion->radio, cuerpoCeleste->posicion->radio);
            //    
            //    glTexCoord2f(1.0, 1.0); glVertex3f(cuerpoCeleste->posicion->radio, cuerpoCeleste->posicion->radio, cuerpoCeleste->posicion->radio);
            //    

            //}
            //glEnd();
            //glScalef (2*cuerpoCeleste->posicion->radio,2* cuerpoCeleste->posicion->radio, 2*cuerpoCeleste->posicion->radio);
            glCallList(myEsfera());


            glDisable(GL_TEXTURE_2D);

        }
        else
        {
            if (!strcmp(cuerpoCeleste->nombre, "Mercurio" )==0 && !strcmp(cuerpoCeleste->nombre, "Tierra") == 0)
            {
                glutWireCube(cuerpoCeleste->posicion->radio);
            }else
            {
                glutSolidCube(cuerpoCeleste->posicion->radio);
            }
            
        }


        if (cuerpoCeleste->tieneAnillos)
        {
            for (float distancia = cuerpoCeleste->posicion->radio * 1.2f; distancia <= cuerpoCeleste->posicion->radio * 2.0f; distancia += 0.2f)
            {
                myEllipse(0.0f, 0.0f, distancia, distancia, 360);
            }
        }


        //glutSolidSphere(cuerpoCeleste->posicion->radio, 20, 20);
       //myEsfera();








        myEjes();

        //myEsfera();
        //glutSolidSphere(cuerpoCeleste->posicion->radio, 20, 20);
        // glutWireSphere(cuerpoCeleste->posicion->radio, 20, 20);

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
        printf("%20s - tamaño: %2.5f - distancia al centro: %2.5f\n", cuerpoCeleste->nombre, cuerpoCeleste->posicion->radio, cuerpoCeleste->posicion->distanciaAlPadre);
    }

}
