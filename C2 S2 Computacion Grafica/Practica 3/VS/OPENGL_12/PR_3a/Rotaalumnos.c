

#include <windows.h>
#include <glut.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <math.h>

extern void myCamara();
extern void myTeclado(unsigned char tras, int x, int y);
extern void myTeclasEspeciales(int cursor, int x, int y);



float Rot;



void myIdle(void)
{

}


// Función que dibuja los ejes
void myEjes()
{
    // Eje X
    glColor3f(1.0f, 0.0f, 0.0f);    // Red
    //  glColor3f(0.0f, 0.0f, 1.0f);    // Blue
    glBegin(GL_LINES);
    {
        glVertex3f(0.0f, 0.0f, 0.0f);
        glVertex3f(0.75f, 0.0f, 0.0f);
    }
    glEnd();

    // Eje Y
    glColor3f(0.0f, 1.0f, 0.0f);    // Green
    //  glColor3f(1.0f, 0.0f, 0.0f);    // Red
    glBegin(GL_LINES);
    {
        glVertex3f(0.0f, 0.0f, 0.0f);
        glVertex3f(0.0f, 0.75f, 0.0f);
    }
    glEnd();

    // Eje Z
    glColor3f(0.0f, 0.0f, 1.0f);    // Blue
    //  glColor3f(0.0f, 1.0f, 0.0f);    // Green
    glBegin(GL_LINES);
    {
        glVertex3f(0.0f, 0.0f, 0.0f);
        glVertex3f(0.0f, 0.0f, 0.75f);
    }
    glEnd();

    // Diagonal - segmento (0,0,0) - (1,1,1)
    glColor3f(1.0f, 1.0f, 1.0f);    // White
    glBegin(GL_LINES);
    {
        glVertex3f(0.0f, 0.0f, 0.0f);
        glVertex3f(0.35f, 0.35f, 0.35f);
    }
    glEnd();
}

void myMovimiento(int value)
{

    Rot += 5.0f;

    if (Rot > 360.0f)
    {
        Rot -= 360.0f;
    }

    glutPostRedisplay(); //Se vuelve a hacer el dibujo

    glutTimerFunc(50, myMovimiento, 0);// hace que se vuelva a ejecutar cada MYTIEMPO milisegundos

}

void myOpenGlInit()
{
    //Habilito aquí el depth en vez de arriba - para los usuarios de linux y mac mejor arriba
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
    {

        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();

        glColor3f(1.0f, 1.0f, 0.0f);

        glPushMatrix();
        
        {
            glRotatef(Rot, 0.0f, 0.0f, 1.0f);
            glTranslatef(.5f, 0.0f, 0.0f);

            glutWireCube(.2);
        }

        glPopMatrix();

        // Ejes


        glBegin(GL_LINES);
        {
            // Eje X
            glColor3f(1.0f, 0.0f, 0.0f);
            glVertex3f(0.0f, 0.0f, 0.0f);
            glVertex3f(1.0f, 0.0f, 0.0f);

            // Eje Y
            glColor3f(0.0f, 1.0f, 0.0f);
            glVertex3f(0.0f, 0.0f, 0.0f);
            glVertex3f(0.0f, 1.0f, 0.0f);

            // Eje Z
            glColor3f(0.0f, 0.0f, 1.0f);
            glVertex3f(0.0f, 0.0f, 0.0f);
            glVertex3f(0.0f, 0.0f, -1.0f);
        }
        glEnd();
    }

    //	Dibujo Pantalla (1,0)
    glViewport(300, 0, 300, 300);
    {

        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();

        glColor3f(1.0f, 1.0f, 0.0f);

        glPushMatrix();

        {
            //glScalef(3.0,3.0,3.0);
            glTranslatef(.5f, 0.0f, 0.0f);
            glRotatef(-Rot, 0.0f, 0.0f, 1.0f);

            glutWireCube(.2);
        }

        glPopMatrix();


        // Ejes
        glColor3f(1.0f, 1.0f, 1.0f);

        glBegin(GL_LINES);
        {
            // Eje X
            glColor3f(1.0f, 0.0f, 0.0f);
            glVertex3f(0.0f, 0.0f, 0.0f);
            glVertex3f(9.0f, 0.0f, 0.0f);

            // Eje Y
            glColor3f(0.0f, 1.0f, 0.0f);
            glVertex3f(0.0f, 0.0f, 0.0f);
            glVertex3f(0.0f, 9.0f, 0.0f);

            // Eje Z
            glColor3f(0.0f, 0.0f, 1.0f);
            glVertex3f(0.0f, 0.0f, 0.0f);
            glVertex3f(0.0f, 0.0f, -9.0f);
        }
        glEnd();
    }

    glutSwapBuffers();
}

int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(600, 300);
    glutInitWindowPosition(10, 10);
    glutCreateWindow("Composicion de movimientos");

    myOpenGlInit();
    glutDisplayFunc(display);
    glutIdleFunc(myIdle);

    myMovimiento(1);

    glutKeyboardFunc(myTeclado);
    glutSpecialFunc(myTeclasEspeciales);

    glutMainLoop();

    return 0;
}
