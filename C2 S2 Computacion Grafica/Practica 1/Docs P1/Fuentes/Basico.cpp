
/*****************************************************

Julian.flores@usc.es

Programas demo para clase -I

*************************************************************/

// Recordar que previa a la compilaci�n de este programa es preciso
// linkar las librerías glut32.lib y opengl32.lib
// Recordar que previa a la compilaci�n de este programa es preciso
// linkar las librerías glut32.lib y opengl32.lib

#include <windows.h>		// Inclusi�n de variables de Windows
#include "glut.h"			// Inclusi�n de librer�as GLUT 
#include <GL/gl.h>			// Inclusi�n de librer�as GL
#include <GL/glu.h>			// Inclusi�n de librer�as auxiliares

// Funci�n de dibujo
void Display(void) {
	// Limpia los buffer de color y profundidad
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glFlush();// Intercambia los buffers gr�ficos disponibles
	glutSwapBuffers();
}

int main(int argc, char **argv) {
	// Inicializa las GLUT
	glutInit(&argc, argv);
	// Inicializa el modo de la pantalla RGB y doble buffer
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);
	// Fija el tama�o de la ventana
	glutInitWindowSize(500, 500);
	// Fija la posici�n de la ventana
	glutInitWindowPosition(100, 100);
	// Permite poner nombre a la ventana en la barra de t�tulo.
	glutCreateWindow("Ventana vacia creada con el Visual C++ y glut");

	// Inicializa la visualizaci�n
	glClearColor(1.0, 1.0, 1.0, 0.0);	// Fija el Blanco como color de borrado
	glClearDepth(1.0);				//Valor de limpieza del z-buffer

	glutDisplayFunc(Display);// Define las funciones de Callback  
	glutMainLoop(); // Inicia el lazo de visualizaci�n.
	return 0;
}