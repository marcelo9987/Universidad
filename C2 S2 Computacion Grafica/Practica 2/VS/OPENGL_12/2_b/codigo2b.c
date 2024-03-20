/****************************************************************************
julian.flores@usc.es


El frustrum corresponde a la proyección
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

Usa la función glPolygonMode

******************************************************************************/



#include <windows.h>    // Inclusión de variables de Windows

#include <glut.h>       // Inclusión de GLUT
#include <GL/gl.h>      // Inclusión de GL
#include <GL/glu.h>

// Inclusión de librerías auxiliares
#include <stdio.h>
#include <math.h>

// #pragma comment(lib, "glut32.dll")

// --

// Están en el segundo archivo

extern myCamara(char *detalleAccion);

extern void myTeclado(unsigned char tras, int x, int y);

extern void myTeclasEspeciales(int cursor, int x, int y);
// --

const int W_WIDTH = 500;    //Ancho de la ventana
const int W_HEIGHT = 500;   //Alto de la ventana

// #define GL_PI M_PI // 3.14f

// Ángulos de rotación para la cámara
static GLfloat xRot = 0.0f;
static GLfloat yRot = 0.0f;



// Esta función contiene muchas cosas no explicadas, por ahora las mantenemos ahí y las iremos explicando.
void myOpenGlInit()
{
    //Habilito aquí el depth en vez de arriba; para los usuarios de linux y mac mejor en el main
    glClearDepth(1.0f); //Valor z-buffer

    glClearColor(0.0f, 0.0f, 0.0f, 1.0f); // valor limpieza buffer color


    glEnable(GL_CULL_FACE); // Habilita la ocultación de caras "back"

    glEnable(GL_NORMALIZE); // Normaliza las normales

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

// ##

void piramide()
{
    glColor3f(1.0f, 1.0f, 1.0f); //Blanco
    glBegin(GL_TRIANGLES);
    {
        glVertex3f(.5f, .5f, 0.0f);
        glVertex3f(.5f, -.5f, 0.0f);
        glVertex3f(-.5f, .5f, 0.0f);
    }
    glEnd();

    glColor3f(1.0f, 0.0f, 1.0f); // Morado
    glBegin(GL_TRIANGLES);
    {
        glVertex3f(.5f, .5f, 0.0f);
        glVertex3f(-.5f, .5f, 0.0f);
        glVertex3f(0.0f, .5f, 0.5f);
    }
    glEnd();

    glColor3f(0.0f, 1.0f, 0.0f); // Verde
    glBegin(GL_TRIANGLES);
    {
        glVertex3f(0.0f, .5f, 0.5f);
        glVertex3f(-.5f, .5f, 0.0f);
        glVertex3f(.5f, -.5f, 0.0f);
    }
    glEnd();

    glColor3f(1.0f, 0.0f, 0.0f);
    glBegin(GL_TRIANGLES);
    {
        glVertex3f(.5f, .5f, 0.0f);
        glVertex3f(0.0f, .5f, 0.5f);
        glVertex3f(.5f, -.5f, 0.0f);
    }
    glEnd();

}

void cubo_directo()
{
    glPolygonMode(GL_FRONT, GL_FILL);
    // glPolygonMode(GL_FRONT, GL_LINE);
    // glPolygonMode(GL_BACK, GL_LINE);

    glBegin(GL_TRIANGLES);
    {
        
        // Primer cuadrado: el de la derecha
        {
            glColor3f(1.0f, 1.0f, 1.0f); //White

            //t1
            glVertex3f(+0.5f, +0.5f, +0.5f);//RSF
            glVertex3f(+0.5f, -0.5f, +0.5f);//RIF
            glVertex3f(+0.5f, -0.5f, -0.5f);//RIT

            //t2
            glVertex3f(+0.5f, -0.5f, -0.5f);//RIT
            glVertex3f(+0.5f, +0.5f, -0.5f);//RST
            glVertex3f(+0.5f, +0.5f, +0.5f);//RSF
        }

        // Segundo cuadrado: el de arriba
        {
            glColor3f(1.0f, 0.0f, 0.0f); //Red

            //t1
            glVertex3f(+0.5f, +0.5f, +0.5f);//RSF
            glVertex3f(+0.5f, +0.5f, -0.5f);//RST
            glVertex3f(-0.5f, +0.5f, -0.5f);//LST

            //t2
            glVertex3f(+0.5f, +0.5f, +0.5f);//RSF
            glVertex3f(-0.5f, +0.5f, -0.5f);//LST
            glVertex3f(-0.5f, +0.5f, +0.5f);//LSF
        }


        // Tercer cuadrado: el frontal
        {
            glColor3f(0.0f, 0.0f, 1.0f); //Blue
            //t1
            glVertex3f(+0.5f, +0.5f, +0.5f);//RSF
            glVertex3f(-0.5f, +0.5f, +0.5f);//LSF
            glVertex3f(+0.5f, -0.5f, +0.5f);//RIF

            //t2
            glVertex3f(+0.5f, -0.5f, +0.5f);//RIF
            glVertex3f(-0.5f, +0.5f, +0.5f);//LSF
            glVertex3f(-0.5f, -0.5f, +0.5f);//LIF
        }

        // Cuarto cuadrado: el Trasero
        {
            glColor3f(1.0f, 0.5f, 0.0f); //Orange
            //t1
            glVertex3f(-0.5f, +0.5f, -0.5f);//LST
            glVertex3f(+0.5f, +0.5f, -0.5f);//RST
            glVertex3f(+0.5f, -0.5f, -0.5f);//RIT

            //t2
            glVertex3f(-0.5f, +0.5f, -0.5f);//LST
            glVertex3f(+0.5f, -0.5f, -0.5f);//RIT
            glVertex3f(-0.5f, -0.5f, -0.5f);//LIT
        }

        // Quinto cuadrado: el de la izquierda
        {
            glColor3f(1.0f, 1.0f, 0.0f); //Yellow

            //t1
            glVertex3f(-0.5f, -0.5f, +0.5f);//LIF
            glVertex3f(-0.5f, +0.5f, +0.5f);//LSF
            glVertex3f(-0.5f, -0.5f, -0.5f);//LIT

            //t2
            glVertex3f(-0.5f, +0.5f, -0.5f);//LST
            glVertex3f(-0.5f, -0.5f, -0.5f);//LIT
            glVertex3f(-0.5f, +0.5f, +0.5f);//LSF
        }

        // Sexto cuadrado: el de abajo
        {
            glColor3f(0.0f, 1.0f, 0.0f); //Red

            //t1
            glVertex3f(+0.5f, -0.5f, -0.5f);//RST
            glVertex3f(+0.5f, -0.5f, +0.5f);//RSF
            glVertex3f(-0.5f, -0.5f, -0.5f);//LST

            //t2
            glVertex3f(-0.5f, -0.5f, -0.5f);//LST
            glVertex3f(+0.5f, -0.5f, +0.5f);//RSF
            glVertex3f(-0.5f, -0.5f, +0.5f);//LSF
        }

    }
    glEnd();

}

GLuint cubo_preparaEnLista() {

    GLuint indiceListaParaElCubo = glGenLists(1); // Generamos un índice para la lista
    glNewList(indiceListaParaElCubo, GL_COMPILE); // Inicializamos la lista
    {

        glBegin(GL_TRIANGLES);
        {

            // Primer cuadrado: el de la derecha
            {
                glColor3f(1.0f, 1.0f, 1.0f); //White

                //t1
                glVertex3f(+0.5f, +0.5f, +0.5f);//RSF
                glVertex3f(+0.5f, -0.5f, +0.5f);//RIF
                glVertex3f(+0.5f, -0.5f, -0.5f);//RIT

                //t2
                glVertex3f(+0.5f, -0.5f, -0.5f);//RIT
                glVertex3f(+0.5f, +0.5f, -0.5f);//RST
                glVertex3f(+0.5f, +0.5f, +0.5f);//RSF
            }

            // Segundo cuadrado: el de arriba
            {
                glColor3f(1.0f, 0.0f, 0.0f); //Red

                //t1
                glVertex3f(+0.5f, +0.5f, +0.5f);//RSF
                glVertex3f(+0.5f, +0.5f, -0.5f);//RST
                glVertex3f(-0.5f, +0.5f, -0.5f);//LST

                //t2
                glVertex3f(+0.5f, +0.5f, +0.5f);//RSF
                glVertex3f(-0.5f, +0.5f, -0.5f);//LST
                glVertex3f(-0.5f, +0.5f, +0.5f);//LSF
            }


            // Tercer cuadrado: el frontal
            {
                glColor3f(0.0f, 0.0f, 1.0f); //Blue
                //t1
                glVertex3f(+0.5f, +0.5f, +0.5f);//RSF
                glVertex3f(-0.5f, +0.5f, +0.5f);//LSF
                glVertex3f(+0.5f, -0.5f, +0.5f);//RIF

                //t2
                glVertex3f(+0.5f, -0.5f, +0.5f);//RIF
                glVertex3f(-0.5f, +0.5f, +0.5f);//LSF
                glVertex3f(-0.5f, -0.5f, +0.5f);//LIF
            }

            // Cuarto cuadrado: el Trasero
            {
                glColor3f(1.0f, 0.5f, 0.0f); //Orange
                //t1
                glVertex3f(-0.5f, +0.5f, -0.5f);//LST
                glVertex3f(+0.5f, +0.5f, -0.5f);//RST
                glVertex3f(+0.5f, -0.5f, -0.5f);//RIT

                //t2
                glVertex3f(-0.5f, +0.5f, -0.5f);//LST
                glVertex3f(+0.5f, -0.5f, -0.5f);//RIT
                glVertex3f(-0.5f, -0.5f, -0.5f);//LIT
            }

            // Quinto cuadrado: el de la izquierda
            {
                glColor3f(1.0f, 1.0f, 0.0f); //Yellow

                //t1
                glVertex3f(-0.5f, -0.5f, +0.5f);//LIF
                glVertex3f(-0.5f, +0.5f, +0.5f);//LSF
                glVertex3f(-0.5f, -0.5f, -0.5f);//LIT

                //t2
                glVertex3f(-0.5f, +0.5f, -0.5f);//LST
                glVertex3f(-0.5f, -0.5f, -0.5f);//LIT
                glVertex3f(-0.5f, +0.5f, +0.5f);//LSF
            }

            // Sexto cuadrado: el de abajo
            {
                glColor3f(0.0f, 1.0f, 0.0f); //Red

                //t1
                glVertex3f(+0.5f, -0.5f, -0.5f);//RST
                glVertex3f(+0.5f, -0.5f, +0.5f);//RSF
                glVertex3f(-0.5f, -0.5f, -0.5f);//LST

                //t2
                glVertex3f(-0.5f, -0.5f, -0.5f);//LST
                glVertex3f(+0.5f, -0.5f, +0.5f);//RSF
                glVertex3f(-0.5f, -0.5f, +0.5f);//LSF
            }

        }
        glEnd();

    }
    glEndList(); // Finalizamos la lista

    return indiceListaParaElCubo; // Devolvemos el índice de la lista
}

void cubo_desdeLista(GLuint indiceListaParaElCubo)
{
    //  glPolygonMode(GL_FRONT, GL_FILL);
    glPolygonMode(GL_FRONT, GL_LINE);

    glTranslatef(-0.5f, -0.5f, -0.5);
    glCallList(indiceListaParaElCubo); // Llamamos a la lista

    glPolygonMode(GL_FRONT, GL_FILL);
    glTranslatef(-0.5f, 0.0f, -0.5f);
    glCallList(indiceListaParaElCubo); // Llamamos a la lista

    glTranslatef(-0.5f, 0.0f, 0.0f);
    glCallList(indiceListaParaElCubo); // Llamamos a la lista
}

// ##

// Función de dibujo (función principal)
void myDisplay(void)
{

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // Clear the window with current clearing color

    myCamara("INIT"); // Para colocar la camara; por ahora nada

    // Inicializamos la matriz del modelo a la identidad
    glMatrixMode(GL_MODELVIEW); //Matriz del Modelo
    glLoadIdentity(); // Inicializamos la matriz del modelo a la identidad

    myEjes(); // Dibujamos los ejes

    // Resto de figuras a dibujar

    // piramide();
    // cubo_directo();
    GLuint indiceListaParaElCubo = cubo_preparaEnLista();


    cubo_desdeLista(indiceListaParaElCubo);


    glFlush();
    glutSwapBuffers();

}


int main(int argc, char **argv)
{

    glutInit(&argc, argv);

    glutInitWindowPosition(0, 0); //Inicializa la ventana en una determinada posición

    glutInitWindowSize(W_WIDTH, W_HEIGHT); //Inicializa el tamaño de la función

    glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH); //Inicializa el modo de display, RGBA, Doble buffer y buffer de profundidad

    glutCreateWindow("Dibuja cubos"); // Nombre de la ventana

    myOpenGlInit(); // Incializaciones varias

    //Eventos comentado hasta la siguiente práctica

    glutKeyboardFunc(myTeclado); // Eventos teclado
    glutSpecialFunc(myTeclasEspeciales); // Teclas especiales

    glutDisplayFunc(myDisplay); //Evento de dibujo

    glutMainLoop(); // Empieza en bucle principal

    return 0;
}