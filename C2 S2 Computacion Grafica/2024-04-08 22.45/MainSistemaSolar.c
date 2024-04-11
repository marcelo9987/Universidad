
#include "comun.h"
#include "controles.h"
#include "sistemaSolar.h"
#include "cargasIniciales.h"
#include <locale.h>

//#pragma comment(lib,"glut32.dll")

// --

// Función de display
void myDisplay(void)
{
    // static bool primeraVez = true;

    // Clear the window with current clearing color

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // --


    // Set the viewport to be the entire window
    glViewport(0, 0, cs.window_width, cs.window_height);
    {
        // Recalculamos la posición de la cámara
        // myCamara("ChangeSize");


        // Se activa la matriz del modelador
        glMatrixMode(GL_MODELVIEW);

        // Inicializamos la matriz del modelo a la identidad
        glLoadIdentity();
        


        //glLightfv(GL_LIGHT0, GL_POSITION, pos);
        

        switch (cs.visualizacionPrincipal)
        {

            case VISTA_GENERAL:
                myCamaraVistaGeneral("Display");
                break;

            case VISTA_GENERAL_CENITAL:
                myCamaraVistaGeneralCenital("Display");
                break;

            case SOL:
                myCamaraDesdeLaTierraHaciaElSol("Display");
                break;

            case LUNA:
            case ISS:
                myCamaraHaciaLaTierra("Display", cs.visualizacionPrincipal);
                break;

            case LUNA_DESDE_LA_TIERRA:
            case ISS_DESDE_LA_TIERRA:
                myCamaraHaciaUnSateliteTerrestre("Display", (cs.visualizacionPrincipal == LUNA_DESDE_LA_TIERRA)?LUNA:ISS);
                break;

            default:
                myCamaraDesdeLaTierraHaciaOtroPlaneta("Display", cs.visualizacionPrincipal);
                break;
        }
        // myEjes();

        
    }
    //glPushMatrix();
    representaCuerpoCeleste(&sol);
    //glPopMatrix();


    // --

    // Monitor Visualización general

    // Set the viewport to be the entire window
    glViewport(1.0 * cs.window_width / 10.0, 1.0 * cs.window_height / 10.0, cs.window_width / 5.0, cs.window_height / 5.0);
    {

        // Se activa la matriz del modelador
        glMatrixMode(GL_MODELVIEW);

        // Inicializamos la matriz del modelo a la identidad
        glLoadIdentity();


        myCamaraVistaGeneral("Display");
        representaCuerpoCeleste(&sol);

        // myEjes();

        
    }

    // --
#ifdef __XX__

    // Monitor Visualización desde la Tierra a Saturno
    // 
    // Set the viewport to be the entire window
    glViewport(3.0 * cs.window_width / 10.0, 1.0 * cs.window_height / 10.0, cs.window_width / 5.0, cs.window_height / 5.0);
    {

        // Se activa la matriz del modelador
        glMatrixMode(GL_MODELVIEW);

        // Inicializamos la matriz del modelo a la identidad
        glLoadIdentity();

       

        // myEjes();

       
        myCamaraDesdeLaTierraHaciaOtroPlaneta("Display", SATURNO);
        representaCuerpoCeleste(&sol);

        //glLoadIdentity();
    }

    // --

    // Monitor Visualización desde la Luna a la Tierra
    // 
    // Set the viewport to be the entire window
    //glPushMatrix();
    glLoadIdentity();
    glViewport(5.0 * cs.window_width / 10.0, 1.0 * cs.window_height / 10.0, cs.window_width / 5.0, cs.window_height / 5.0);
    {
        
        // Se activa la matriz del modelador
        //glClear(GL_VIEWPORT_BIT);
        // Inicializamos la matriz del modelo a la identidad
       /* glLoadIdentity();*/

        glMatrixMode(GL_MODELVIEW);

        /*glPushMatrix();*/
        //representaCuerpoCeleste(&sol);
        /*glPopMatrix();*/
        
        //myCamaraVistaGeneralCenital("Display");
        myCamaraHaciaLaTierra("Display", LUNA);
        representaCuerpoCeleste(&sol);
        
        
        // myEjes();

       
    }
    
    // --

    // Monitor Visualización desde la Tierra a la Luna
    // 
    // Set the viewport to be the entire window
    glViewport(7.0 * cs.window_width / 10.0, 1.0 * cs.window_height / 10.0, cs.window_width / 5.0, cs.window_height / 5.0);
    {

        // Se activa la matriz del modelador
        glMatrixMode(GL_MODELVIEW);

        // Inicializamos la matriz del modelo a la identidad
        glLoadIdentity();

        

        myCamaraHaciaUnSateliteTerrestre("Display", LUNA);
        representaCuerpoCeleste(&sol);

        // myEjes();

        
    }

    // --
#endif // __XX__

    // Se limpian los buffers
    glutSwapBuffers();

    glFlush();

    // primeraVez = false;
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

    // myCamara("MyStep");


    glutPostRedisplay();
}

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


    glEnable(GL_SMOOTH);
    glShadeModel(GL_SMOOTH);

    //iluminaCuerpoCelesteNoEmisor();

    enciendeLuces();

}


int main(int argc, char** argv)
{
    //pongo el locale para que los decimales sean con punto y los acentos se vean bien
    setlocale(LC_ALL, "spanish");

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

    glutReshapeFunc(myChangeSize);

    // --
    // Función de actualización
    glutIdleFunc(myIdle);

    myOpenGlInit();

    iniciaMenu();

    myMovimiento(1);

    // Recalculamos la posición de la cámara
    //myCamaras("START");

    glutPostRedisplay();

    // --

    // Lazo principal
    glutMainLoop();

    // --

    return 0;
}
