
#include "controles.h"
#include "sistemaSolar.h"
#include "cargasIniciales.h"

#define INCREMENTO .05


DWORD WINAPI ObtenerRespuestaAyuda(void *lpParam);

// --

const ConfiguracionVelocidadSimulacion K_VELOCIDAD_SPD_ARRAY[K_VELOCIDAD_SPD_ARRAY_SIZE] = {
        {INFINITY,              /**/ "detenido"},
        {24.0f * 60.0f * 60.0f, /**/ "1 segundo (tiempo real)"},
        {24.0f * 60.0f,         /**/ "1 minuto"},
        {24.0f * 10.0f,         /**/ "10 minutos"},
        {24.0f,                 /**/ "1 hora"},
        {1.0f,                  /**/ "1 dia"},
        {1.0f / 7.0f,           /**/ "1 semana"},
        {12.0f / 365.26f,       /**/ "1 mes"},
        {1.0f / 365.26f,        /**/ "1 anho"}
};
/*
const double K_VELOCIDAD_SPD_ARRAY[K_VELOCIDAD_SPD_ARRAY_SIZE] = {
		INFINITY,       // detenido
		24.0f,          // 1 hora por segundo
		1.0f,           // 1 día por segundo
		1.0f / 7.0f,    // 1 semana por segundo
		12.0f / 365.26f // 1 mes por segundo
};
*/
// --



// --

//void imprimeDatos(char* detalleAccion)
//{
//    printf("\n[DEBUG] %10s: alpha (LEFT-RIGHT): %f, beta(UP-DOWN): %f\n", detalleAccion, radianesAGrados(cs.camaraPrincipal.alpha), radianesAGrados(cs.camaraPrincipal.beta));
//}

void myChangeSize(GLint newWidth, GLint newHeight) {
    cs.window_width = newWidth;
    cs.window_height = newHeight;

    // Para no hacer divisiones por cero
    // No tiene sentido tener una ventana de tamaño 0, así que la ponemos a 1
    if (cs.window_height == 0) {
        cs.window_height = 1;
    }


    // Recalculamos la posición de la cámara
/*
		myCamara("ChangeSize");
	// Set the viewport to be the entire window
		glViewport(100, 100, cs.window_width/10.0, cs.window_height/10.0);

	// Recalculamos la posición de la cámara
		myCamara("ChangeSize");
*/

// Forzamos el redibujado
    glutPostRedisplay();
}


