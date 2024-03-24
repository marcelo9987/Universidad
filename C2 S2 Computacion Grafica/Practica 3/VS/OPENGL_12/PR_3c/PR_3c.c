
#include "controles.h"
#include "sistemaSolar.h"

#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <windows.h>

// --

//extern int myEsfera();

// --
extern CuerpoCeleste sol;

extern CuerpoCeleste planetas[];

extern CuerpoCeleste satelitesTerrestres[];

// --



// --

const int W_WIDTH = 1000;
const int W_HEIGHT = 1000;

//GLfloat fAngulo;

// --

void myEjes()
{
    // Eje X
    glColor3f(1.0f, 0.0f, 0.0f);    // Red
    //  glColor3f(0.0f, 0.0f, 1.0f);    // Blue
    glBegin(GL_LINES);
    {
        glVertex3f(0.0f, 0.0f, 0.0f);
        glVertex3f(0.75f, 0.0f, 0.0f);
    }
    glEnd();

    // Eje Y
    glColor3f(0.0f, 1.0f, 0.0f);    // Green
    //  glColor3f(1.0f, 0.0f, 0.0f);    // Red
    glBegin(GL_LINES);
    {
        glVertex3f(0.0f, 0.0f, 0.0f);
        glVertex3f(0.0f, 0.75f, 0.0f);
    }
    glEnd();

    // Eje Z
    glColor3f(0.0f, 0.0f, 1.0f);    // Blue
    //  glColor3f(0.0f, 1.0f, 0.0f);    // Green
    glBegin(GL_LINES);
    {
        glVertex3f(0.0f, 0.0f, 0.0f);
        glVertex3f(0.0f, 0.0f, 0.75f);
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


// Función de display
void myDisplay(void)
{
    static bool primeraVez = true;


    // Clear the window with current clearing color

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Se activa la matriz del modelador
    glMatrixMode(GL_MODELVIEW);

    // Inicializamos la matriz del modelo a la identidad
    glLoadIdentity();

    myEjes();

    // Sol
    representaSol(&sol, primeraVez);

    for (int pos = 0; pos < 9; pos++)
    {
        representaPlaneta(&planetas[pos], primeraVez);
    }



    // Se limpian los buffers
    glutSwapBuffers();
    glFlush();

    primeraVez = false;
}

// ##

void myStep(void)
{
    /*fAngulo += 0.3f;
    if (fAngulo > 360.0f)
    {
        fAngulo -= 360.0f;
    }*/

    actualizaDatosSol(&sol);

    for (int pos = 0; pos < 9; pos++)
    {
        actualizaDatosPlaneta(&planetas[pos]);
    }

    glutPostRedisplay();
}

// Para que cada electrón vaya a diferentes velocidades debes usar una variable (fAngulo) para cada electron.
void myIdle(void)
{
    //myStep(); //Se hace el movimiento
}

void myMovimiento(int value)
{

    myStep(); //Se hace el movimiento

    glutTimerFunc(40, myMovimiento, 0);// hace que se vuelva a ejecutar cada MYTIEMPO milisegundos

}

// ##

void myOpenGlInit()
{
    // Habilito aqui el depth en vez de arriba - para los usuarios de linux y mac mejor arriba

    // Incializaciones varias
    glClearDepth(1.0f);         //Valor z-buffer
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);  // Valor limpieza buffer color
    glEnable(GL_DEPTH_TEST);    // z-buffer
    glEnable(GL_CULL_FACE);     // Ocultación caras back
    glCullFace(GL_BACK);

}


int main(int argc, char** argv)
{

    glutInit(&argc, argv);

    // Posición de la ventana
    glutInitWindowPosition(100, 100);
    // Tamaño de la ventana
    glutInitWindowSize(W_WIDTH, W_HEIGHT);
    // Tipo de color y buffer
    glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);
    // Crear la ventana
    glutCreateWindow("Ventana con el Visual C++ y glut");

    // Función que mira el teclado
    glutKeyboardFunc(myTeclado);

    glutSpecialFunc(myTeclasEspeciales);

    // Función de dibujo
    glutDisplayFunc(myDisplay);

    // --

    // Función de actualización
    glutIdleFunc(myIdle);

    myOpenGlInit();

    inicializaConfiguracionSistema();
    inicializaConfiguracionCamara();

    myMovimiento(1);

    // Recalculamos la posición de la cámara
    myCamara("START");

    // --

    // Lazo principal
    glutMainLoop();

    // --

    return 0;
}
