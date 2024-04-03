#include "cargasIniciales.h"

#define STB_IMAGE_IMPLEMENTATION    
#include "stb_image.h"

#include "figurasGeometricas.h"


ConfiguracionSistema cs;

PosicionCuerpoCeleste posicionSatTerr[K_NUM_SATELITES_TERRESTRES];
PosicionCuerpoCeleste posicionPlanetas[K_NUM_PLANETAS];
PosicionCuerpoCeleste posicionSol; // = { 0.0f, 0.0f };

CuerpoCeleste satelitesTerrestres[K_NUM_SATELITES_TERRESTRES] =
{
            { LUNA,      /**/ "Luna",         /**/  0.30f, /**/   0.00757f, /**/   0.0f,  /**/ 27.32f,        /**/ "texturas/Luna.bmp",      /**/ {0.7f, 0.7f, 0.7f}, /**/ false, /**/ &posicionSatTerr[0], /**/                            0, /**/ NULL                  /**/ },
            { ISS,       /**/ "ISS",          /**/  0.13f, /**/   0.00257f, /**/   0.0f,  /**/ 1.0f / 24.0f,   /**/ "texturas/ISS.jpg",       /**/ {0.0f, 0.1f, 0.0f}, /**/ false, /**/ &posicionSatTerr[1], /**/                            0, /**/ NULL                  /**/ }
};

CuerpoCeleste planetas[K_NUM_PLANETAS] =
{
    //             /**/                                distancia       periodo         periodo                                            
    //   quienSoy  /**/ nombre               radio    MaximaAlSol      Rotacion      Translacion                            rutaTextura                     color           tieneAnillos      posicion                                          numHijos       hijos
       { MERCURIO, /**/ "Mercurio",    /**/   0.38f, /**/  0.39f,    /**/  58.65f, /**/    87.97f,     /**/ "texturas/Mercurio8K.jpg", /**/ {0.7f, 0.7f, 0.7f}, /**/ false, /**/ &posicionPlanetas[0], /**/                          0, /**/ NULL                  /**/ },
       { VENUS,    /**/ "Venus",       /**/   0.95f, /**/  0.72f,    /**/ 243.02f, /**/   224.70f,     /**/ "texturas/Venus8K.jpg",    /**/ {0.7f, 0.7f, 1.0f}, /**/ false, /**/ &posicionPlanetas[1], /**/                          0, /**/ NULL                  /**/ },
       { TIERRA,   /**/ "Tierra",      /**/   1.00f, /**/  1.00f,    /**/   1.00f, /**/   365.26f,     /**/ "texturas/Tierra8K.jpg",   /**/ {0.0f, 0.0f, 1.0f}, /**/ false, /**/ &posicionPlanetas[2], /**/ K_NUM_SATELITES_TERRESTRES, /**/ satelitesTerrestres   /**/ },
       { MARTE,    /**/ "Marte",       /**/   0.53f, /**/  1.52f,    /**/   1.03f, /**/   686.98f,     /**/ "texturas/Marte8k.jpg",    /**/ {1.0f, 0.0f, 0.0f}, /**/ false, /**/ &posicionPlanetas[3], /**/                          0, /**/ NULL                  /**/ },
       { JUPITER,  /**/ "Jupiter",     /**/  11.21f, /**/  5.20f,    /**/   0.41f, /**/  4332.59f,     /**/ "texturas/Jupiter8k.jpg",  /**/ {0.7f, 0.7f, 0.0f}, /**/ false, /**/ &posicionPlanetas[4], /**/                          0, /**/ NULL                  /**/ },
       { SATURNO,  /**/ "Saturno",     /**/   9.45f, /**/  9.58f,    /**/   0.45f, /**/ 10759.22f,     /**/ "texturas/Saturno8K.jpg",  /**/ {0.0f, 0.0f, 1.0f}, /**/  true, /**/ &posicionPlanetas[5], /**/                          0, /**/ NULL                  /**/ },
       { URANO,    /**/ "Urano",       /**/   4.01f, /**/ 19.22f,    /**/   0.72f, /**/ 30685.40f,     /**/ "texturas/Urano2K.jpg",    /**/ {0.0f, 0.0f, 1.0f}, /**/ false, /**/ &posicionPlanetas[6], /**/                          0, /**/ NULL                  /**/ },
       { NEPTUNO,  /**/ "Neptuno",     /**/   3.88f, /**/ 30.05f,    /**/   0.67f, /**/ 60189.00f,     /**/ "texturas/Neptuno2K.jpg",  /**/ {0.0f, 0.0f, 1.0f}, /**/ false, /**/ &posicionPlanetas[7], /**/                          0, /**/ NULL                  /**/ },
       { PLUTON,   /**/ "Pluton",      /**/    0.18f,/**/ 39.48f,    /**/   6.39f, /**/ 90560.00f,     /**/ "texturas/Pluton2K.jpg",   /**/ {0.0f, 0.0f, 1.0f}, /**/ false, /**/ &posicionPlanetas[8], /**/                          0, /**/ NULL                  /**/ }
};

