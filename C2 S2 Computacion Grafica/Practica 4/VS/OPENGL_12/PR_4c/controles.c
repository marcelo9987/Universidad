

#include "controles.h"
#include "sistemaSolar.h"
#include "cargasIniciales.h"

#define INCREMENTO .05


// --

const float K_VELOCIDAD_SPD_ARRAY[K_VELOCIDAD_SPD_ARRAY_SIZE] = {
    INFINITY,       // detenido
    24.0f,          // 1 hora por segundo
    1.0f,           // 1 día por segundo
    1.0f / 7.0f,    // 1 semana por segundo
    12.0f / 365.26f // 1 mes por segundo
};

// --



// --

void imprimeDatos(char* detalleAccion)
{
    printf("\n[DEBUG] %10s: alpha (LEFT-RIGHT): %f, beta(UP-DOWN): %f\n", detalleAccion, radianesAGrados(cs.camaraPrincipal.alpha), radianesAGrados(cs.camaraPrincipal.beta));
}

void myChangeSize(GLint newWidth, GLint newHeight)
{
    cs.window_width = newWidth;
    cs.window_height = newHeight;

    // Prevent a divide by zero, when window is too short
    // (you cant make a window of zero width).
    if (cs.window_height == 0)
    {
        cs.window_height = 1;
    }


    // Recalculamos la posición de la cámara
    //myCamara("ChangeSize");
    /*

    // Set the viewport to be the entire window
    glViewport(100, 100, cs.window_width/10.0, cs.window_height/10.0);

    // Recalculamos la posición de la cámara
    myCamara("ChangeSize");
    */

    // Forzamos el redibujado
    glutPostRedisplay();
}

void doMyCamara(float eyeX, float eyeY, float eyeZ, float nearX, float nearY, float nearZ)
{

    glMatrixMode(GL_PROJECTION); //Configuración de la matriz de proyección

    glLoadIdentity(); //La ponemos a uno

    float fovy = 60.0f;
    float aspect = ((float)cs.window_width) / (float)cs.window_height;
    float zNear = 0.001f;
    float zFar = 1000.0f;

    //glOrtho(-1.0, 1.0f, -1.0, 1.0f, .1, 10.0f); //proyección ortográfica
    gluPerspective(fovy, aspect, zNear, zFar); //Proyección perspectiva
    // gluPerspective(45, 4.0/3.0, 0, 1500); //Proyección perspectiva


    gluLookAt(
        eyeX, eyeY, eyeZ, // look from camera XYZ
        nearX, nearY, nearZ, // look at the origin
        0, 1, 0); // positive Y up vector
}

void myCamaraVistaGeneral(char* detalleAccion)
{

    float eyeX = cs.camaraPrincipal.distanciaCamara * sin(cs.camaraPrincipal.alpha) * fabs(cos(cs.camaraPrincipal.beta));
    float eyeY = cs.camaraPrincipal.distanciaCamara * sin(cs.camaraPrincipal.beta);
    float eyeZ = cs.camaraPrincipal.distanciaCamara * cos(cs.camaraPrincipal.alpha) * fabs(cos(cs.camaraPrincipal.beta));

    float nearX = 0.0f;
    float nearY = 0.0f;
    float nearZ = 0.0f;

    //cs.camaraPrincipal.mostrarOrbitas = true;

    doMyCamara(eyeX, eyeY, eyeZ, nearX, nearY, nearZ);
}


void myCamaraDesdeLaTierraHaciaElSol(char* detalleAccion)
{
    float posXtierra = (cs.camaraPrincipal.distanciaCamara / 100) * planetas[TIERRA].posicion->posX;
    float posYtierra = (cs.camaraPrincipal.distanciaCamara / 100) * planetas[TIERRA].posicion->posY;
    float posZtierra = (cs.camaraPrincipal.distanciaCamara / 100) * planetas[TIERRA].posicion->posZ;

    float posXsol = 0.0f;
    float posYsol = 0.0f;
    float posZsol = 0.0f;

    //cs.camaraPrincipal.mostrarOrbitas = false;

    doMyCamara(posXtierra, posYtierra, posZtierra, posXsol, posYsol, posZsol);
}

void myCamaraDesdeLaTierraHaciaOtroPlaneta(char* detalleAccion, enum EnumCuerpoCeleste haciaQueCuerpoCeleste)
{
    float posXtierra = planetas[TIERRA].posicion->posX;
    float posYtierra = planetas[TIERRA].posicion->posY;
    float posZtierra = planetas[TIERRA].posicion->posZ;

    float posXdestino = planetas[haciaQueCuerpoCeleste].posicion->posX;
    float posYdestino = planetas[haciaQueCuerpoCeleste].posicion->posY;
    float posZdestino = planetas[haciaQueCuerpoCeleste].posicion->posZ;

    //cs.camaraPrincipal.mostrarOrbitas = false;

    doMyCamara(posXtierra, posYtierra, posZtierra, posXdestino, posYdestino, posZdestino);
}

