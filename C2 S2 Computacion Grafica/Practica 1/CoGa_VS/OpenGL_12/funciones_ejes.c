
/*****************************************************

Julian.flores@usc.es

Programas demo para clase -I

Por ahora nos la creemos y la llamamos ya explicaremos que hace.

*************************************************************/


#include <windows.h>    //Inclusión de variables de windows
#include <glut.h>       //Inclusión de GLUT
#include <GL/gl.h>      //Inclusión de GL
#include <GL/glu.h>
#include <stdio.h>
#include <math.h>       //Inclusión de librerías auxiliares


#define INCREMENTO .05
#define DISTANCIA 1
#define PI 3.1416

#define radianesAGrados(x) (x * 180.0 / PI)
#define gradosARadianes(x) (x * PI / 180.0)

// Angulos (en radianes) para la cámara
float alpha = 0.0f;  // Izquierda y derecha
float beta = 0.0f;  // Arriba y abajo

void imprimeDatos(char* detalleAccion)
{
    printf("[DEBUG] %s: alpha (LEFT-RIGHT): %f, beta(UP-DOWN): %f\n", detalleAccion, radianesAGrados(alpha), radianesAGrados(beta));
}


void myCamara()
{

    /**/

    glMatrixMode(GL_PROJECTION);//Configuración de la matriz de proyección
    glLoadIdentity();
    glOrtho(-1.0, 1.0f, -1.0, 1.0f, .1, 10.0f);    //proyección ortográfica

    float eyeX = (float)DISTANCIA * (float)sin(alpha) * fabs(cos(beta));
    float eyeY = (float)DISTANCIA * (float)sin(beta);
    float eyeZ = (float)DISTANCIA * cos(alpha) * fabs(cos(beta)) * (1.0);
    gluLookAt(
        eyeX, eyeY, eyeZ,
        0, 0, 0,
        0, 1, 0);

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
FUNCIÓN DE CONTROL DE TECLAS ESPECIAIS:
**************************************
*/
void myTeclasespeciales(int cursor, int x, int y)
{
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
        imprimeDatos("RESET");
        break;

        //Giros:
    case GLUT_KEY_UP:
        // Mover la cámara hacia arriba
        beta += INCREMENTO;
        imprimeDatos("UP   ");
        break;
    case GLUT_KEY_DOWN:
        // Mover la cámara hacia abajo
        beta -= INCREMENTO;
        imprimeDatos("DOWN ");
        break;

    case GLUT_KEY_RIGHT:
        // Mover la cámara a la derecha
        alpha += INCREMENTO;
        imprimeDatos("RIGHT");
        break;
    case GLUT_KEY_LEFT:
        // Mover la cámara a la izquierda
        alpha -= INCREMENTO;
        imprimeDatos("LEFT ");
        break;
    default:
        break;
    }

    // Izquierda y derecha
    if (alpha >= PI * 2.0)
    {
        alpha = 0;
    }else if (alpha < 0)
    {
        alpha = PI * 2.0;
    }

    // Arriba y abajo
    if (beta >= PI * 2.0)
    {
        beta = 0;
    }
    else if (beta < 0)
    {
        beta = PI * 2.0;
    }//hay que repasarlo para evitar el salto


    // Recalculamos la posición de la cámara
    myCamara();

    // Forzamos el redibujado
    glutPostRedisplay();

}
