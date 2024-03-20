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

Usa la funcion glPolygonMode

******************************************************************************/



#include <windows.h>	//Inclusion de variables de windows

#include <glut.h>	//Inclusion de GLUT mira que la tienes ahi
#include <GL/GL.H>		//Inclusion de GL		 	
#include <GL/glu.h>	
#include <stdio.h>
#include <math.h>	//Inclusion de librerias auxiliares	


extern int myEsfera();
extern void myCamara();
extern void myTeclado(unsigned char tras, int x, int y);
extern void myTeclasespeciales(int cursor, int x, int y);

const int W_WIDTH = 500;	 //Ancho de la ventana
const int W_HEIGHT = 500;		//Alto de la ventana

GLuint myObjeto;

// #define GL_PI M_PI // 3.14f

// �ngulos de rotaci�n para la c�mara
static GLfloat xRot = 0.0f;
static GLfloat yRot = 0.0f;

//extern myCamara();

//extern void myTeclado(unsigned char tras,int x,int y);
//extern void myTeclasespeciales(int cursor,int x,int y) ;


/* funcion que dibuja los ejes*/
void myEjes () {

	
	
	glColor3f (0.0f,0.0f,1.0f);
	glBegin(GL_LINES);
	glVertex3f(0.0f,0.0f,0.0f);
	glVertex3f(.75f,0.0f,0.0f);
	glEnd();

	
	glColor3f (1.0f,0.0f,0.0f);
	glBegin(GL_LINES);
	glVertex3f(0.0f,0.0f,0.0f);
	glVertex3f(0.0f,.75f,0.0f);
	glEnd();

	
	glColor3f (0.0f,1.0f,0.0f);
	glBegin(GL_LINES);
	glVertex3f(0.0f,0.0f,0.0f);
	glVertex3f(0.0f,0.0,.75f);
	glEnd();

	//Diagonal
	glColor3f (1.0f,1.0f,1.0f);
	glBegin(GL_LINES);
	glVertex3f(0.0f,0.0f,0.0f);
	glVertex3f(.35f,.35,.35f);
	glEnd();
	
}
// Funcion de dibuk
void myDisplay (void) {
		

	// Clear the window with current clearing color
		
	 
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	//myCamara(); // para colocar la camara por ahora nada


	glMatrixMode(GL_MODELVIEW); //Matriz del Modelo
	glLoadIdentity(); // Inicializamos la matriz del modelo a la identidad
	
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	//myEjes();

//	glColor3f(1.0f, 1.0f, 1.0f);

	glCallList(myObjeto);

	glutSwapBuffers();
	glFlush();
	
		
}	
 


int main(int argc, char **argv) {

	glutInit(&argc, argv);
	
	glutInitWindowPosition(100,100);  
	glutInitWindowSize (W_WIDTH, W_HEIGHT);
	glutInitDisplayMode (GLUT_RGBA | GLUT_DOUBLE |GLUT_DEPTH);
	glutCreateWindow("Dibuja una esfera");
	

		
	
	glEnable(GL_CULL_FACE); // Habilita la ocultacion de caras
	glEnable(GL_NORMALIZE);


	//Eventos comentado hasta la siguiente practica
	glutKeyboardFunc(myTeclado);
	glutSpecialFunc(myTeclasespeciales);
	glutDisplayFunc(myDisplay);

	myObjeto = myEsfera();
	
	// Empieza en bucle principal
	glutMainLoop();
	return 0;
}