void myTeclado(unsigned char tras, int x, int y) {

    char *detalleAccion = "-----";

//	DWORD dwRespuestaAdquisicionAumentoDecremento;

    switch (tolower(tras)) {
        case 27: // Escape key (Salir)
            exit(0);
            break;


        case 'c': // Cerca
            cs.camaraPrincipal.zoomCamara *= 1.1f;

            if (cs.visualizacionPrincipal == VISTA_GENERAL || cs.visualizacionPrincipal == VISTA_GENERAL_CENITAL) {

                if (cs.camaraPrincipal.zoomCamara > 25.0f) {
                    cs.camaraPrincipal.zoomCamara = 25.0f;
                }
            } else { // Desde la Tierra al Sol
                if (cs.camaraPrincipal.zoomCamara > 7.0f) {
                    cs.camaraPrincipal.zoomCamara = 7.0f;
                }
            }

            detalleAccion = "CERCA";
            break;

        case 'e': // Easter Eggs
            cs.mostrarEasterEggs = !cs.mostrarEasterEggs;
            detalleAccion = "EASTER EGGS";
            break;

        case 'h': // Ayuda

            if(!cs.seMuestraAyuda){
                cs.seMuestraAyuda = true;

                // Nótese que la función tiene mayúscula por primera letra a razón de ser función de win32
                // Lanzamos un hilo para que ejecute el script de ayuda
                CreateThread(NULL, 0, ObtenerRespuestaAyuda, NULL, 0, NULL);
            }

            detalleAccion = "AYUDA";
            break;

        case 'l': // Lejos
            cs.camaraPrincipal.zoomCamara /= 1.1f;

            if (cs.visualizacionPrincipal == VISTA_GENERAL || cs.visualizacionPrincipal == VISTA_GENERAL_CENITAL) {

                if (cs.camaraPrincipal.zoomCamara < 0.20f) {
                    cs.camaraPrincipal.zoomCamara = 0.20f;
                }
            } else { // Desde la Tierra al Sol
                if (cs.camaraPrincipal.zoomCamara < 0.1f) {
                    cs.camaraPrincipal.zoomCamara = 0.1f;
                }
            }

            detalleAccion = "LEJOS";
            break;

        case 'm': // Mostrar monitores inferriores
            cs.mostrarMonitores = !cs.mostrarMonitores;
            detalleAccion = "MONITORES";
            break;

        case 'p': // Pausa
            /*
            // Adquirimos mutex de la variable cs.chronos_segundosRealesPorDiaSimulado_posicionSeleccionada para actualizarla
            dwRespuestaAdquisicionAumentoDecremento = WaitForSingleObject(mutexVelocidad, 500);
            if (dwRespuestaAdquisicionAumentoDecremento == WAIT_OBJECT_0) {
                cs.chronos_segundosRealesPorDiaSimulado_posicionSeleccionada = 0;
                ReleaseMutex(mutexVelocidad);
                dwRespuestaAdquisicionAumentoDecremento = -1;
            } else {
                printf_s("Error al obtener el mutex de la variable cs.chronos_segundosRealesPorDiaSimulado_posicionSeleccionada\n");
            }
            */
            cs.chronos_segundosRealesPorDiaSimulado_posicionSeleccionada = 0;

            detalleAccion = "PAUSA";
            break;

        case 'o': // Mostrar órbitas
            cs.camaraPrincipal.mostrarOrbitas = !cs.camaraPrincipal.mostrarOrbitas;

            detalleAccion = "ORBITAS";

            break;

        case 'r': // Reset
            inicializaConfiguracionSistema(false);
            inicializaConfiguracionCamaras();
            detalleAccion = "RESET";
            //cs.visualizacionPrincipal = VISTA_GENERAL;
            break;
            

        case 's': // Encender / Apagar el Sol
            cs.solEncendido = !cs.solEncendido;

            detalleAccion = "SOL";
            break;

        case '+': // Speed
/*
            // Incrementamos la velocidad
            // Para evitar conflictos, se adquiere el mutex de la variable cs.chronos_segundosRealesPorDiaSimulado_posicionSeleccionada
            dwRespuestaAdquisicionAumentoDecremento = WaitForSingleObject(mutexVelocidad, 500);
            if (dwRespuestaAdquisicionAumentoDecremento == WAIT_OBJECT_0) {
                cs.chronos_segundosRealesPorDiaSimulado_posicionSeleccionada += 1;
                if (cs.chronos_segundosRealesPorDiaSimulado_posicionSeleccionada >= K_VELOCIDAD_SPD_ARRAY_SIZE) {
                    cs.chronos_segundosRealesPorDiaSimulado_posicionSeleccionada = K_VELOCIDAD_SPD_ARRAY_SIZE - 1;
                }
                ReleaseMutex(mutexVelocidad);
                dwRespuestaAdquisicionAumentoDecremento = -1;
            } else {
                printf_s("Error al obtener el mutex de la variable cs.chronos_segundosRealesPorDiaSimulado_posicionSeleccionada\n");
            }
*/

            cs.chronos_segundosRealesPorDiaSimulado_posicionSeleccionada += 1;
            if (cs.chronos_segundosRealesPorDiaSimulado_posicionSeleccionada >= K_VELOCIDAD_SPD_ARRAY_SIZE) {
                cs.chronos_segundosRealesPorDiaSimulado_posicionSeleccionada = K_VELOCIDAD_SPD_ARRAY_SIZE - 1;
            }

            detalleAccion = "RAPIDO";
            break;

        case '-': // Speed
/*
            // Decrementamos la velocidad
            // Para evitar conflictos, se adquiere el mutex de la variable cs.chronos_segundosRealesPorDiaSimulado_posicionSeleccionada
            dwRespuestaAdquisicionAumentoDecremento = WaitForSingleObject(mutexVelocidad, 500);
            if (dwRespuestaAdquisicionAumentoDecremento == WAIT_OBJECT_0) {
                cs.chronos_segundosRealesPorDiaSimulado_posicionSeleccionada -= 1;
                if (cs.chronos_segundosRealesPorDiaSimulado_posicionSeleccionada <= 0) {
                    cs.chronos_segundosRealesPorDiaSimulado_posicionSeleccionada = 0;
                }
                ReleaseMutex(mutexVelocidad);
                dwRespuestaAdquisicionAumentoDecremento = -1;
            } else {
                printf_s("Error al obtener el mutex de la variable cs.chronos_segundosRealesPorDiaSimulado_posicionSeleccionada\n");
            }
*/

            cs.chronos_segundosRealesPorDiaSimulado_posicionSeleccionada -= 1;
            if (cs.chronos_segundosRealesPorDiaSimulado_posicionSeleccionada <= 0) {
                cs.chronos_segundosRealesPorDiaSimulado_posicionSeleccionada = 0;
            }

            detalleAccion = "LENTO";
            break;


        default:
            break;
    }

    // Recalculamos la posición de las cámaras
    //myCamaras(detalleAccion);

    // Si se ha modificado, algo se redibuja
    //glutPostRedisplay();
}