void myCamaraHaciaLaTierra(char* detalleAccion, enum EnumCuerpoCeleste desdeQueCuerpoCeleste)
{

    float posXtierra = planetas[TIERRA].posicion->posX;
    float posYtierra = planetas[TIERRA].posicion->posY;
    float posZtierra = planetas[TIERRA].posicion->posZ;

    float anguloSatelite = planetas[TIERRA].posicion->anguloTraslacion + planetas[TIERRA].posicion->anguloRotacion + satelitesTerrestres[desdeQueCuerpoCeleste-LUNA].posicion->anguloTraslacion;

    float posRelXsatelite = cosf360(anguloSatelite) * satelitesTerrestres[desdeQueCuerpoCeleste - LUNA].posicion->distanciaAlPadre;
    float posRelYsatelite = +0.0f;
    float posRelZsatelite = -sinf360(anguloSatelite) * satelitesTerrestres[desdeQueCuerpoCeleste - LUNA].posicion->distanciaAlPadre;


    //cs.camaraPrincipal.mostrarOrbitas = false;

    doMyCamara(posXtierra - posRelXsatelite, posYtierra - posRelYsatelite, posZtierra - posRelZsatelite,
        posXtierra, posYtierra, posZtierra);

}

void myCamaraHaciaUnSateliteTerrestre(char* detalleAccion, enum EnumCuerpoCeleste haciaQueCuerpoCeleste)
{
    float posXtierra = planetas[TIERRA].posicion->posX;
    float posYtierra = planetas[TIERRA].posicion->posY;
    float posZtierra = planetas[TIERRA].posicion->posZ;

    float anguloSatelite = planetas[TIERRA].posicion->anguloTraslacion + planetas[TIERRA].posicion->anguloRotacion + satelitesTerrestres[haciaQueCuerpoCeleste - LUNA].posicion->anguloTraslacion;

    float posRelXsatelite = cosf360(anguloSatelite) * satelitesTerrestres[haciaQueCuerpoCeleste - LUNA].posicion->distanciaAlPadre;
    float posRelYsatelite = +0.0f;
    float posRelZsatelite = -sinf360(anguloSatelite) * satelitesTerrestres[haciaQueCuerpoCeleste - LUNA].posicion->distanciaAlPadre;


    //cs.camaraPrincipal.mostrarOrbitas = false;

    doMyCamara(posXtierra, posYtierra, posZtierra,
        posXtierra + posRelXsatelite, posYtierra + posRelYsatelite, posZtierra + posRelZsatelite);

}

void myTeclado(unsigned char tras, int x, int y)
{

    char* detalleAccion = "-----";

    switch (tolower(tras))
    {
    case 27: // Escape key
        exit(0);
        break;

    case 'l':
        cs.camaraPrincipal.distanciaCamara *= 1.1f;
        detalleAccion = "LEJOS";
        break;

    case 'c':
    case 'C':
        cs.camaraPrincipal.distanciaCamara /= 1.1f;
        if (cs.camaraPrincipal.distanciaCamara < 0.001f)
        {
            cs.camaraPrincipal.distanciaCamara = 0.001f;
        }
        detalleAccion = "CERCA";

        break;

    case 'r':
        break;

    case 'p':
        cs.chronos_segundosRealesPorDiaSimulado_posicionSeleccionada = 0;
        detalleAccion = "PAUSA";
        break;

    case 'o':
        cs.camaraPrincipal.mostrarOrbitas = !cs.camaraPrincipal.mostrarOrbitas;

        detalleAccion = "ORBITAS";

        break;

    case '+': // Speed            
        cs.chronos_segundosRealesPorDiaSimulado_posicionSeleccionada += 1;
        if (cs.chronos_segundosRealesPorDiaSimulado_posicionSeleccionada >= K_VELOCIDAD_SPD_ARRAY_SIZE)
        {
            cs.chronos_segundosRealesPorDiaSimulado_posicionSeleccionada = K_VELOCIDAD_SPD_ARRAY_SIZE - 1;
        }

        detalleAccion = "RAPIDO";

        break;

    case '-': // Speed
        cs.chronos_segundosRealesPorDiaSimulado_posicionSeleccionada -= 1;
        if (cs.chronos_segundosRealesPorDiaSimulado_posicionSeleccionada <= 0)
        {
            cs.chronos_segundosRealesPorDiaSimulado_posicionSeleccionada = 0;
        }

        detalleAccion = "LENTO";

        break;


    default:
        break;
    }

    // Recalculamos la posición de las cámaras
    //myCamaras(detalleAccion);

    // Si se ha modificado, algo se redibuja
    //glutPostRedisplay();
}

