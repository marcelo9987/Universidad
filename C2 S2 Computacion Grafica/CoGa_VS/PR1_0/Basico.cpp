
/*****************************************************

Julian.flores@usc.es

Programas demo para clase -I

*************************************************************/

// Recordar que previa a la compilación de este programa es preciso
// linkar las librerias glut32.lib y opengl32.lib
// Recordar que previa a la compilación de este programa es preciso
// linkar las librerias glut32.lib y opengl32.lib

#include <windows.h>		// Inclusión de variables de Windows
#include "glut.h"			// Inclusión de librerías GLUT 
#include <GL/gl.h>			// Inclusión de librerías GL
#include <GL/glu.h>			// Inclusión de librerías auxiliares

// Función de dibujo
void Display(void) {
	// Limpia los buffer de color y profundidad
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glFlush();// Intercambia los buffers gráficos disponibles
	glutSwapBuffers();
}

int main(int argc, char **argv) {
	// Inicializa las GLUT
	glutInit(&argc, argv);
	// Inicializa el modo de la pantalla RGB y doble buffer
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);
	// Fija el tamaño de la ventana
	glutInitWindowSize(500, 500);
	// Fija la posición de la ventana
	glutInitWindowPosition(100, 100);
	// Permite poner nombre a la ventana en la barra de título.
	glutCreateWindow("Ventana vacia creada con el Visual C++ y glut");

	// Inicializa la visualización
	glClearColor(1.0, 1.0, 1.0, 0.0);	// Fija el Blanco como color de borrado
	glClearDepth(1.0);				//Valor de limpieza del z-buffer

	glutDisplayFunc(Display);// Define las funciones de Callback  
	glutMainLoop(); // Inicia el lazo de visualización.
	return 0;
}