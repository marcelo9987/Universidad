// Programa que abre una ventana vacia de openGl con GLUT

/***************************************NOTA*******************************************/
//// Recordar que previa a la compilación de este programa es preciso
//// linkar las librerías glut32.lib y opengl32.lib
//// Para su ejecución debe estar correctamente colocado la glut32.dll
/*************************************************************************************/

#include <stdio.h>
#include <windows.h>		// Inclusión de variables de Windows
#include <glut.h>			// Inclusión de librerías GLUT
#include <GL/gl.h>			// Inclusión de librerías GL
#include <GL/glu.h>			// Inclusión de librerías auxiliares

const int W_WIDTH = 500;	// Ancho de la ventana
const int W_HEIGHT = 500;	// Alto de la ventana

// Función de dibujo
void myDisplay(void) {

    //	glClearColor(1.0,1.0,1.0,0.0);	// Fija el Blanco como color de borrado
    glClearColor(1.0, 0.0, 0.0, 0.0);	// Fija el Negro como color de borrado
    glClearDepth(1.0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Intercambia los dos buffers gráficos disponibles
    glutSwapBuffers(); // buffer de glut
    glFlush();			//buffer de openGL
}

int main(int argc, char** argv) {
    // Inicializa las GLUT
    glutInit(&argc, argv);

    glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE); // Inicializa el modo de la pantalla RGB y doble buffer
    glutInitWindowSize(W_WIDTH, W_HEIGHT); // Fija el tamaño de la ventana
    glutInitWindowPosition(100, 100); // Fija la posición de la ventana
    glutCreateWindow("Ventana vacía creada con el Visual C++ y glut"); // Permite poner nombre a la ventana en la barra de título.

    glutDisplayFunc(myDisplay); // Define las funciones de Callback

    // Inicia el lazo de visualización.
    glutMainLoop();
    return 0;
}