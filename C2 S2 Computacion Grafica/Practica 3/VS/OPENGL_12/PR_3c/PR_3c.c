#include <windows.h>

#include "sistemaSolar.h"

#include <stdio.h>
#include <math.h>

// --

extern void myCamara();

extern void myTeclado(unsigned char tras, int x, int y);

extern void myTeclasEspeciales(int cursor, int x, int y);

extern int myEsfera();

// --

planeta planetas[9] = {
    {"Mercurio",    /* */ 0.38, /*  */ 0.39, /* */ 58.65, /*   */ 87.97, /**/ 0.0, /**/ {0.7, 0.7, 0.7}},
    {"Venus",       /* */ 0.95, /*  */ 0.72, /**/ 243.02, /*  */ 224.70, /**/ 0.0, /**/ {0.7, 0.7, 1.0}},
    {"Tierra",      /* */ 1.00, /*  */ 1.00, /*  */ 1.00, /*  */ 365.26, /**/ 0.0, /**/ {0.0, 0.0, 1.0}},
    {"Marte",       /* */ 0.53, /*  */ 1.52, /*  */ 1.03, /*  */ 686.98, /**/ 0.0, /**/ {1.0, 0.0, 0.0}},
    {"Jupiter",     /**/ 11.21, /*  */ 5.20, /*  */ 0.41, /* */ 4332.59, /**/ 0.0, /**/ {0.7, 0.7, 0.0}},
    {"Saturno",     /* */ 9.45, /*  */ 9.58, /*  */ 0.45, /**/ 10759.22, /**/ 0.0, /**/ {0.0, 0.0, 1.0}},
    {"Urano",       /* */ 4.01, /* */ 19.22, /*  */ 0.72, /**/ 30685.40, /**/ 0.0, /**/ {0.0, 0.0, 1.0}},
    {"Neptuno",     /* */ 3.88, /* */ 30.05, /*  */ 0.67, /**/ 60189.00, /**/ 0.0, /**/ {0.0, 0.0, 1.0}},
    {"Pluton",      /* */ 0.18, /* */ 39.48, /*  */ 6.39, /**/ 90560.00, /**/ 0.0, /**/ {0.0, 0.0, 1.0}}
};

// --

const int W_WIDTH = 500;
const int W_HEIGHT = 500;

GLfloat fAngulo;

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

    // Clear the window with current clearing color

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Se activa la matriz del modelador
    glMatrixMode(GL_MODELVIEW);

    // Inicializamos la matriz del modelo a la identidad
    glLoadIdentity();

    myEjes();

    // Sol
    {
        glPushMatrix();

        glColor3f(1.0, 1.0, 0);

        //La hago más pequeña
        glScalef(0.1, 0.1, 0.1);

        glTranslatef(0.0f, 0.0f, 0.0f);

        myEsfera();

        glPopMatrix();
    }

    for (int pos =0; pos < 9; pos++)
    {
        representaUnPlaneta(&planetas[pos]);
    }
   


    // Se limpian los buffers
    glutSwapBuffers();
    glFlush();
}

// ##

void myStep(void)
{
    fAngulo += 0.3f;
    if (fAngulo > 360.0f)
    {
        fAngulo -= 360.0f;
    }

    for (int pos = 0; pos < 9; pos++)
    {
        actualizaDatosUnPlaneta(&planetas[pos]);
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

    glutTimerFunc(5, myMovimiento, 0);// hace que se vuelva a ejecutar cada MYTIEMPO milisegundos

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


int main(int argc, char **argv)
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

    myMovimiento(1);

    // --

    // Lazo principal
    glutMainLoop();

    // --

    return 0;
}