/**************************************
FUNCIÓN DE CONTROL DE TECLAS ESPECIALES:
**************************************
*/
void myTeclasEspeciales(int cursor, int x, int y) {
    char *detalleAccion = "-----";

    switch (cursor) {
        case GLUT_KEY_F1:
            break;
        case GLUT_KEY_F2:

            break;
        case GLUT_KEY_F3:

            break;
        case GLUT_KEY_F4:
            break;
        case GLUT_KEY_F5:

            break;
        case GLUT_KEY_F6:
            break;

        case GLUT_KEY_F10:
            inicializaConfiguracionSistema(false);
            inicializaConfiguracionCamaras();
            detalleAccion = "RESET";
            //cs.visualizacionPrincipal = VISTA_GENERAL;
            break;

            //Giros:
        case GLUT_KEY_UP:
            // Mover la cámara hacia arriba
            cs.camaraPrincipal.beta += INCREMENTO;
            detalleAccion = "UP";
            break;
        case GLUT_KEY_DOWN:
            // Mover la cámara hacia abajo
            cs.camaraPrincipal.beta -= INCREMENTO;
            detalleAccion = "DOWN";
            break;

        case GLUT_KEY_RIGHT:
            // Mover la cámara a la derecha
            cs.camaraPrincipal.alpha += INCREMENTO;
            detalleAccion = "RIGHT";
            break;
        case GLUT_KEY_LEFT:
            // Mover la cámara a la izquierda
            cs.camaraPrincipal.alpha -= INCREMENTO;
            detalleAccion = "LEFT";
            break;

        default:
            break;
    }

    // Izquierda y derecha
    if (cs.camaraPrincipal.alpha >= 2.0 * M_PI) {
        cs.camaraPrincipal.alpha -= 2.0 * M_PI;
    } else if (cs.camaraPrincipal.alpha < 0) {
        cs.camaraPrincipal.alpha += 2.0 * M_PI;
    }

    // Arriba y abajo
    if (cs.camaraPrincipal.beta >= M_PI / 2.0) {
        cs.camaraPrincipal.beta = M_PI / 2.0;
    } else if (cs.camaraPrincipal.beta < -M_PI / 2.0) {
        cs.camaraPrincipal.beta = -M_PI / 2.0;
    }

    // Recalculamos la posición de las cámaras
    //myCamaras(detalleAccion);

    // Forzamos el redibujado
    //glutPostRedisplay();

}

