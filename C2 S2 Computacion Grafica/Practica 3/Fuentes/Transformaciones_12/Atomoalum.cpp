#include <windows.h>

#include <glut.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <stdio.h>

const int W_WIDTH = 500;
const int W_HEIGHT = 500;
GLfloat fAngulo;


// Funcion de teclado
void tecla(unsigned char c, int x, int y) {

	switch (c) {
	case 'a':    // Se ha pulsado la tecla 'a'
		break;
	case 'b':    // Se ha pulsado la tecla 'b'
		break;
	case 27:     // Se ha pulsado Esc. 
		exit(0); // Salimos del programa
		break;
	default:
		break;
	}

	// Si se ha modificado algo se redibuja
	glutPostRedisplay();
}


// Función de display
void Display(void) {

	// Clear the window with current clearing color
	
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// Se activa la matriz del modelador
	glMatrixMode(GL_MODELVIEW);
	// Inicializamos la matriz del modelo a la identidad
	glLoadIdentity();
	glTranslatef(0.0f, 0.0f, -.5f);

	// Red Nucleus
	glColor3f(255, 0, 0);

	// Se dibuja una esfera
	glutSolidSphere(.1f, 20, 20);


	// First Electron Orbit
	// Save viewing transformation
	glColor3f(0, 100, 0);
	// Se hace un push copiamos la traslacion  de -100 a la Pila
	glPushMatrix();

	// Rotate by angle of revolution
	//Sumamos a la translacion 
	glRotatef(fAngulo, 0.0f, 1.0f, 0.0f);

	// Translate out from origin to orbit distance
	//Sumamos a la trans+rotacion 
	glTranslatef(.5f, 0.0f, 0.0f);
	// Draw the electron
	glutSolidSphere(.1f, 20, 20);

	// Restore the viewing transformation
	// se recupera la matriz de la pila 
	glPopMatrix();

	// Se limpian los buffers
	glutSwapBuffers();
	glFlush();
}

// Para que cada electrón vaya a diferentes velocidades debes usar una variable (fAngulo) para cada electron.
void Idle(void) {
	fAngulo += 0.3f;
	if (fAngulo > 360)
		fAngulo -= 360.0f;
	glutPostRedisplay();
}

void openGlInit() {
	//Habilito aqui el depth en vez de arriba para los usuarios de linux y mac mejor arriba
	//Incializaciones varias
	glClearDepth(1.0f); //Valor z-buffer
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);  // valor limpieza buffer color
	glEnable(GL_DEPTH_TEST); // z-buffer
	glEnable(GL_CULL_FACE); //ocultacion caras back
	glCullFace(GL_BACK);

}


int main(int argc, char **argv) {

	glutInit(&argc, argv);
	//Posicion de la ventana
	glutInitWindowPosition(100, 100);
	//Tamano de la ventana
	glutInitWindowSize(W_WIDTH, W_HEIGHT);
	//Tipo de color y buffer
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE);
	//Crear la ventana
	glutCreateWindow("Ventana con el Visual C++ y glut");

	//Funcion de dibujo
	glutDisplayFunc(Display);
	//Funcion de actualizacion
	glutIdleFunc(Idle);
	//Funcion que mira el teclado
	glutKeyboardFunc(tecla);

	openGlInit();
	
	//Lazo principal
	glutMainLoop();
	return 0;
}