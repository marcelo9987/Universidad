#include "cargasIniciales.h"

#define STB_IMAGE_IMPLEMENTATION    
#include "stb_image.h"

#include "figurasGeometricas.h"


ConfiguracionSistema cs;
//HANDLE mutexVelocidad;

PosicionCuerpoCeleste posicionSatTerr[K_NUM_SATELITES_TERRESTRES];
PosicionCuerpoCeleste posicionPlanetas[K_NUM_PLANETAS];
PosicionCuerpoCeleste posicionSol;
PosicionCuerpoCeleste posicionBovedaCelestial;


CuerpoCeleste satelitesTerrestres[K_NUM_SATELITES_TERRESTRES] =
{
      // La luna tarda entre 27 y 28 días en dar una vuelta a la Tierra
      { LUNA,               /**/ "Luna",             /**/  0.30,    /**/  0.00757, /**/   0.0,  /**/   27.32,       /**/ "Texturas/Luna.bmp",       /**/ {0.7, 0.7, 0.7}, /**/ false, /**/ &posicionSatTerr[0],           /**/ 0,                         /**/ NULL                  /**/ },
      // La ISS tarda 90 minutos en dar una vuelta a la Tierra (16 puestas de sol al día) - la hemos puesto "marcha atrás" con respecto a los demás giros de los otros cuerpos celestes
//    { ISS,                /**/ "ISS",              /**/  0.13,    /**/  0.00257, /**/   0.0,  /**/ 1.0 / 16.0,    /**/ "Texturas/iss_1.jpg",      /**/ {0.0, 0.1, 0.0}, /**/ false, /**/ &posicionSatTerr[1],           /**/ 0,                         /**/ NULL                  /**/ }
      { ISS,                /**/ "ISS",              /**/  0.13,    /**/  0.00257, /**/   0.0,  /**/ 1.0 / 16.0,    /**/ NULL,                      /**/ {1.0, 1.0, 1.0}, /**/ false, /**/& posicionSatTerr[1],           /**/ 0,                         /**/ NULL                  /**/ }
};

CuerpoCeleste planetas[K_NUM_PLANETAS] =
{
    //                      /**/                                       distancia       periodo         periodo                                                                                                         
    //   quienSoy           /**/ nombre                    radio      MaximaAlSol      Rotacion      Translacion         rutaTextura                     color           tieneAnillos      posicion                          numHijos                        hijos
       { MERCURIO,          /**/ "Mercurio",         /**/   0.38,   /**/  0.39,    /**/  58.65, /**/    87.97,      /**/ "Texturas/Mercurio8K.jpg", /**/ {0.7, 0.7, 0.7}, /**/ false, /**/ &posicionPlanetas[0],        /**/ 0,                         /**/ NULL                  /**/ },
       { VENUS,             /**/ "Venus",            /**/   0.95,   /**/  0.72,    /**/ 243.02, /**/   224.70,      /**/ "Texturas/Venus8K.jpg",    /**/ {0.7, 0.7, 1.0}, /**/ false, /**/ &posicionPlanetas[1],        /**/ 0,                         /**/ NULL                  /**/ },
       { TIERRA,            /**/ "Tierra",           /**/   1.00,   /**/  1.00,    /**/   1.00, /**/   365.26,      /**/ "Texturas/Tierra8K.jpg",   /**/ {0.0, 0.0, 1.0}, /**/ false, /**/ &posicionPlanetas[2],        /**/ K_NUM_SATELITES_TERRESTRES,/**/ satelitesTerrestres   /**/ },
       { MARTE,             /**/ "Marte",            /**/   0.53,   /**/  1.52,    /**/   1.03, /**/   686.98,      /**/ "Texturas/Marte8k.jpg",    /**/ {1.0, 0.0, 0.0}, /**/ false, /**/ &posicionPlanetas[3],        /**/ 0,                         /**/ NULL                  /**/ },
       { JUPITER,           /**/ "Jupiter",          /**/  11.21,   /**/  5.20,    /**/   0.41, /**/  4332.59,      /**/ "Texturas/Jupiter8k.jpg",  /**/ {0.7, 0.7, 0.0}, /**/ false, /**/ &posicionPlanetas[4],        /**/ 0,                         /**/ NULL                  /**/ },
       { SATURNO,           /**/ "Saturno",          /**/   9.45,   /**/  9.58,    /**/   0.45, /**/ 10759.22,      /**/ "Texturas/Saturno8K.jpg",  /**/ {0.0, 0.0, 1.0}, /**/  true, /**/ &posicionPlanetas[5],        /**/ 0,                         /**/ NULL                  /**/ },
       { URANO,             /**/ "Urano",            /**/   4.01,   /**/ 19.22,    /**/   0.72, /**/ 30685.40,      /**/ "Texturas/Urano2K.jpg",    /**/ {0.0, 0.0, 1.0}, /**/ false, /**/ &posicionPlanetas[6],        /**/ 0,                         /**/ NULL                  /**/ },
       { NEPTUNO,           /**/ "Neptuno",          /**/   3.88,   /**/ 30.05,    /**/   0.67, /**/ 60189.00,      /**/ "Texturas/Neptuno2K.jpg",  /**/ {0.0, 0.0, 1.0}, /**/ false, /**/ &posicionPlanetas[7],        /**/ 0,                         /**/ NULL                  /**/ },
       { PLUTON,            /**/ "Pluton",           /**/   0.18,   /**/ 39.48,    /**/   6.39, /**/ 90560.00,      /**/ "Texturas/Pluton2K.jpg",   /**/ {0.0, 0.0, 1.0}, /**/ false, /**/ &posicionPlanetas[8],        /**/ 0,                         /**/ NULL                  /**/ }
};

