#include <windows.h>

#include <glut.h>
#include <GL/gl.h>
#include <GL/glu.h>

#include <stdio.h>
#include <math.h>

// --

extern void myCamara();

extern void myTeclado(unsigned char tras, int x, int y);

extern void myTeclasEspeciales(int cursor, int x, int y);

// --

const int W_WIDTH = 500;
const int W_HEIGHT = 500;

GLfloat fAngulo_electron1, fAngulo_electron2, fAngulo_electron3;

// --

// Función de display
void myDisplay(void)
{

    // Clear the window with current clearing color

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Se activa la matriz del modelador
    glMatrixMode(GL_MODELVIEW);

    // Inicializamos la matriz del modelo a la identidad
    glLoadIdentity();

    glTranslatef(0.0f, 0.0f, -0.5f);

    // ## Núcleo
    {

        // Red Nucleus
        glColor3f(255, 0, 0);

        // Se dibuja una esfera
        glutSolidSphere(.1f, 20, 20);
    }

    // ## Primer electrón

    {
        // First Electron Orbit
        glColor3f(0, 100, 0);

        {
            // Save viewing transformation
            // Se hace un push - copiamos la traslación de -100 a la Pila
            glPushMatrix();

            // Rotate by angle of revolution
            // Sumamos a la translación
            glRotatef(fAngulo_electron1, 0.0f, 1.0f, 0.0f);

            // Translate out from origin to orbit distance
            // Sumamos a la trans+rotación
            glTranslatef(.5f, 0.0f, 0.0f);

            // Draw the electron
            glutSolidSphere(.1f, 20, 20);


            // Restore the viewing transformation
            // Se recupera la matriz de la pila
            glPopMatrix();

        }
    }

    // ## Segundo electrón

    {
        glColor3f(1, 1, 1);

        {
            glPushMatrix();

            glRotatef(fAngulo_electron2, 1.0f, 1.0f, 0.0f);
            glTranslatef(-0.5, 0.5, .0);
            glutWireSphere(.1f, 20, 20);

            glPopMatrix();
        }

    }

    //Tercer electrón
    {
        glColor3f(0, 0, 1);

        {
            glPushMatrix();

            glRotatef(fAngulo_electron3, -1.0f, 1.0f, 0.0f);
            glTranslatef(-0.5, -0.5, .0);
            //glutSolidSphere(.1f, 20, 20);
            glutWireSphere(.1f, 20, 20);

            glPopMatrix();
        }

    }

    // Se limpian los buffers
    glutSwapBuffers();
    glFlush();
}

// ##

void myStep(void)
{
    fAngulo_electron1 += 0.3f;
    if (fAngulo_electron1 > 360.0f)
    {
        fAngulo_electron1 -= 360.0f;
    }

    fAngulo_electron2 += 0.7f;
    if (fAngulo_electron2 > 360.0f)
    {
        fAngulo_electron2 -= 360.0f;
    }

    fAngulo_electron3 += 0.2f;
    if (fAngulo_electron3 > 360.0f)
    {
        fAngulo_electron3 -= 360.0f;
    }
    glutPostRedisplay();
}

// Para que cada electrón vaya a diferentes velocidades debes usar una variable (fAngulo) para cada electron.
void myIdle(void)
{
    //myStep(); //Se hace el movimiento
}

void myMovimiento(int value)
{

    myStep(); //Se hace el movimiento

    glutTimerFunc(5, myMovimiento, 0);// hace que se vuelva a ejecutar cada MYTIEMPO milisegundos

}

// ##

void myOpenGlInit()
{
    // Habilito aquí el depth en vez de arriba - para los usuarios de linux y mac mejor arriba

    // Incializaciones varias
    glClearDepth(1.0f);         // Valor z-buffer
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);  // Valor limpieza buffer color
    glEnable(GL_DEPTH_TEST);    // z-buffer
    glEnable(GL_CULL_FACE);     // Ocultación caras back
    glCullFace(GL_BACK);

}


int main(int argc, char **argv)
{

    glutInit(&argc, argv);

    // Posición de la ventana
    glutInitWindowPosition(100, 100);
    // Tamaño de la ventana
    glutInitWindowSize(W_WIDTH, W_HEIGHT);
    // Tipo de color y buffer
    glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE);
    // Crear la ventana
    glutCreateWindow("Ventana con el Visual C++ y glut");

    // Función que mira el teclado
    glutKeyboardFunc(myTeclado);

    glutSpecialFunc(myTeclasEspeciales);

    // Función de dibujo
    glutDisplayFunc(myDisplay);

    // --

    // Función de actualización
    glutIdleFunc(myIdle);

    myOpenGlInit();

    myMovimiento(1);

    // --

    // Lazo principal
    glutMainLoop();

    // --

    return 0;
}
