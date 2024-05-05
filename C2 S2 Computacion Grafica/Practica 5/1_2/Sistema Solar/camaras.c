#include "camaras.h"
#include "sistemaSolar.h"


// --

void doMyCamara(GLdouble eyeX, GLdouble eyeY, GLdouble eyeZ, GLdouble nearX, GLdouble nearY, GLdouble nearZ)
{
    glMatrixMode(GL_PROJECTION); //Configuración de la matriz de proyección

    glLoadIdentity(); //La ponemos a uno

    GLdouble fovy = 60.0;
    GLdouble aspect = ((GLdouble)cs.window_width) / (GLdouble)cs.window_height;
    GLdouble zNear = 0.001;
    GLdouble zFar = 1000.0;

    //glOrtho(-1.0, 1.0f, -1.0, 1.0f, .1, 10.0f); //proyección ortográfica
    gluPerspective(fovy, aspect, zNear, zFar); //Proyección perspectiva
    // gluPerspective(45, 4.0/3.0, 0, 1500); //Proyección perspectiva

    gluLookAt(
        eyeX, eyeY, eyeZ, // look from camera XYZ
        nearX, nearY, nearZ, // look at the origin
        0, 1, 0); // positive Y up vector
}

// --

void myCamaraVistaGeneral(struct ConfiguracionCamara *configuracionCamara)
{
    const GLdouble factorDistanciaRelativaEspecifica = 100.0;

    GLdouble posXcamara = factorDistanciaRelativaEspecifica / configuracionCamara->zoomCamara * sin(configuracionCamara->alpha) * fabs(cos(configuracionCamara->beta));
    GLdouble posYcamara = factorDistanciaRelativaEspecifica / configuracionCamara->zoomCamara * sin(configuracionCamara->beta);
    GLdouble posZcamara = factorDistanciaRelativaEspecifica / configuracionCamara->zoomCamara * cos(configuracionCamara->alpha) * fabs(cos(configuracionCamara->beta));

    GLdouble posXdestino = 0.0f;
    GLdouble posYdestino = 0.0f;
    GLdouble posZdestino = 0.0f;

    doMyCamara(posXcamara, posYcamara, posZcamara, posXdestino, posYdestino, posZdestino);
}

void myCamaraDesdeLaTierraHaciaElSol(struct ConfiguracionCamara *configuracionCamara)
{
    const GLdouble factorDistanciaRelativaEspecifica = 1.0;

    GLdouble posXcamara = factorDistanciaRelativaEspecifica / configuracionCamara->zoomCamara * planetas[TIERRA].posicion->posX;
    GLdouble posYcamara = factorDistanciaRelativaEspecifica / configuracionCamara->zoomCamara * planetas[TIERRA].posicion->posY;
    GLdouble posZcamara = factorDistanciaRelativaEspecifica / configuracionCamara->zoomCamara * planetas[TIERRA].posicion->posZ;

    GLdouble posXdestino = 0.0;
    GLdouble posYdestino = 0.0;
    GLdouble posZdestino = 0.0;

    doMyCamara(posXcamara, posYcamara, posZcamara, posXdestino, posYdestino, posZdestino);
}

void myCamaraDesdeLaTierraHaciaOtroPlaneta(struct ConfiguracionCamara *configuracionCamara, enum EnumCuerpoCeleste haciaQueCuerpoCeleste)
{

    GLdouble posXcamara = planetas[TIERRA].posicion->posX;
    GLdouble posYcamara = planetas[TIERRA].posicion->posY;
    GLdouble posZcamara = planetas[TIERRA].posicion->posZ;

    GLdouble posXdestino = planetas[haciaQueCuerpoCeleste].posicion->posX;
    GLdouble posYdestino = planetas[haciaQueCuerpoCeleste].posicion->posY;
    GLdouble posZdestino = planetas[haciaQueCuerpoCeleste].posicion->posZ;

    doMyCamara(posXcamara, posYcamara, posZcamara, posXdestino, posYdestino, posZdestino);
}

void myCamaraHaciaLaTierra(struct ConfiguracionCamara *configuracionCamara, enum EnumCuerpoCeleste desdeQueCuerpoCeleste)
{

    GLdouble posXtierra = planetas[TIERRA].posicion->posX;
    GLdouble posYtierra = planetas[TIERRA].posicion->posY;
    GLdouble posZtierra = planetas[TIERRA].posicion->posZ;

    GLdouble anguloSatelite = planetas[TIERRA].posicion->anguloTraslacion + /* planetas[TIERRA].posicion->anguloRotacion +*/ satelitesTerrestres[desdeQueCuerpoCeleste - LUNA].posicion->anguloTraslacion;

    GLdouble posRelXsatelite = cos360(anguloSatelite) * satelitesTerrestres[desdeQueCuerpoCeleste - LUNA].posicion->distanciaAlPadre;
    GLdouble posRelYsatelite = +0.0;
    GLdouble posRelZsatelite = -sin360(anguloSatelite) * satelitesTerrestres[desdeQueCuerpoCeleste - LUNA].posicion->distanciaAlPadre;

    doMyCamara(posXtierra - posRelXsatelite, posYtierra - posRelYsatelite, posZtierra - posRelZsatelite,
        posXtierra, posYtierra, posZtierra);

}

