

#include <windows.h>
#include <glut.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <math.h>

float Rot;



void idle(void) {

}

void myMovimiento(int value) {

	Rot += 5.0f;

	if (Rot > 360)
		Rot -= 360.0f;
	glutPostRedisplay(); //Se vuelve a hacer el dibujo

	glutTimerFunc(50, myMovimiento, 0);// hace que se vuelva a ejecutar cada MYTIEMPO milisegundos

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

void display(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


	//	Dibujo pantalla (0,0)
	glViewport(0, 0, 300, 300);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glColor3f(1.0f, 1.0f, 0.0f);

	glPushMatrix();
	glRotatef(Rot, 0.0f, 0.0f, 1.0f);
	glTranslatef(.5f, 0.0f, 0.0f);

	glutWireCube(.2);
	glPopMatrix();

	// Ejes
	glColor3f(1.0f, 1.0f, 1.0f);

	glBegin(GL_LINES);
	// Eje X
	glVertex3f(0.0f, 0.0f, 0.0f);
	glVertex3f(1.0f, 0.0f, 0.0f);

	// Eje Y
	glVertex3f(0.0f, 0.0f, 0.0f);
	glVertex3f(0.0f, 1.0f, 0.0f);

	// Eje Z
	glVertex3f(0.0f, 0.0f, 0.0f);
	glVertex3f(0.0f, 0.0f, -1.0f);
	glEnd();

	//	Dibujo Pantalla (1,0)
	glViewport(300, 0, 300, 300);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glColor3f(1.0f, 1.0f, 0.0f);

	glPushMatrix();
	//glScalef(3.0,3.0,3.0);
	glTranslatef(.5f, 0.0f, 0.0f);
	glRotatef(-Rot, 0.0f, 0.0f, 1.0f);

	glutWireCube(.2);
	glPopMatrix();


	// Ejes
	glColor3f(1.0f, 1.0f, 1.0f);

	glBegin(GL_LINES);
	// Eje X
	glVertex3f(0.0f, 0.0f, 0.0f);
	glVertex3f(9.0f, 0.0f, 0.0f);

	// Eje Y
	glVertex3f(0.0f, 0.0f, 0.0f);
	glVertex3f(0.0f, 9.0f, 0.0f);

	// Eje Z
	glVertex3f(0.0f, 0.0f, 0.0f);
	glVertex3f(0.0f, 0.0f, -9.0f);
	glEnd();

	glutSwapBuffers();
}

int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowSize(600, 300);
	glutInitWindowPosition(10, 10);
	glutCreateWindow("Composicion de movimientos");

	openGlInit();
	glutDisplayFunc(display);
	glutIdleFunc(idle);

	myMovimiento(1);

	glutMainLoop();

	return 0;
}