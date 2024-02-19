/*****************************************************

Julian.flores@usc.es

Programas demo para clase -I Colores triángulos.

Dibuja únicamente un un triangulo

*************************************************************/

#define EJECUCION_EXITOSA 1

#include <windows.h>		// Inclusión de variables de Windows
#include <glut.h>	        // Inclusión de librerías GLUT
#include <GL/gl.h>			// Inclusión de librerías GL
#include <GL/glu.h>			// Inclusión de librerías auxiliares

const int W_WIDTH = 500;	// Ancho de la ventana
const int W_HEIGHT = 500;	// Alto de la ventana

// Función de dibujo
void Display(void) {

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // Limpia los buffer de color y profundidad

	// Triangulo superior
	glBegin(GL_TRIANGLES);
		// 
		glColor3f(1.0f, 1.0f, 1.0f);      // Blanco
		glVertex3f(0.0f, 0.0f, 0.0f);     // Punto central
									      
		glColor3f(1.0f, 1.0f, 0.0f);      // Amarillo
		glVertex3f(1.0f, 0.0f, 0.0f);     // Punto derecho
									      
		glColor3f(1.0f, 0.0f, 0.0f);      // Rojo
		glVertex3f(-0.5f, 0.866f, 0.0f);  // Punto superior 
	glEnd();

	// Triangulo inferior
	glBegin(GL_TRIANGLES);
	// 
		glColor3f(1.0f, 1.0f, 1.0f);      // Blanco
		glVertex3f(0.0f, 0.0f, 0.0f);     // Punto central

		glColor3f(0.0f, 1.0f, 0.0f);      // Verde
		glVertex3f(1.0f, 0.0f, 0.0f);     // Punto derecho

		glColor3f(0.0f, 0.5f, 0.5f);      // Verde windows
		glVertex3f(-0.5f, -0.866f, 0.0f);  // Punto inferior 
	glEnd();

	// Triangulo derecho
	glBegin(GL_TRIANGLES);
	// 
		glColor3f(1.0f, 1.0f, 1.0f);      // Blanco
		glVertex3f(0.0f, 0.0f, 0.0f);     // Punto central

		glColor3f(1.0f, 0.0f, 1.0f);      // Morado claro
		glVertex3f(-0.5f, 0.866f, 0.0f);  // Punto superior 

		glColor3f(0.5f, 0.0f, 0.5f);       // Morado oscuro
		glVertex3f(-0.5f, -0.866f, 0.0f);  // Punto inferior 
	glEnd();


	
	glutSwapBuffers(); // Intercambia los dos buffers gráficos disponibles
	glFlush();// Vacia todos los Buffers
}
int main(int argc, char **argv) {
	// Inicializa las GLUT
	glutInit(&argc, argv);
	// Inicializa el modo de la pantalla RGB y doble buffer
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE);
	// Fija el tamaño de la ventana
	glutInitWindowSize(W_WIDTH, W_HEIGHT);
	// Fija la posición de la ventana
	glutInitWindowPosition(100, 100);
	// Permite poner nombre a la ventana en la barra de título.
	glutCreateWindow("Ventana vacía creada con el Visual C++ y glut");

	glutDisplayFunc(Display);

//	Init();
	glutMainLoop();

	return EJECUCION_EXITOSA;
}