void myCamaraHaciaUnSateliteTerrestre(struct ConfiguracionCamara *configuracionCamara, enum EnumCuerpoCeleste haciaQueCuerpoCeleste)
{
    glMatrixMode(GL_PROJECTION); //Configuración de la matriz de proyección
    //glLoadIdentity();

    GLdouble posXtierra = planetas[TIERRA].posicion->posX;
    GLdouble posYtierra = planetas[TIERRA].posicion->posY;
    GLdouble posZtierra = planetas[TIERRA].posicion->posZ;

    //  GLdouble anguloSatelite = planetas[TIERRA].posicion->anguloTraslacion + planetas[TIERRA].posicion->anguloRotacion + satelitesTerrestres[haciaQueCuerpoCeleste - LUNA].posicion->anguloTraslacion;
    GLdouble anguloSatelite = planetas[TIERRA].posicion->anguloTraslacion + satelitesTerrestres[haciaQueCuerpoCeleste - LUNA].posicion->anguloTraslacion;

    GLdouble posRelXsatelite = cos360(anguloSatelite) * satelitesTerrestres[haciaQueCuerpoCeleste - LUNA].posicion->distanciaAlPadre;
    GLdouble posRelYsatelite = +0.0;
    GLdouble posRelZsatelite = -sin360(anguloSatelite) * satelitesTerrestres[haciaQueCuerpoCeleste - LUNA].posicion->distanciaAlPadre;


    //configuracionCamara->mostrarOrbitas = false;

    doMyCamara(posXtierra, posYtierra, posZtierra,
        posXtierra + posRelXsatelite, posYtierra + posRelYsatelite, posZtierra + posRelZsatelite);

}

// --

void seleccionarVistaCamara(struct ConfiguracionCamara *configuracionCamara, enum EnumCuerpoCeleste visualizacionSeleccionada)
{

    // printf("Vista principal seleccionada: %d\n", visualizacionSeleccionada);
    
    switch (visualizacionSeleccionada)
    {
        case VISTA_GENERAL:
            configuracionCamara->alpha = 0.0f;
            configuracionCamara->beta = gradosARadianes(15.0f);

            configuracionCamara->zoomCamara = 1.0f;
            configuracionCamara->mostrarOrbitas = true;
            break;

        case VISTA_GENERAL_CENITAL:
            configuracionCamara->alpha = 0.0f;
            configuracionCamara->beta = gradosARadianes(90.0f);

            configuracionCamara->zoomCamara = 1.0f/3.0f;
            configuracionCamara->mostrarOrbitas = true;
            break;

        default:
            configuracionCamara->zoomCamara = 1.0f;
            configuracionCamara->mostrarOrbitas = false;
            break;
    }

};

void seleccionadaDesdeMenuVistaCamaraVisualizacionPrincipal(int opcionSeleccionada)
{
    enum EnumCuerpoCeleste visualizacionSeleccionada = (enum EnumCuerpoCeleste) opcionSeleccionada;

    cs.visualizacionPrincipal = visualizacionSeleccionada;
    seleccionarVistaCamara(&cs.camaraPrincipal, visualizacionSeleccionada);
}


void seleccionaCamara(struct ConfiguracionCamara *configuracionCamara, enum EnumCuerpoCeleste visualizacionSeleccionada)
{
    switch (visualizacionSeleccionada)
    {

    case VISTA_GENERAL:
    case VISTA_GENERAL_CENITAL:
        myCamaraVistaGeneral(configuracionCamara);
        break;

    case SOL:
        myCamaraDesdeLaTierraHaciaElSol(configuracionCamara);
        break;

    case LUNA:
    case ISS:
        myCamaraHaciaLaTierra(configuracionCamara, visualizacionSeleccionada);
        break;

    case LUNA_DESDE_LA_TIERRA:
    case ISS_DESDE_LA_TIERRA:
        myCamaraHaciaUnSateliteTerrestre(configuracionCamara,(visualizacionSeleccionada == LUNA_DESDE_LA_TIERRA) ? LUNA : ISS);
        break;

    default:
        myCamaraDesdeLaTierraHaciaOtroPlaneta(configuracionCamara, visualizacionSeleccionada);
        break;
    }

}
