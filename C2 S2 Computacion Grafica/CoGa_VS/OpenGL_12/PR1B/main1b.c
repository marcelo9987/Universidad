
/*****************************************************

Julian.flores@usc.es

Programas demo para clase -I

Dibujar los ejes coordenados, en este caso solo hace uno.

Fijarse en las librerias extenas que debe ser incluidas se encuentran el el fichero. funciones_ejes.c

*************************************************************/

// Recordar que previa a la compilación de este programa es preciso
// linkar las librerias glut32.lib y opengl32.lib


#include <windows.h>	//Inclusión de variables de windows

#include <glut.h>	    //Inclusión de GLUT
#include <GL/gl.h>		//Inclusión de GL
#include <GL/glu.h>
#include <stdio.h>
#include <math.h>	    //Inclusión de librerías auxiliares

const int W_WIDTH = 500;	//Ancho de la ventana
const int W_HEIGHT = 500;   //Alto de la ventana



// Ángulos de rotación
static GLfloat xRot = 0.0f;
static GLfloat yRot = 0.0f;


//Están el segundo archivo
extern myCamara();
extern void myTeclado(unsigned char tras, int x, int y);
extern void myTeclasespeciales(int cursor, int x, int y);


// Funcion de dibujo, funcion principal
void myDisplay(void) {


    // Clear the window with current clearing color
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


    // Inicializamos la matriz del modelo a la identidad
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    // Dibujamos los ejes coordenados. Segmentos de dos puntos cada uno con su color.
    glBegin(GL_LINES);
        // Eje X
        glColor3f(1.0f, 0.0f, 0.0f);
        glVertex3f(0.0f, 0.0f, 0.0f);
        glVertex3f(0.75f, 0.0f, 0.0f);

        // Eje Y
        glColor3f(0.0f, 1.0f, 0.0f);
        glVertex3f(0.0f, 0.0f, 0.0f);
        glVertex3f(0.0f, 0.75f, 0.0f);

        // Eje Z
        glColor3f(1.0f, 1.0f, 0.0f);
        glVertex3f(0.0f, 0.0f, 0.0f);
        glVertex3f(0.0f, 0.0f, 0.75f);
    glEnd();


    // Dibujo el segmento (0,0,0) - (1,1,1)

    glBegin(GL_LINES);
        glColor3f(1.0f, 1.0f, 1.0f);
        glVertex3f(0.0f, 0.0f, 0.0f);
        glVertex3f(0.35f, 0.35f, 0.35f);
    glEnd();

    glFlush();
    glutSwapBuffers();

}

// Esta función contiene muchas cosas no explicadas, por ahora las mantenemos ahí y las iremos explicado.
void openGlInit() {
    //Habilito aqui el depth en vez de arriba para los usuarios de linux y mac mejor en el main
    //Incializaciones varias
    glClearDepth(1.0f); //Valor z-buffer
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);  // valor limpieza buffer color
    glEnable(GL_DEPTH_TEST); // z-buffer
    glEnable(GL_CULL_FACE); //ocultacion caras back
    glCullFace(GL_BACK);
    glEnable(GL_NORMALIZE); // Normaliza las normales
}

int main(int argc, char** argv) {

    glutInit(&argc, argv);
    //Inicializa la ventana en una determinada posicion
    glutInitWindowPosition(0, 0);
    //Inicializa el tamano de la funcion
    glutInitWindowSize(W_WIDTH, W_HEIGHT);
    //Inicaliza el modeo de display, RGBA y Doble buffer
    glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE);
    // Nombre de la ventana
    glutCreateWindow("Generación de ejes");



    openGlInit();
    
    //Eventos teclado, teclas especiales
    glutKeyboardFunc(myTeclado);
    glutSpecialFunc(myTeclasespeciales);

    //Evento de dibujo
    glutDisplayFunc(myDisplay);


    // Empieza en bucle principal
    glutMainLoop();
    return 0;
}