CuerpoCeleste sol[1] =
{
        { SOL,              /**/ "Sol",              /**/ 109.00,   /**/  0.0,     /**/   0.0,  /**/     0.0,       /**/ "Texturas/Sol8K.jpg",      /**/ {1.0, 1.0, 0.0}, /**/ false, /**/ &posicionSol,                /**/ K_NUM_PLANETAS,            /**/ planetas             /**/ }
};

CuerpoCeleste bovedaCelestial[1] =
{
        { BOVEDA_CELESTIAL, /**/ "Bóveda Celestial", /**/ 30.00,   /**/  0.0,     /**/   0.0,  /**/     0.0,       /**/ "Texturas/boveda.jpg",     /**/ {1.0, 1.0, 0.0}, /**/ false, /**/ &posicionBovedaCelestial,    /**/ 1,                         /**/ sol                  /**/ }
};

void inicializaConfiguracionSistema(bool primeraVez)
{
    if (primeraVez) {
        cs.window_width = 1200;
        cs.window_height = 800;
    }

    cs.chronos_diaActualmenteSimulado = ((double)rand() / (double)(RAND_MAX)) * 10000.0;
    cs.chronos_segundosRealesPorDiaSimulado_posicionSeleccionada = 1;
    cs.chronos_framesPorSegundo = 24.0f;

    cs.factorEscaladoCuerposCelestes = 10.0f;
    cs.factorEscaladoDistancias = 30.0f;

    cs.mostrarEasterEggs = false;
    cs.mostrarEjes = false;
    cs.mostrarMonitores = true;
    cs.mostrarTextos = true;
    cs.seMuestraAyuda = false;
    
    cs.solEncendido = true;
    cs.potenciaIluminacion = 90; // [0..100]

//    mutexVelocidad = CreateMutex(NULL, FALSE, NULL);
    
}

void inicializaConfiguracionCamaras()
{
    enum EnumCuerpoCeleste visualizacionSeleccionada = VISTA_GENERAL;

    cs.visualizacionPrincipal = visualizacionSeleccionada;
    seleccionarVistaCamara(&cs.camaraPrincipal, visualizacionSeleccionada);

}

