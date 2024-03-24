#include <windows.h>    //Inclusión de variables de windows

#include <glut.h>       //Inclusión de GLUT
#include <GL/gl.h>      //Inclusión de GL
#include <GL/glu.h>
#include <stdio.h>

#define _USE_MATH_DEFINES

#include <math.h>       //Inclusión de librerías auxiliares

#define INCREMENTO .05


#define radianesAGrados(x) (x * 180.0 / M_PI)
#define gradosARadianes(x) (x * M_PI / 180.0)

// --

typedef struct
{
    float alpha;            // Izquierda y derecha (Ángulos en radianes)
    float beta;             // Arriba y abajo (Ángulos en radianes)
    float distanciaCamara;   // Distancia de la cámara al origen;

} ConfiguracionCamara;

ConfiguracionCamara camaraPrincipal;

void inicializaConfiguracionCamara()
{
    camaraPrincipal.alpha = 0.0f;
    camaraPrincipal.beta = gradosARadianes(15.0f);
    camaraPrincipal.distanciaCamara = 100.0f;
}

// --

void imprimeDatos(char *detalleAccion)
{
    printf("\n[DEBUG] %5s: alpha (LEFT-RIGHT): %f, beta(UP-DOWN): %f\n", detalleAccion, radianesAGrados(camaraPrincipal.alpha), radianesAGrados(camaraPrincipal.beta));
}

void myCamara(char *detalleAccion)
{

    glMatrixMode(GL_PROJECTION); //Configuración de la matriz de proyección

    glLoadIdentity(); //La ponemos a uno

    //glOrtho(-1.0, 1.0f, -1.0, 1.0f, .1, 10.0f); //proyección ortográfica
    gluPerspective(60.0f, 1.0f, 0.001f, 1000.0f); //Proyección perspectiva
    

    float eyeX = camaraPrincipal.distanciaCamara * sin(camaraPrincipal.alpha) * fabs(cos(camaraPrincipal.beta));
    float eyeY = camaraPrincipal.distanciaCamara * sin(camaraPrincipal.beta);
    float eyeZ = camaraPrincipal.distanciaCamara * cos(camaraPrincipal.alpha) * fabs(cos(camaraPrincipal.beta));

    gluLookAt(
            eyeX, eyeY, eyeZ, // look from camera XYZ
            0, 0, 0, // look at the origin
            0, 1, 0); // positive Y up vector


    imprimeDatos(detalleAccion);
    printf("eyeX: %f, eyeY: %f, eyeZ: %f\n", eyeX, eyeY, eyeZ);

}

void myTeclado(unsigned char tras, int x, int y)
{

    char* detalleAccion = "-----";

    switch (tras)
    {
        case 27: // Escape key
            exit(0);
            break;

        case 'l':
            camaraPrincipal.distanciaCamara *= 1.1f;
            detalleAccion = "LEJOS";
            break;

        case 'c':
            camaraPrincipal.distanciaCamara /= 1.1f;
            if (camaraPrincipal.distanciaCamara < 0.001f)
            {
                camaraPrincipal.distanciaCamara = 0.001f;
            }
            detalleAccion = "CERCA";
                
            break;

        case 'r':
            break;

        case 'p':
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
            inicializaConfiguracionCamara();
            detalleAccion = "RESET";
            break;

            //Giros:
        case GLUT_KEY_UP:
            // Mover la cámara hacia arriba
            camaraPrincipal.beta += INCREMENTO;
            detalleAccion = "UP";
            break;
        case GLUT_KEY_DOWN:
            // Mover la cámara hacia abajo
            camaraPrincipal.beta -= INCREMENTO;
            detalleAccion = "DOWN";
            break;

        case GLUT_KEY_RIGHT:
            // Mover la cámara a la derecha
            camaraPrincipal.alpha += INCREMENTO;
            detalleAccion = "RIGHT";
            break;
        case GLUT_KEY_LEFT:
            // Mover la cámara a la izquierda
            camaraPrincipal.alpha -= INCREMENTO;
            detalleAccion = "LEFT";
            break;

        default:
            break;
    }

    // Izquierda y derecha
    if (camaraPrincipal.alpha >= 2.0 * M_PI)
    {
        camaraPrincipal.alpha -= 2.0 * M_PI;
    } else if (camaraPrincipal.alpha < 0)
    {
        camaraPrincipal.alpha += 2.0 * M_PI;
    }

    // Arriba y abajo
    if (camaraPrincipal.beta >= M_PI / 2.0)
    {
        camaraPrincipal.beta = M_PI / 2.0;
    } else if (camaraPrincipal.beta < -M_PI / 2.0)
    {
        camaraPrincipal.beta = -M_PI / 2.0;
    }

    // Recalculamos la posición de la cámara
    myCamara(detalleAccion);

    // Forzamos el redibujado
    glutPostRedisplay();

}
