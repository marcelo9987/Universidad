
#include "controles.h"
#include "sistemaSolar.h"
#include "cargasIniciales.h"

// --

ConfiguracionSistema cs;

// --

// Función de display
void myDisplay(void)
{
    static bool primeraVez = true;


    // Clear the window with current clearing color

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Se activa la matriz del modelador
    glMatrixMode(GL_MODELVIEW);

    // Inicializamos la matriz del modelo a la identidad
    glLoadIdentity();

//    myEjes();

    // representaSol(&sol, primeraVez);
    
    representaCuerpoCeleste(&sol, primeraVez);

    //// Sol
    //representaSol(&sol, primeraVez);

    //for (int pos = 0; pos < K_NUM_PLANETAS; pos++)
    //{
    //    representaCuerpoCeleste(&planetas[pos], primeraVez);
    //}



    // Se limpian los buffers
    glutSwapBuffers();
    glFlush();

    primeraVez = false;
}

// ##

void myStep(void)
{
    if (cs.chronos_segundosRealesPorDiaSimulado_posicionSeleccionada != 0)
    {
        float chronos_segundosRealesPorDiaSimulado = K_VELOCIDAD_SPD_ARRAY[cs.chronos_segundosRealesPorDiaSimulado_posicionSeleccionada];

        float deltaTiempoEnSegundosSimulados = 1.0 / (chronos_segundosRealesPorDiaSimulado * cs.chronos_framesPorSegundo);
        cs.chronos_diaActualmenteSimulado += deltaTiempoEnSegundosSimulados;
    }

    actualizaDatosCuerpoCeleste(&sol);

    myCamara("MyStep");

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

    glutTimerFunc(1000.0 / cs.chronos_framesPorSegundo, myMovimiento, 0);// hace que se vuelva a ejecutar cada MYTIEMPO milisegundos

}

// ##

void myOpenGlInit()
{
    // Habilito aqui el depth en vez de arriba - para los usuarios de linux y mac mejor arriba

    // Incializaciones varias
    glClearDepth(1.0f);         //Valor z-buffer
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);  // Valor limpieza buffer color
    glEnable(GL_DEPTH_TEST);    // z-buffer
    glEnable(GL_CULL_FACE);     // Ocultación caras back
    glCullFace(GL_BACK);

}



int main(int argc, char** argv)
{

    inicializaConfiguracionSistema();
    inicializaConfiguracionCamara();

    glutInit(&argc, argv);

    // Posición de la ventana
    glutInitWindowPosition(100, 100);
    // Tamaño de la ventana
    glutInitWindowSize(cs.window_width, cs.window_height);
    // Tipo de color y buffer
    glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);
    // Crear la ventana
    glutCreateWindow("Ventana con el Visual C++ y glut");

    inicializaPosicionCuerpoCeleste(&sol);

    // Función que mira el teclado
    glutKeyboardFunc(myTeclado);

    glutSpecialFunc(myTeclasEspeciales);

    // Función de dibujo
    glutDisplayFunc(myDisplay);

    // --
    // Función de actualización
    glutIdleFunc(myIdle);

    myOpenGlInit();

    iniciaMenu();

    myMovimiento(1);

    // Recalculamos la posición de la cámara
    myCamara("START");

    // --

    // Lazo principal
    glutMainLoop();

    // --

    return 0;
}