bool cargaTextura(GLuint numTextura, char* rutaTextura)
{
    // Basado en https://learnopengl.com/Getting-started/Textures
    // Basado en https://stackoverflow.com/questions/5681948/multiple-textures-opengl-glut-c



    int width, height, nrChannels;
    unsigned char* data = stbi_load(rutaTextura, &width, &height, &nrChannels, 0);
    if (data == NULL)
    {
        printf("Error al cargar la textura %s\n", rutaTextura);
        return false;
    }

    glBindTexture(GL_TEXTURE_2D, numTextura);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);

    //Parametros
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    stbi_image_free(data);

    return true;
}

//extern void myElipse(float cx, float cy, float rx, float ry, int num_segments, enum TipoCuerpoCeleste tipoCuerpoCeleste /*, int32_t flags*/);


void inicializaCuerpoCeleste(CuerpoCeleste* cuerpoCeleste)
{
    if (cuerpoCeleste->quienSoy == BOVEDA_CELESTIAL) {
        cuerpoCeleste->posicion->radio = cuerpoCeleste->radio;
    }
    else {
        cuerpoCeleste->posicion->radio = log10(cs.factorEscaladoCuerposCelestes * cuerpoCeleste->radio);
    }

    if (cuerpoCeleste->posicion->radio < 0.2)
    {
        cuerpoCeleste->posicion->radio = 0.2;
    }

    cuerpoCeleste->posicion->distanciaAlPadre = 0.0;

    if (cuerpoCeleste->distanciaMaximaAlSol > 0.0)
    {
        cuerpoCeleste->posicion->distanciaAlPadre = cs.factorEscaladoDistancias * sqrt(cuerpoCeleste->distanciaMaximaAlSol);

        if (cuerpoCeleste->posicion->distanciaAlPadre < 0.2)
        {
            cuerpoCeleste->posicion->distanciaAlPadre = 0.2;
        }

    }

    // --

    cuerpoCeleste->posicion->anguloRotacion = 0.0;
    cuerpoCeleste->posicion->anguloTraslacion = 0.0;

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

    switch (cuerpoCeleste->quienSoy)
    {
    case ISS:
        glEnable(GL_TEXTURE_GEN_S); //enable texture coordinate generation
        glEnable(GL_TEXTURE_GEN_T);
#if defined tetera
        {
            myEsfera(2);
        }
#else
        {
            myISS(); 
        }
#endif

        glDisable(GL_TEXTURE_GEN_S); //enable texture coordinate generation
        glDisable(GL_TEXTURE_GEN_T);

        break;

    case JUPITER:

        glEnable(GL_TEXTURE_GEN_S); //enable texture coordinate generation
        glEnable(GL_TEXTURE_GEN_T);

        //glBindTexture(GL_TEXTURE_2D, theTexture[2]);

        //glutWireDodecahedron();
        //glutSolidCube(2);
#if defined tetera
        glutSolidTeapot(2);
#else
        myEsfera();
#endif

        glDisable(GL_TEXTURE_GEN_S); //enable texture coordinate generation
        glDisable(GL_TEXTURE_GEN_T);

        break;

    case BOVEDA_CELESTIAL:
        glEnable(GL_TEXTURE_GEN_S); //enable texture coordinate generation
        glEnable(GL_TEXTURE_GEN_T);

        myReverseSolidCube(20);

        glDisable(GL_TEXTURE_GEN_S); //enable texture coordinate generation
        glDisable(GL_TEXTURE_GEN_T);

        break;

    default:

        myEsfera();
    }

    {
        if (cuerpoCeleste->tieneAnillos)
        {
            for (float distancia = cuerpoCeleste->posicion->radio * 1.2; distancia <= cuerpoCeleste->posicion->radio * 2.0; distancia += 0.2)
            {
                myElipse(0.0, 0.0, distancia, distancia, 360, tccAnillos /* O_ANILLOS*/);
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
            inicializaCuerpoCeleste(&cuerpoCeleste->hijos[pos]);
        }
    }

}