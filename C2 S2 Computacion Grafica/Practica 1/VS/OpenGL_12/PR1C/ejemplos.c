#include <windows.h>		// Inclusión de variables de Windows
#include <glut.h>	        // Inclusión de librerías GLUT
#include <GL/gl.h>			// Inclusión de librerías GL
#include <GL/glu.h>			// Inclusión de librerías auxiliares



// Función de dibujo
void myDisplay_tema2_38_1(void)
{


	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // Limpia los buffer de color y profundidad

	glPolygonMode(GL_FRONT, GL_FILL);
	glPolygonMode(GL_BACK, GL_LINES);

	glColor3f(1.0f, 0.0f, 0.0f);

	glBegin(GL_TRIANGLES);
	{
		glVertex3f(-0.5f, -0.5f, 0.0f); // 1

		glVertex3f(0.25f, -0.5f, 0.0f); // 2 

		glVertex3f(0.0f, 0.0f, 0.0f); // 3


		glColor3f(0.0f, 1.0f, 1.0f);
		glVertex3f(0.5f, 0.0f, 0.0f); // 4

		glColor3f(0.0f, 0.0f, 1.0f);
		glVertex3f(0.3f, 0.5f, 0.0f); // 5

	}
	glEnd();



	glutSwapBuffers(); // Intercambia los dos buffers gráficos disponibles
	glFlush();// Vacia todos los Buffers
}// Función de dibujo


void myDisplay_tema2_38_2(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // Limpia los buffer de color y profundidad

	glPolygonMode(GL_FRONT, GL_FILL);
	glPolygonMode(GL_BACK, GL_LINE);

	glColor3f(1.0f, 0.0f, 0.0f);

	glBegin(GL_TRIANGLES);
	{
		glVertex3f(0.0f, 0.0f, 0.0f); // 3

		glVertex3f(0.25f, -0.5f, 0.0f); // 2 

		glVertex3f(-0.5f, -0.5f, 0.0f); // 1


		glColor3f(0.0f, 1.0f, 1.0f);
		glVertex3f(0.0f, 0.0f, 0.0f); // 3

		//glColor3f(0.0f, 0.0f, 1.0f);
		glVertex3f(0.5f, 0.0f, 0.0f); // 4

		//glColor3f(0.0f, 1.0f, 0.0f);

		glVertex3f(0.3f, 0.5f, 0.0f); // 5
	}
	glEnd();



	glutSwapBuffers(); // Intercambia los dos buffers gráficos disponibles
	glFlush();// Vacia todos los Buffers
}

void myDisplay_tema2_38_3(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // Limpia los buffer de color y profundidad

	glPolygonMode(GL_FRONT, GL_FILL);
	glPolygonMode(GL_BACK, GL_LINE);

	glColor3f(1.0f, 0.0f, 0.0f);

	glBegin(GL_TRIANGLES);
	{
		glVertex3f(0.25f, -0.5f, 0.0f); // 2 

		glVertex3f(-0.5f, -0.5f, 0.0f); // 1

		glVertex3f(0.0f, 0.0f, 0.0f); // 3

		//glColor3f(0.0f, 0.0f, 1.0f);
		glVertex3f(0.5f, 0.0f, 0.0f); // 4

		glColor3f(0.0f, 1.0f, 1.0f);

		glVertex3f(0.0f, 0.0f, 0.0f); // 3

		glVertex3f(0.25f, -0.5f, 0.0f); // 2

		glVertex3f(0.0f, 0.0f, 0.0f); // 3

		glVertex3f(0.3f, 0.5f, 0.0f); // 5

		//glColor3f(0.0f, 0.0f, 1.0f);
		glVertex3f(0.5f, 0.0f, 0.0f); // 4

	}
	glEnd();



	glutSwapBuffers(); // Intercambia los dos buffers gráficos disponibles
	glFlush();// Vacia todos los Buffers
}

void myDisplay_tema2_39_1(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // Limpia los buffer de color y profundidad

	glPolygonMode(GL_FRONT, GL_FILL);
	glPolygonMode(GL_BACK, GL_LINE);

	glColor3f(1.0f, 0.0f, 0.0f);

	glBegin(GL_TRIANGLE_STRIP);
	{
		glVertex3f(0.25f, -0.5f, 0.0f); // 2 

		glVertex3f(-0.5f, -0.5f, 0.0f); // 1

		glVertex3f(0.0f, 0.0f, 0.0f); // 3

		glColor3f(0.0f, 0.0f, 1.0f);
		glVertex3f(0.5f, 0.0f, 0.0f); // 4

		glVertex3f(0.3f, 0.5f, 0.0f); // 5

	}
	glEnd();



	glutSwapBuffers(); // Intercambia los dos buffers gráficos disponibles
	glFlush();// Vacia todos los Buffers
}

void myDisplay_tema2_39_2(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // Limpia los buffer de color y profundidad

	glPolygonMode(GL_FRONT, GL_FILL);
	glPolygonMode(GL_BACK, GL_LINE);

	glColor3f(1.0f, 0.0f, 0.0f);

	glBegin(GL_TRIANGLE_STRIP);
	{
		glVertex3f(-0.5f, -0.5f, 0.0f); // 1

		glVertex3f(0.25f, -0.5f, 0.0f); // 2 

		glColor3f(0.0f, 1.0f, 1.0f);
		glVertex3f(0.0f, 0.0f, 0.0f); // 3

		glColor3f(0.0f, 0.0f, 1.0f);
		glVertex3f(0.5f, 0.0f, 0.0f); // 4

		glColor3f(0.0f, 1.0f, 0.0f);

		glVertex3f(0.3f, 0.5f, 0.0f); // 5
	}
	glEnd();



	glutSwapBuffers(); // Intercambia los dos buffers gráficos disponibles
	glFlush();// Vacia todos los Buffers
}