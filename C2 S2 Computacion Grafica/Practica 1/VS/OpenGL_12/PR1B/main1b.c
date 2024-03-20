
/*****************************************************

Julian.flores@usc.es

Programas demo para clase -I

Dibujar los ejes coordenados, en este caso solo hace uno.

Fijarse en las librerías externas que debe ser incluidas se encuentran el el fichero. funciones_ejes.c

*************************************************************/

// Recordar que previa a la compilación de este programa es preciso
// linkar las librerías glut32.lib y opengl32.lib


#include <windows.h>    // Inclusión de variables de Windows

#include <glut.h>       // Inclusión de GLUT
#include <GL/gl.h>      // Inclusión de GL
#include <GL/glu.h>

#include <stdio.h>
#include <math.h>       //Inclusión de librerías auxiliares

// #pragma comment(lib, "glut32.dll")

const int W_WIDTH = 500;    //Ancho de la ventana
const int W_HEIGHT = 500;   //Alto de la ventana



// Ángulos de rotación para la cámara
static GLfloat xRot = 0.0f;
static GLfloat yRot = 0.0f;

//Están en el segundo archivo

// extern myCamara();

extern void myTeclado(unsigned char tras, int x, int y);

extern void myTeclasEspeciales(int cursor, int x, int y);


// Esta función contiene muchas cosas no explicadas, por ahora las mantenemos ahí y las iremos explicando.
void myOpenGlInit()
{
    //Habilito aquí el depth en vez de arriba; para los usuarios de linux y mac mejor en el main
    glClearDepth(1.0f); //Valor z-buffer

    glClearColor(0.0f, 0.0f, 0.0f, 1.0f); // valor limpieza buffer color

    glEnable(GL_DEPTH_TEST); // z-buffer

    glEnable(GL_CULL_FACE); // Habilita la ocultación de caras "back"
    glCullFace(GL_BACK);
    glEnable(GL_NORMALIZE); // Normaliza las normales

}

void myEjes()
{
    // Dibujamos los ejes coordenados. Segmentos de dos puntos cada uno con su color.
    glBegin(GL_LINES);
    {
        // Eje X
        glColor3f(1.0f, 0.0f, 0.0f);    // Red
        glVertex3f(0.0f, 0.0f, 0.0f);
        glVertex3f(0.75f, 0.0f, 0.0f);

        // Eje Y
        glColor3f(0.0f, 1.0f, 0.0f);    // Green
        glVertex3f(0.0f, 0.0f, 0.0f);
        glVertex3f(0.0f, 0.75f, 0.0f);

        // Eje Z
        glColor3f(0.0f, 0.0f, 1.0f);    // Blue
        glVertex3f(0.0f, 0.0f, 0.0f);
        glVertex3f(0.0f, 0.0f, 0.75f);
    }
    glEnd();


    // Diagonal - segmento (0,0,0) - (1,1,1)
    glBegin(GL_LINES);
    {
        glColor3f(1.0f, 1.0f, 1.0f);    // White
        glVertex3f(0.0f, 0.0f, 0.0f);
        glVertex3f(0.35f, 0.35f, 0.35f);
    }
    glEnd();
}

// Función de dibujo (función principal)
void myDisplay(void)
{
    // Clear the window with current clearing color
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // myCamara(); // Para colocar la camara; por ahora nada

    // Inicializamos la matriz del modelo a la identidad
    glMatrixMode(GL_MODELVIEW); //Matriz del Modelo
    glLoadIdentity(); // Inicializamos la matriz del modelo a la identidad

    myEjes(); // Dibujamos los ejes

    // Resto de figuras a dibujar

    glFlush();
    glutSwapBuffers();

}

int main(int argc, char **argv)
{

    glutInit(&argc, argv);

    glutInitWindowPosition(0, 0); //Inicializa la ventana en una determinada posición

    glutInitWindowSize(W_WIDTH, W_HEIGHT); //Inicializa el tamaño de la función

    glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE); //Inicializa el modo de display, RGBA y Doble buffer

    glutCreateWindow("Generación de ejes"); // Nombre de la ventana

    myOpenGlInit(); // Incializaciones varias

    //Eventos comentado hasta la siguiente práctica

    //Eventos teclado, teclas especiales
    glutKeyboardFunc(myTeclado);
    glutSpecialFunc(myTeclasEspeciales);

    //Evento de dibujo
    glutDisplayFunc(myDisplay);


    // Empieza en bucle principal
    glutMainLoop();

    return 0;
}