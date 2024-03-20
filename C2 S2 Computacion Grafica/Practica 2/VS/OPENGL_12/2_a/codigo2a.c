/****************************************************************************
julian.flores@usc.es


El frustrum corresponde a la proyeccion
glOrtho(-100.0,100.0f,-100.0,100.0f,-100.0,100.0f);

Tareas a hacer.

Genera las mismas figuras con
Razona que pasa en cada caso.
GL_LINES
GL_LINE_STRIP
GL_LINE_LOOP
GL_TRIANGLES
GL_QUADS
GL_POLYGON

Usa la función glPolygonMode

******************************************************************************/



#include <windows.h>    // Inclusión de variables de Windows

#include <glut.h>       // Inclusión de GLUT
#include <GL/gl.h>      // Inclusión de GL
#include <GL/glu.h>

//Inclusión de librerías auxiliares
#include <stdio.h>
#include <math.h>

// #pragma comment(lib, "glut32.dll")

const int W_WIDTH = 500;    //Ancho de la ventana
const int W_HEIGHT = 500;   //Alto de la ventana

// #define GL_PI M_PI // 3.14f

// Ángulos de rotación para la cámara
static GLfloat xRot = 0.0f;
static GLfloat yRot = 0.0f;

//Están en el segundo archivo

extern myCamara();

extern void myTeclado(unsigned char tras, int x, int y);

extern void myTeclasEspeciales(int cursor, int x, int y);


// Esta función contiene muchas cosas no explicadas, por ahora las mantenemos ahí y las iremos explicando.
void myOpenGlInit()
{
    //Habilito aquí el depth en vez de arriba; para los usuarios de linux y mac mejor en el main
    glClearDepth(1.0f); //Valor z-buffer

    glClearColor(0.0f, 0.0f, 0.0f, 1.0f); // valor limpieza buffer color


    glEnable(GL_CULL_FACE); // Habilita la ocultación de caras "back"

    glEnable(GL_NORMALIZE); // Normaliza las normales

}

// Función que dibuja los ejes
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


void cuadrado__GL_QUADS()
{
    glColor3f(1.0f, 1.0f, 50.0f);
    glBegin(GL_QUADS);
    {
        //	glVertex3f(-.50f, -.5f, 0.0f);
        glVertex3f(.5f, -.5f, 0.0f);
        glVertex3f(.5f, .5f, 0.0f);
        //	glVertex3f(.5f, .5f, 0.0f);
        glVertex3f(-.5f, .5f, 0.0f);
        glVertex3f(-.5f, -.5f, 0.0f);
    }
    glEnd();
}


void cuadrado__GL_LINE_STRIP()
{
    glColor3f(1.0f, 1.0f, 50.0f);
    glBegin(GL_LINE_STRIP);
    {
        glVertex3f(-.50f, -.5f, 0.0f);
        glVertex3f(.5f, -.5f, 0.0f);
        glVertex3f(.5f, .5f, 0.0f);
        glVertex3f(-.5f, .5f, 0.0f);
        glVertex3f(-.5f, -.5f, 0.0f);
    }
    glEnd();
}

// ##

// Función de dibujo (función principal)
void myDisplay(void)
{

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // Clear the window with current clearing color

    myCamara(); // Para colocar la camara; por ahora nada

    // Inicializamos la matriz del modelo a la identidad
    glMatrixMode(GL_MODELVIEW); //Matriz del Modelo
    glLoadIdentity(); // Inicializamos la matriz del modelo a la identidad

    myEjes(); // Dibujamos los ejes

    // Resto de figuras a dibujar

    // cuadrado__GL_QUADS();
    cuadrado__GL_LINE_STRIP();

    glFlush();
    glutSwapBuffers();

}

int main(int argc, char **argv)
{

    glutInit(&argc, argv);

    glutInitWindowPosition(0, 0); //Inicializa la ventana en una determinada posición

    glutInitWindowSize(W_WIDTH, W_HEIGHT); //Inicializa el tamaño de la función

    glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH); //Inicializa el modo de display, RGBA, Doble buffer y buffer de profundidad

    glutCreateWindow("Dibuja dos cuadrados, zbuffer y caras ocultas"); // Nombre de la ventana

    myOpenGlInit(); // Incializaciones varias

    //Eventos comentado hasta la siguiente práctica

    glutKeyboardFunc(myTeclado); // Eventos teclado
    glutSpecialFunc(myTeclasEspeciales); // Teclas especiales


    glutDisplayFunc(myDisplay); //Evento de dibujo

    glutMainLoop(); // Empieza en bucle principal

    return 0;
}