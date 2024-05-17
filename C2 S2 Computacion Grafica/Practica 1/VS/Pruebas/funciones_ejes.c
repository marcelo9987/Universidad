
/*****************************************************
Julian.flores@usc.es

Programas demo para clase -I

Por ahora nos la creemos y la llamamos ya explicaremos qué hace.
*************************************************************/


#include <windows.h>    //Inclusión de variables de windows

#include <glut.h>       //Inclusión de GLUT
#include <GL/gl.h>      //Inclusión de GL
#include <GL/glu.h>
#include <stdio.h>

#define _USE_MATH_DEFINES

#include <math.h>       //Inclusión de librerías auxiliares

#define INCREMENTO .05
#define DISTANCIA 1
// #define PI 3.1416

#define radianesAGrados(x) (x * 180.0 / M_PI)
#define gradosARadianes(x) (x * M_PI / 180.0)

// Ángulos (en radianes) para la cámara
float alpha = 0.0f;  // Izquierda y derecha
float beta = 0.0f;  // Arriba y abajo

void imprimeDatos(char *detalleAccion)
{
    printf("[DEBUG] %5s: alpha (LEFT-RIGHT): %f, beta(UP-DOWN): %f\n", detalleAccion, radianesAGrados(alpha), radianesAGrados(beta));
}

void myCamara(char *detalleAccion)
{

    glMatrixMode(GL_PROJECTION); //Configuración de la matriz de proyección

    glLoadIdentity(); //La ponemos a uno

    glOrtho(-1.0, 1.0f, -1.0, 1.0f, .1, 10.0f); //proyección ortográfica

    float eyeX = (float) DISTANCIA * (float) sin(alpha) * fabs(cos(beta));
    float eyeY = (float) DISTANCIA * (float) sin(beta);
    float eyeZ = (float) DISTANCIA * cos(alpha) * fabs(cos(beta)) * (1.0);

    gluLookAt(
            eyeX, eyeY, eyeZ,
            0, 0, 0,
            0, 1, 0);


    imprimeDatos(detalleAccion);
    printf("eyeX: %f, eyeY: %f, eyeZ: %f\n", eyeX, eyeY, eyeZ);

}

void myTeclado(unsigned char tras, int x, int y)
{
    switch (tras)
    {
        case 'l':
            break;
        case 'c':
            break;
        case 'r':
            break;
        case 'p':
            break;

        default:
            break;
    }

    // Se se modificou algo redebúxase
    glutPostRedisplay();
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
            alpha = 0.0f;
            beta = 0.0f;
            detalleAccion = "RESET";
            break;

            //Giros:
        case GLUT_KEY_UP:
            // Mover la cámara hacia arriba
            beta += INCREMENTO;
            detalleAccion = "UP";
            break;
        case GLUT_KEY_DOWN:
            // Mover la cámara hacia abajo
            beta -= INCREMENTO;
            detalleAccion = "DOWN";
            break;

        case GLUT_KEY_RIGHT:
            // Mover la cámara a la derecha
            alpha += INCREMENTO;
            detalleAccion = "RIGHT";
            break;
        case GLUT_KEY_LEFT:
            // Mover la cámara a la izquierda
            alpha -= INCREMENTO;
            detalleAccion = "LEFT";
            break;

        default:
            break;
    }

    // Izquierda y derecha
    if (alpha >= 2.0 * M_PI)
    {
        alpha -= 2.0 * M_PI;
    } else if (alpha < 0)
    {
        alpha += 2.0 * M_PI;
    }

    // Arriba y abajo
    if (beta >= 2.0 * M_PI)
    {
        beta -= 2.0 * M_PI;
    } else if (beta < 0)
    {
        beta += 2.0 * M_PI;
    }

    // Recalculamos la posición de la cámara
    myCamara(detalleAccion);

    // Forzamos el redibujado
    glutPostRedisplay();

}