void iniciaMenu() {
    int satelitesTerrestresMenu = glutCreateMenu(seleccionadaDesdeMenuVistaCamaraVisualizacionPrincipal);
    glutAddMenuEntry("Luna", LUNA);
    glutAddMenuEntry("ISS", ISS);

    int desdeTierra = glutCreateMenu(seleccionadaDesdeMenuVistaCamaraVisualizacionPrincipal);
    glutAddMenuEntry("Sol", SOL);
    glutAddMenuEntry("Mercurio", MERCURIO);
    glutAddMenuEntry("Venus", VENUS);
    glutAddMenuEntry("Marte", MARTE);
    glutAddMenuEntry("Jupiter", JUPITER);
    glutAddMenuEntry("Saturno", SATURNO);
    glutAddMenuEntry("Urano", URANO);
    glutAddMenuEntry("Neptuno", NEPTUNO);
    glutAddMenuEntry("Pluton", PLUTON);
    glutAddMenuEntry("-- La Luna --", LUNA_DESDE_LA_TIERRA);
    glutAddMenuEntry("-- La Estacion Espacial Internacional --", ISS_DESDE_LA_TIERRA);

    int menuPrincipal = glutCreateMenu(seleccionadaDesdeMenuVistaCamaraVisualizacionPrincipal);
    glutAddMenuEntry("Vista general normal", VISTA_GENERAL);
    glutAddMenuEntry("Vista general cenital", VISTA_GENERAL_CENITAL);
    glutAddSubMenu("Enfocar desde la Tierra", desdeTierra);
    glutAddSubMenu("Enfocar la Tierra desde", satelitesTerrestresMenu);

    glutSetMenu(menuPrincipal);
    glutAttachMenu(GLUT_RIGHT_BUTTON);

}

void imprimeTexto(int x, int y, float r, float g, float b, void *font, char *texto) {
    // font is one of GLUT font constants :

    /*
    GLUT_BITMAP_8_BY_13
    GLUT_BITMAP_9_BY_15
    GLUT_BITMAP_TIMES_ROMAN_10
    GLUT_BITMAP_TIMES_ROMAN_24
    GLUT_BITMAP_HELVETICA_10
    GLUT_BITMAP_HELVETICA_12
    GLUT_BITMAP_HELVETICA_18
    */


    glColor3f(r, g, b);
    glRasterPos2f(x, y);
    int len = (int) strlen(texto);
    for (int i = 0; i < len; i++) {
        glutBitmapCharacter(font, texto[i]);
    }
}

DWORD WINAPI ObtenerRespuestaAyuda(void *lpParam) {
    //printf("Thread de ayuda\n");
    //ejecuto sobre.vbs bloqueando el programa
    // int posicionSeleccionadaAntigua;

    FILE *pArchivo = _popen("cscript.exe /nologo sobre.vbs", "r");
    if (pArchivo == NULL) {
        fprintf(stderr, "Error al abrir el archivo\n");
        exit(1);
    }

    //obtengo mutex de la variable cs.chronos_segundosRealesPorDiaSimulado_posicionSeleccionada para actualizarla
    /*
    DWORD dwRespuestaAdquisicionPausa = WaitForSingleObject(mutexVelocidad, 500);
    if (dwRespuestaAdquisicionPausa == WAIT_OBJECT_0) {
        posicionSeleccionadaAntigua = cs.chronos_segundosRealesPorDiaSimulado_posicionSeleccionada;
        cs.chronos_segundosRealesPorDiaSimulado_posicionSeleccionada = 0;
        ReleaseMutex(mutexVelocidad);
    } else {
        printf_s("Error al obtener el mutex de la variable cs.chronos_segundosRealesPorDiaSimulado_posicionSeleccionada\n");
    
    */

    char buffer[1000];
    while (fgets(buffer, 1000, pArchivo) != NULL) {
        printf("%s", buffer);
    }

    /*
    //obtengo mutex de la variable cs.chronos_segundosRealesPorDiaSimulado_posicionSeleccionada para actualizarla
    DWORD dwRespuestaAdquisicionDevolucion = WaitForSingleObject(mutexVelocidad, 500);
    if (dwRespuestaAdquisicionDevolucion == WAIT_OBJECT_0) {
        cs.chronos_segundosRealesPorDiaSimulado_posicionSeleccionada = cs.chronos_segundosRealesPorDiaSimulado_posicionSeleccionada == 0 ? posicionSeleccionadaAntigua : cs.chronos_segundosRealesPorDiaSimulado_posicionSeleccionada;
        ReleaseMutex(mutexVelocidad);
    } else {
        printf_s("Error al obtener el mutex de la variable cs.chronos_segundosRealesPorDiaSimulado_posicionSeleccionada\n");
    }
    */
    
    _pclose(pArchivo);

    cs.seMuestraAyuda = false;

    return 0;
}
	
