#include "comun.h"
#include "controles.h"
#include "sistemaSolar.h"
#include "cargasIniciales.h"
#include <locale.h>
#include <time.h>

//#pragma comment(lib,"glut32.dll")

// --


void pintarViewPort(GLint x, GLint y, GLsizei width, GLsizei height) {

	// Creamos un viewport para que sea "toda mi ventana" como un monitor

	glViewport(x, y, width, height);
	{

		// ==

		// Ponemos el color de fondo

		glClearColor(0.0, 0.0, 0.0, 0.0);


		glScissor(x, y, width, height);


		glEnable(GL_SCISSOR_TEST);
		glClear(GL_COLOR_BUFFER_BIT);
		glDisable(GL_SCISSOR_TEST);

		// ==

		glPushAttrib(GL_LINE_BIT | GL_CURRENT_BIT | GL_POLYGON_BIT | GL_ENABLE_BIT | GL_TRANSFORM_BIT);

		// ==

		// Ponemos un borde alrededor del viewport

		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();

		glOrtho(0, cs.window_width, 0, cs.window_height, -1, 1);

		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();

		glLineWidth(5.0);

		glDisable(GL_LIGHTING);


		//glPolygonMode(GL_FRONT, GL_FILL);
		//glPolygonMode(GL_BACK, GL_FILL);

		glColor3f(0.0f, 0.0f, 1.0f); // Azul

		// TODO: Recuperar color del sol en el sol

		glBegin(GL_LINE_LOOP);

		// TODO: Poner colores aleatorios
		// glColor3f( (rand() % 100)/100.0f, (rand() % 100)/100.0f, (rand() % 100)/100.0f );
		glVertex3f(1.0, cs.window_height + 1, 0);           // A /| 
		//glColor3f(0.0, 1.0, 0.0);

		// glColor3f((rand() % 100) / 100.0f, (rand() % 100) / 100.0f, (rand() % 100) / 100.0f);
		glVertex3f(cs.window_width, cs.window_height + 1, 0); // B |\
		        //glColor3f(0.0, 1.0, 0.0);

				// glColor3f((rand() % 100) / 100.0f, (rand() % 100) / 100.0f, (rand() % 100) / 100.0f);
		glVertex3f(cs.window_width, 0, 0);                   // C /
		//glColor3f(0.0, 1.0, 0.0);

		// glColor3f((rand() % 100) / 100.0f, (rand() % 100) / 100.0f, (rand() % 100) / 100.0f);
		glVertex3f(1.0, 0, 0);                              // D \
		        //glColor3f(0.0, 1.0, 0.0);
		glEnd();

		// ==

		glPopAttrib();

	}

}

char* preparaMensajeVistaActual(enum EnumCuerpoCeleste vista)
{
	switch (vista) {
	case VISTA_GENERAL:
		return "Vista General";
	case VISTA_GENERAL_CENITAL:
		return "Vista General Cenital";
	case SOL:
		return "El Sol desde la tierra";
	case MERCURIO:
		return "Mercurio dese la Tierra";
	case VENUS:
		return "Venus desde la Tierra";
	case MARTE:
		return "Marte desde la Tierra";
	case JUPITER:
		return "Jupiter desde la Tierra";
	case SATURNO:
		return "Saturno desde la Tierra";
	case URANO:
		return "Urano desde la Tierra";
	case NEPTUNO:
		return "Neptuno desde la Tierra";
	case PLUTON:
		return "Pluton desde la Tierra";
	case LUNA:
		return "La Tierra desde la Luna";
	case ISS:
		return "La Tierra desde la Estacion Espacial Internacional";
	case LUNA_DESDE_LA_TIERRA:
		return "La Luna desde la Tierra";
	case ISS_DESDE_LA_TIERRA:
		return "La Estacion Espacial Internacional desde la Tierra";
	}

	return NULL;
}

#define K_MAX_LEN_TEXT 200