/**************************************
FUNCIÓN DE CONTROL DE TECLAS ESPECIALES:
**************************************
*/
void myTeclasEspeciales(int cursor, int x, int y)
{
    char* detalleAccion = "-----";

    switch (cursor)
    {
        //Traslaciones:
    case GLUT_KEY_F1:
        break;
    case GLUT_KEY_F2:

        break;
    case GLUT_KEY_F3:

        break;
    case GLUT_KEY_F4:
        break;
    case GLUT_KEY_F5:

        break;
    case GLUT_KEY_F6:
        break;

    case GLUT_KEY_F10:
        inicializaConfiguracionSistema();
        inicializaConfiguracionCamara();
        detalleAccion = "RESET";
        //cs.visualizacionPrincipal = VISTA_GENERAL;
        break;

        //Giros:
    case GLUT_KEY_UP:
        // Mover la cámara hacia arriba
        cs.camaraPrincipal.beta += INCREMENTO;
        detalleAccion = "UP";
        break;
    case GLUT_KEY_DOWN:
        // Mover la cámara hacia abajo
        cs.camaraPrincipal.beta -= INCREMENTO;
        detalleAccion = "DOWN";
        break;

    case GLUT_KEY_RIGHT:
        // Mover la cámara a la derecha
        cs.camaraPrincipal.alpha += INCREMENTO;
        detalleAccion = "RIGHT";
        break;
    case GLUT_KEY_LEFT:
        // Mover la cámara a la izquierda
        cs.camaraPrincipal.alpha -= INCREMENTO;
        detalleAccion = "LEFT";
        break;

    default:
        break;
    }

    // Izquierda y derecha
    if (cs.camaraPrincipal.alpha >= 2.0 * M_PI)
    {
        cs.camaraPrincipal.alpha -= 2.0 * M_PI;
    }
    else if (cs.camaraPrincipal.alpha < 0)
    {
        cs.camaraPrincipal.alpha += 2.0 * M_PI;
    }

    // Arriba y abajo
    if (cs.camaraPrincipal.beta >= M_PI / 2.0)
    {
        cs.camaraPrincipal.beta = M_PI / 2.0;
    }
    else if (cs.camaraPrincipal.beta < -M_PI / 2.0)
    {
        cs.camaraPrincipal.beta = -M_PI / 2.0;
    }

    // Recalculamos la posición de las cámaras
    //myCamaras(detalleAccion);

    // Forzamos el redibujado
    //glutPostRedisplay();

}

void seleccionarVistaCamara(int vistaSeleccionada)
{
    printf("Seleccionado: %d\n", vistaSeleccionada);
    cs.visualizacionPrincipal = vistaSeleccionada;

    /*
    if (cs.visualizacionPrincipal == VISTA_GENERAL)
    {
        cs.camaraPrincipal.mostrarOrbitas = true;
    }
    else
    {
        cs.camaraPrincipal.mostrarOrbitas = false;
    }
    */

    //myCamaras("CambPersp.");

    //glutPostRedisplay();

};

void iniciaMenu()
{
    int satelitesTerrestresMenu = glutCreateMenu(seleccionarVistaCamara);
    glutAddMenuEntry("Luna", LUNA);
    glutAddMenuEntry("ISS", ISS);

    int desdeTierra = glutCreateMenu(seleccionarVistaCamara);
    glutAddMenuEntry("Sol", SOL);
    glutAddMenuEntry("Mercurio", MERCURIO);
    glutAddMenuEntry("Venus", VENUS);
    glutAddMenuEntry("Marte", MARTE);
    glutAddMenuEntry("Jupiter", JUPITER);
    glutAddMenuEntry("Saturno", SATURNO);
    glutAddMenuEntry("Urano", URANO);
    glutAddMenuEntry("Neptuno", NEPTUNO);
    glutAddMenuEntry("Pluton", PLUTON);
    glutAddMenuEntry("-- La Luna --", LUNA_DESDE_LA_TIERRA);

    int menuPrincipal = glutCreateMenu(seleccionarVistaCamara);
    glutAddMenuEntry("Vista general", VISTA_GENERAL);
    glutAddSubMenu("Enfocar desde la Tierra", desdeTierra);
    glutAddSubMenu("Enfocar la Tierra desde", satelitesTerrestresMenu);

    glutSetMenu(menuPrincipal);
    glutAttachMenu(GLUT_RIGHT_BUTTON);


}
