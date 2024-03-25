#include <windows.h>    //Inclusión de variables de windows

#include <glut.h>       //Inclusión de GLUT
#include <GL/gl.h>      //Inclusión de GL
#include <GL/glu.h>

#include <stdio.h>

#define _USE_MATH_DEFINES
#include <math.h>       //Inclusión de librerías auxiliares

#include "controles.h"
#include "sistemaSolar.h"


#define INCREMENTO .05


#define radianesAGrados(x) (x * 180.0 / M_PI)
#define gradosARadianes(x) (x * M_PI / 180.0)

// --

void inicializaConfiguracionCamara()
{
    cs.camaraPrincipal.alpha = 0.0f;
    cs.camaraPrincipal.beta = gradosARadianes(15.0f);
    cs.camaraPrincipal.distanciaCamara = 100.0f;
}

// --

void imprimeDatos(char *detalleAccion)
{
    printf("\n[DEBUG] %5s: alpha (LEFT-RIGHT): %f, beta(UP-DOWN): %f\n", detalleAccion, radianesAGrados(cs.camaraPrincipal.alpha), radianesAGrados(cs.camaraPrincipal.beta));
}

void myCamara(char *detalleAccion)
{

    glMatrixMode(GL_PROJECTION); //Configuración de la matriz de proyección

    glLoadIdentity(); //La ponemos a uno

    //glOrtho(-1.0, 1.0f, -1.0, 1.0f, .1, 10.0f); //proyección ortográfica
    gluPerspective(60.0f, 1.0f, 0.001f, 1000.0f); //Proyección perspectiva


    float eyeX = cs.camaraPrincipal.distanciaCamara * sin(cs.camaraPrincipal.alpha) * fabs(cos(cs.camaraPrincipal.beta));
    float eyeY = cs.camaraPrincipal.distanciaCamara * sin(cs.camaraPrincipal.beta);
    float eyeZ = cs.camaraPrincipal.distanciaCamara * cos(cs.camaraPrincipal.alpha) * fabs(cos(cs.camaraPrincipal.beta));

    gluLookAt(
            eyeX, eyeY, eyeZ, // look from camera XYZ
            0, 0, 0, // look at the origin
            0, 1, 0); // positive Y up vector


    imprimeDatos(detalleAccion);
    printf("eyeX: %f, eyeY: %f, eyeZ: %f\n", eyeX, eyeY, eyeZ);

}

void myTeclado(unsigned char tras, int x, int y)
{

    char *detalleAccion = "-----";

    switch (tras)
    {
        case 27: // Escape key
            exit(0);
            break;

        case 'l':
            cs.camaraPrincipal.distanciaCamara *= 1.1f;
            detalleAccion = "LEJOS";
            break;

        case 'c':
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
            break;

        case '+': // Speed            
            cs.velocidad_segundosPorDia_posicionSeleccionada += 1;
            if (cs.velocidad_segundosPorDia_posicionSeleccionada >= K_VELOCIDAD_SPD_ARRAY_SIZE)
            {
                cs.velocidad_segundosPorDia_posicionSeleccionada = K_VELOCIDAD_SPD_ARRAY_SIZE - 1;
            }
            break;

        case '-': // Speed
            cs.velocidad_segundosPorDia_posicionSeleccionada -= 1;
            if (cs.velocidad_segundosPorDia_posicionSeleccionada <= 0)
            {
                cs.velocidad_segundosPorDia_posicionSeleccionada = 0;
            }
            break;


        default:
            break;
    }

    // Recalculamos la posición de la cámara
    myCamara(detalleAccion);

    // Si se ha modificado, algo se redibuja
    glutPostRedisplay();
}

/**************************************
FUNCIÓN DE CONTROL DE TECLAS ESPECIALES:
**************************************
*/
void myTeclasEspeciales(int cursor, int x, int y)
{
    char *detalleAccion = "-----";

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
    } else if (cs.camaraPrincipal.alpha < 0)
    {
        cs.camaraPrincipal.alpha += 2.0 * M_PI;
    }

    // Arriba y abajo
    if (cs.camaraPrincipal.beta >= M_PI / 2.0)
    {
        cs.camaraPrincipal.beta = M_PI / 2.0;
    } else if (cs.camaraPrincipal.beta < -M_PI / 2.0)
    {
        cs.camaraPrincipal.beta = -M_PI / 2.0;
    }

    // Recalculamos la posición de la cámara
    myCamara(detalleAccion);

    // Forzamos el redibujado
    glutPostRedisplay();

}