// Función de display
void myDisplay(void) {
	// static bool primeraVez = true;

	// Clear the window with current clearing color

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// [Profundidad] Reserve 50% of the back depth range for the main window
	glDepthRange(0.5, 1.0);


	// Set the viewport to be the entire window
	// glViewport(0, 0, cs.window_width, cs.window_height);
	pintarViewPort(0, 0, cs.window_width, cs.window_height);
	{
		if (cs.mostrarTextos) {
			char mensaje[K_MAX_LEN_TEXT];

			// Velocidad
			sprintf_s(mensaje, K_MAX_LEN_TEXT, "Por cada segundo real, simulamos avanzar %s", K_VELOCIDAD_SPD_ARRAY[cs.chronos_segundosRealesPorDiaSimulado_posicionSeleccionada].nombreConfiguracion);
			imprimeTexto(0.1 * cs.window_width, 0.05 * cs.window_height, 1, 1, 1, GLUT_BITMAP_HELVETICA_18, mensaje);

			// Vista actual
			sprintf_s(mensaje, K_MAX_LEN_TEXT, "Vista actual: %s", preparaMensajeVistaActual(cs.visualizacionPrincipal));
			imprimeTexto(0.025 * cs.window_width, 0.95 * cs.window_height, 1, 1, 1, GLUT_BITMAP_HELVETICA_18, mensaje);

			// Zoom
			switch (cs.visualizacionPrincipal) {
			case VISTA_GENERAL:
			case VISTA_GENERAL_CENITAL:
			case SOL:
				sprintf_s(mensaje, K_MAX_LEN_TEXT, "Zoom: x%.2g", cs.camaraPrincipal.zoomCamara);
				imprimeTexto(0.80 * cs.window_width, 0.05 * cs.window_height, 1, 1, 1, GLUT_BITMAP_HELVETICA_18, mensaje);
				break;
			}
		}
		/*
			}

			glViewport(0, 0, cs.window_width, cs.window_height);
			{
		*/

		// Recalculamos la posición de la cámara
		// myCamara("ChangeSize");


		// Se activa la matriz del modelador
		glMatrixMode(GL_MODELVIEW);

		// Inicializamos la matriz del modelo a la identidad
		glLoadIdentity();



		//glLightfv(GL_LIGHT0, GL_POSITION, pos);

		seleccionaCamara(&cs.camaraPrincipal, cs.visualizacionPrincipal);


		// myEjes();




		// --

		//glPushMatrix();
		//representaCuerpoCeleste(&sol[0], tccSol, &cs.camaraPrincipal);
		representaCuerpoCeleste(&bovedaCelestial[0], tccBovedaCelestial, &cs.camaraPrincipal);
		//glPopMatrix();

		// --
		/*
		glDisable(GL_LIGHTING);

		for (GLfloat x = 0; x <= 100; x += 1.0) {
			for (GLfloat y = 0; y <= 100; y += 1.0) {
				for (GLfloat z = 0; z <= 100; z += 1.0) {
					myEstrella(x, y, z);
				}
			}
		}

		glEnable(GL_LIGHTING);
		*/
	}

	// --

#define __MOSTRAR_MONITORES__ 1

#if __MOSTRAR_MONITORES__

	if (cs.mostrarMonitores) {
		// [Profundidad] reserve 50% of the front depth range for the secondary viewports
		glDepthRange(0, 0.5);

		const float anchoBase = cs.window_width / 10.0;
		const float altoBase = cs.window_height / 10.0;

		// Monitor Visualización general
		pintarViewPort(1.0 * anchoBase, 1.0 * altoBase, 2.0 * anchoBase, 2.0 * altoBase);
		{
			imprimeTexto(1.1 * anchoBase, 1.1 * altoBase, 1, 1, 1, GLUT_BITMAP_HELVETICA_12, "Vista General");

			// Representamos nuestro sistema solar en este monitor

			// Se activa la matriz del modelador
			glMatrixMode(GL_MODELVIEW);

			// Inicializamos la matriz del modelo a la identidad
			glLoadIdentity();

			seleccionarVistaCamara(&cs.camarasSecundarias[0], VISTA_GENERAL);
			myCamaraVistaGeneral(&cs.camarasSecundarias[0]);

			//representaCuerpoCeleste(&sol[0], tccSol, &cs.camarasSecundarias[0]);
			representaCuerpoCeleste(&bovedaCelestial[0], tccBovedaCelestial, &cs.camarasSecundarias[0]);

			// myEjes();
		}

		// --

		// Monitor Visualización desde la Tierra a Saturno
		pintarViewPort(3.0 * anchoBase, 1.0 * altoBase, 2.0 * anchoBase, 2.0 * altoBase);
		{
			imprimeTexto(1.1 * anchoBase, 1.1 * altoBase, 1, 1, 1, GLUT_BITMAP_HELVETICA_12, "Saturno desde la Tierra");

			// Representamos nuestro sistema solar en este monitor

			// Se activa la matriz del modelador
			glMatrixMode(GL_MODELVIEW);

			// Inicializamos la matriz del modelo a la identidad
			glLoadIdentity();

			// myEjes();

			myCamaraDesdeLaTierraHaciaOtroPlaneta(&cs.camarasSecundarias[1], SATURNO);

			//representaCuerpoCeleste(&bovedaCelestial[0] /* &sol[0] */, tccSol, &cs.camarasSecundarias[1]);
			representaCuerpoCeleste(&bovedaCelestial[0], tccBovedaCelestial, &cs.camarasSecundarias[1]);

			//glLoadIdentity();
		}

		//--

		// Monitor Visualización desde la Luna a la Tierra
		pintarViewPort(5.0 * anchoBase, 1.0 * altoBase, 2.0 * anchoBase, 2.0 * altoBase);
		{
			imprimeTexto(1.1 * anchoBase, 1.1 * altoBase, 1, 1, 1, GLUT_BITMAP_HELVETICA_12, "La Tierra desde la Luna");

			// Se activa la matriz del modelador
			//glClear(GL_VIEWPORT_BIT);
			// Inicializamos la matriz del modelo a la identidad
			/* glLoadIdentity();*/

			glMatrixMode(GL_MODELVIEW);

			glLoadIdentity();

			/*glPushMatrix();*/
			//representaCuerpoCeleste(&sol[0], tccSol, &cs.camaraPrincipal);
			/*glPopMatrix();*/

			//myCamaraVistaGeneralCenital("Display");
			myCamaraHaciaLaTierra(&cs.camarasSecundarias[2], LUNA);

			//representaCuerpoCeleste(&bovedaCelestial[0] /* &sol[0] */, tccSol, &cs.camarasSecundarias[2]);
			representaCuerpoCeleste(&bovedaCelestial[0], tccBovedaCelestial, &cs.camarasSecundarias[2]);

			// myEjes();


		}

		//--

		// Monitor Visualización desde la Tierra a la Luna
		pintarViewPort(7.0 * anchoBase, 1.0 * altoBase, 2.0 * anchoBase, 2.0 * altoBase);
		{
			imprimeTexto(1.1 * anchoBase, 1.1 * altoBase, 1, 1, 1, GLUT_BITMAP_HELVETICA_12, "La Luna desde la Tierra");

			// Se activa la matriz del modelador
			glMatrixMode(GL_MODELVIEW);

			// Inicializamos la matriz del modelo a la identidad
			glLoadIdentity();

			myCamaraHaciaUnSateliteTerrestre(&cs.camarasSecundarias[3], LUNA);

			//representaCuerpoCeleste(&bovedaCelestial[0] /* &sol[0] */, tccSol, &cs.camarasSecundarias[3]);
			representaCuerpoCeleste(&bovedaCelestial[0], tccBovedaCelestial, &cs.camarasSecundarias[3]);

			// myEjes();


		}

		// [Profundidad] restore depth range
		glDepthRange(0, 1.0);

	}

#endif // __MOSTRAR_MONITORES__

	// Se limpian los buffers
	glutSwapBuffers();

	glFlush();

	// primeraVez = false;
}