CuerpoCeleste sol =
/**/{ SOL,      /**/ "Sol",        /**/ 109.00f, /**/  0.0f,     /**/   0.0f,  /**/     0.0f,      /**/ "texturas/Sol8K.jpg",        /**/ {1.0f, 1.0f, 0.0f}, /**/ false, /**/ &posicionSol,         /**/              K_NUM_PLANETAS, /**/ planetas              /**/ };


void inicializaConfiguracionSistema()
{
    cs.window_width = 1200;
    cs.window_height = 800;

    cs.chronos_diaActualmenteSimulado = 0.0f;
    cs.chronos_segundosRealesPorDiaSimulado_posicionSeleccionada = 1;
    cs.chronos_framesPorSegundo = 24.0f;

    cs.factorEscaladoCuerposCelestes = 10.0f;
    cs.factorEscaladoDistancias = 30.0f;

    cs.visualizacionPrincipal = VISTA_GENERAL;
}

void inicializaConfiguracionCamara()
{
    cs.camaraPrincipal.alpha = 0.0f;
    cs.camaraPrincipal.beta = gradosARadianes(15.0f);
    cs.camaraPrincipal.distanciaCamara = 100.0f;
    cs.camaraPrincipal.mostrarOrbitas = true;
}

bool cargaTextura(GLuint numTextura, char* rutaTextura)
{
    // Basado en https://learnopengl.com/Getting-started/Textures
    // Basado en https://stackoverflow.com/questions/5681948/multiple-textures-opengl-glut-c

    glBindTexture(GL_TEXTURE_2D, numTextura);

    int width, height, nrChannels;
    unsigned char* data = stbi_load(rutaTextura, &width, &height, &nrChannels, 0);
    if (data == NULL)
    {
        printf("Error al cargar la textura %s\n", rutaTextura);
        return false;
    }

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);

    //Parametros
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    stbi_image_free(data);

    return true;
}

extern void myEllipse(float cx, float cy, float rx, float ry, int num_segments);

void inicializaPosicionCuerpoCeleste(CuerpoCeleste* cuerpoCeleste)
{
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

    // --

    cuerpoCeleste->posicion->anguloRotacion = 0.0f;
    cuerpoCeleste->posicion->anguloTraslacion = 0.0f;

    // --

    cuerpoCeleste->posicion->numTexturaObjeto = INT_MIN;

    if (cuerpoCeleste->rutaTextura)
    {

        glGenTextures(1, &cuerpoCeleste->posicion->numTexturaObjeto);

        if (!cargaTextura(cuerpoCeleste->posicion->numTexturaObjeto, cuerpoCeleste->rutaTextura))
        {
            cuerpoCeleste->posicion->numTexturaObjeto = INT_MIN;
        }
    }

    // --


    cuerpoCeleste->posicion->numListaObjeto = glGenLists(1);


    glNewList(cuerpoCeleste->posicion->numListaObjeto, GL_COMPILE);
    {
        myEsfera();

        if (cuerpoCeleste->tieneAnillos)
        {
            for (float distancia = cuerpoCeleste->posicion->radio * 1.2f; distancia <= cuerpoCeleste->posicion->radio * 2.0f; distancia += 0.2f)
            {
                myEllipse(0.0f, 0.0f, distancia, distancia, 360);
            }
        }
    }
    glEndList();
/*
    // --

    glPushMatrix();

    glScalef(cs.factorEscaladoCuerposCelestes, cs.factorEscaladoCuerposCelestes, cs.factorEscaladoCuerposCelestes);


     glCallList(cuerpoCeleste->posicion->numListaObjeto);

    glPopMatrix();

    // --

            glCallList(cuerpoCeleste->posicion->numListaObjeto

*/

    // Imprimo los hijos
    if (cuerpoCeleste->numHijos > 0)
    {
        for (int pos = 0; pos < cuerpoCeleste->numHijos; pos++)
        {
            inicializaPosicionCuerpoCeleste(&cuerpoCeleste->hijos[pos]);
        }
    }

}