// ##

void myStep(void) {

	// Actualizamos el tiempo simulado

	if (cs.chronos_segundosRealesPorDiaSimulado_posicionSeleccionada != 0) {
		double chronos_segundosRealesPorDiaSimulado = K_VELOCIDAD_SPD_ARRAY[cs.chronos_segundosRealesPorDiaSimulado_posicionSeleccionada].segundosRealesPorDiaSimulado;

		double deltaTiempoEnSegundosSimulados = 1.0 / (chronos_segundosRealesPorDiaSimulado * cs.chronos_framesPorSegundo);
		cs.chronos_diaActualmenteSimulado += deltaTiempoEnSegundosSimulados;
	}

	if (cs.solEncendido && cs.potenciaIluminacion < 90) {
		cs.potenciaIluminacion += 1;
	}
	else if (!cs.solEncendido && cs.potenciaIluminacion > 0) {
		cs.potenciaIluminacion -= 1;
	}

	actualizaCuerpoCeleste(&bovedaCelestial[0]);

	// myCamara("MyStep");


	glutPostRedisplay();
}

void myIdle(void) {
	//myStep(); //Se hace el movimiento
}

void myMovimiento(int value) {

	myStep(); //Se hace el movimiento

	glutTimerFunc(1000.0 / cs.chronos_framesPorSegundo, myMovimiento, 0);// hace que se vuelva a ejecutar cada MYTIEMPO milisegundos

}

// ##

void myOpenGlInit() {
	// Habilito aqui el depth en vez de arriba - para los usuarios de linux y mac mejor arriba

	// Incializaciones varias
	glClearDepth(1.0f);         //Valor z-buffer
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);  // Valor limpieza buffer color
	glEnable(GL_DEPTH_TEST);    // z-buffer
	glEnable(GL_CULL_FACE);     // Ocultación caras back
	glCullFace(GL_BACK);


	glEnable(GL_SMOOTH);
	glShadeModel(GL_SMOOTH);

}


int main(int argc, char** argv) {
	srand((unsigned int)time(NULL));

	//pongo el locale para que los decimales sean con punto y los acentos se vean bien
	setlocale(LC_ALL, "spanish");

	inicializaConfiguracionSistema(true);
	inicializaConfiguracionCamaras();

	glutInit(&argc, argv);

	// Posición de la ventana
	glutInitWindowPosition(100, 100);
	// Tamaño de la ventana
	glutInitWindowSize(cs.window_width, cs.window_height);
	// Tipo de color y buffer
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);
	// Crear la ventana
	glutCreateWindow("Sistema solar con C y glut");

	// --

	inicializaCuerpoCeleste(&bovedaCelestial[0]);

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
