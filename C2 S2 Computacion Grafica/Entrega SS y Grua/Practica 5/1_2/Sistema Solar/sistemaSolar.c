#include "controles.h"

#include "sistemaSolar.h"
#include "figurasGeometricas.h"


// --

void loDelSol() {

    //glClear(GL_LIGHTING_BIT);
    //shade_model(GL_FLAT;)

    if (cs.solEncendido) {
        glDisable(GL_LIGHTING);
        glDisable(GL_LIGHT0);
        glDisable(GL_LIGHT1);

        // glDisable(GL_LIGHT2);
        // glDisable(GL_LIGHT3);
	}
	else {
        // glEnable(GL_LIGHTING);
        // glEnable(GL_LIGHT0);
        // glEnable(GL_LIGHT1);

        // glEnable(GL_LIGHT2);
        // glEnable(GL_LIGHT3);
	}

    // Ponemos el color de fondo adecuado, porque la textura es transparente en parte
    glColor3f(sol->color[0], sol->color[1], sol->color[2]);

    GLfloat sun_mat_ambient[] = { 0.5f, 0.5f, 0.5f, 0.5f };
    GLfloat sun_mat_diffuse[] = { 1.0f, 1.0f, 1.0f, 1.0f };
    // GLfloat sun_mat_specular[] = { 0.5f, 0.5f, 0.5f, 0.5f };
    // GLfloat sun_mat_emission[] = { 0.8f, 0.8f, 0.8f, 1.0f };
    // GLfloat sun_mat_shininess = 1.0f;

    glMaterialfv(GL_FRONT, GL_AMBIENT, sun_mat_ambient);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, sun_mat_diffuse);
    // glMaterialfv(GL_FRONT, GL_SPECULAR, sun_mat_specular);
    // glMaterialfv(GL_FRONT, GL_EMISSION, sun_mat_emission);
    // glMaterialf(GL_FRONT, GL_SHININESS, sun_mat_shininess);
}

void loDelResto(int potenciaIluminacion ) {

    glClearColor(0.0, 0.0, 0.0, 0.0);

    if (true) {
        //glEnable(GL_DEPTH_TEST);
        //glEnable(GL_SMOOTH);
        //glShadeModel(GL_SMOOTH);

        glEnable(GL_LIGHTING);
        glEnable(GL_LIGHT0);
        glEnable(GL_LIGHT1);

        //glEnable(GL_LIGHT2);
        //glEnable(GL_LIGHT3);

    }

    glMatrixMode(GL_MODELVIEW);
    //glLoadIdentity();


    GLfloat posSol[] = { 0, 0, 0, 1.0 };

    GLfloat direccionFocoSol0[] = { 1.00f , 0.00f ,  0.00f , 1.00f };
    GLfloat direccionFocoSol1[] = { -1.00f , 0.00f ,  0.00f , 1.00f };
    //GLfloat direccionFocoSol2[] = {  0.00f , 0.00f ,  1.00f , 1.00f };
    //GLfloat direccionFocoSol3[] = {  0.00f , 0.00f , -1.00f , 1.00f };


    GLfloat lightAmb[] = { 0.25f , 0.25f , 0.25f , 0.5f };
    GLfloat lightDif[] = { 1.00f , 1.00f , 1.00f , 1.0f };
    GLfloat lightSpc[] = { 1.00f , 1.00f , 1.00f , 1.0f };

    if (true) {
        glLightfv(GL_LIGHT0, GL_POSITION, posSol);
        glLightfv(GL_LIGHT1, GL_POSITION, posSol);
        //glLightfv(GL_LIGHT2, GL_POSITION, posSol);
        //glLightfv(GL_LIGHT3, GL_POSITION, posSol);

        glLightfv(GL_LIGHT0, GL_SPOT_DIRECTION, direccionFocoSol0);
        glLightfv(GL_LIGHT1, GL_SPOT_DIRECTION, direccionFocoSol1);
        //glLightfv(GL_LIGHT2, GL_SPOT_DIRECTION, direccionFocoSol2);
        //glLightfv(GL_LIGHT3, GL_SPOT_DIRECTION, direccionFocoSol3);

        // glLighti(GL_LIGHT0, GL_SPOT_CUTOFF, 180);
        glLightfv(GL_LIGHT0, GL_AMBIENT, lightAmb);
        glLightfv(GL_LIGHT1, GL_AMBIENT, lightAmb);
        //glLightfv(GL_LIGHT2, GL_AMBIENT, lightAmb);
        //glLightfv(GL_LIGHT3, GL_AMBIENT, lightAmb);

        glLightfv(GL_LIGHT0, GL_DIFFUSE, lightDif);
        glLightfv(GL_LIGHT1, GL_DIFFUSE, lightDif);
        //glLightfv(GL_LIGHT2, GL_DIFFUSE, lightDif);
        //glLightfv(GL_LIGHT3, GL_DIFFUSE, lightDif);

        glLightfv(GL_LIGHT0, GL_SPECULAR, lightSpc);
        glLightfv(GL_LIGHT1, GL_SPECULAR, lightSpc);
        //glLightfv(GL_LIGHT2, GL_SPECULAR, lightSpc);
        //glLightfv(GL_LIGHT3, GL_SPECULAR, lightSpc);


        glLighti(GL_LIGHT0, GL_SPOT_CUTOFF, potenciaIluminacion);
        glLighti(GL_LIGHT1, GL_SPOT_CUTOFF, potenciaIluminacion);
        // glLighti(GL_LIGHT2, GL_SPOT_CUTOFF, potenciaIluminacion);
        // glLighti(GL_LIGHT3, GL_SPOT_CUTOFF, potenciaIluminacion);


        /*glEnable(GL_LIGHT0);
        glEnable(GL_LIGHTING);*/
    }

    GLfloat mat_ambient[] = { 0.5f, 0.5f, 0.5f, 1.0f };
    GLfloat mat_diffuse[] = { 0.9f, 0.9f, 0.9f, 1.0f };
    // GLfloat mat_specular[] = { 0.0f, 0.0f, 1.0f, 1.0f };
    // GLfloat mat_emission[] = { 0.0f, 0.0f, 0.0f, 1.0f };
    // GLfloat mat_shininess = 0.0f;

    glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
    // glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
    // glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, mat_emission);
    // glMaterialf(GL_FRONT, GL_SHININESS, mat_shininess);

}


void actualizaCuerpoCeleste(CuerpoCeleste* cuerpoCeleste) {

    if (fpclassify(cuerpoCeleste->periodoTraslacion) != FP_ZERO && cs.chronos_segundosRealesPorDiaSimulado_posicionSeleccionada != 0) {

        cuerpoCeleste->posicion->anguloTraslacion = cs.chronos_diaActualmenteSimulado * (360.0 / cuerpoCeleste->periodoTraslacion);

        cuerpoCeleste->posicion->anguloTraslacion = fmod(cuerpoCeleste->posicion->anguloTraslacion, 360.0);

    }

    // --

    if (fpclassify(cuerpoCeleste->periodoRotacion) != FP_ZERO && cs.chronos_segundosRealesPorDiaSimulado_posicionSeleccionada != 0) {

        cuerpoCeleste->posicion->anguloRotacion = cs.chronos_diaActualmenteSimulado * (360.0 / cuerpoCeleste->periodoRotacion);

        cuerpoCeleste->posicion->anguloRotacion = fmod(cuerpoCeleste->posicion->anguloRotacion, 360.0);

    }

    // --

    cuerpoCeleste->posicion->posX = cos360(cuerpoCeleste->posicion->anguloTraslacion) * cuerpoCeleste->posicion->distanciaAlPadre;
    cuerpoCeleste->posicion->posY = 0.0;
    cuerpoCeleste->posicion->posZ = -sin360(cuerpoCeleste->posicion->anguloTraslacion) * cuerpoCeleste->posicion->distanciaAlPadre;

    // --

    if (cuerpoCeleste->numHijos > 0) {

        for (int pos = 0; pos < cuerpoCeleste->numHijos; pos++) {
            actualizaCuerpoCeleste(&cuerpoCeleste->hijos[pos]);
        }
    }

    // --


}

//int ft = 0;


void representaCuerpoCeleste(CuerpoCeleste* cuerpoCeleste, enum TipoCuerpoCeleste tipoCuerpoCeleste, struct ConfiguracionCamara* configuracionCamara) {

    //    iluminaCuerpoCeleste(cuerpoCeleste);
    switch (cuerpoCeleste->quienSoy){
        case BOVEDA_CELESTIAL:
            loDelResto(90);
            break;

        case SOL:
            loDelSol();
            break;

        default:
            break;
    }

    glPushMatrix(); // 2

    {
        if (configuracionCamara->mostrarOrbitas && cuerpoCeleste->posicion->distanciaAlPadre > 0.0f) {
            if (false && cs.mostrarEasterEggs && tipoCuerpoCeleste == tccPlaneta) {
                myElipse(0.0f, 0.0f, cuerpoCeleste->posicion->distanciaAlPadre, cuerpoCeleste->posicion->distanciaAlPadre / 2.0, 360, tipoCuerpoCeleste);
            }
            else {
                myElipse(0.0f, 0.0f, cuerpoCeleste->posicion->distanciaAlPadre, cuerpoCeleste->posicion->distanciaAlPadre, 360, tipoCuerpoCeleste);
            }

        }

        if (fpclassify(cuerpoCeleste->periodoTraslacion) != FP_ZERO)
        {
            if (cs.mostrarEasterEggs && cuerpoCeleste->quienSoy == ISS)
            {
                glRotated(cuerpoCeleste->posicion->anguloTraslacion, 0.5, 1.0, -0.2);
            }
            else {
                glRotated(cuerpoCeleste->posicion->anguloTraslacion, 0.0, 1.0, 0.0);
            }


        }

        if (cuerpoCeleste->posicion->distanciaAlPadre > 0.0) {
            if (false && cs.mostrarEasterEggs && tipoCuerpoCeleste == tccPlaneta) {
                glTranslated(cuerpoCeleste->posicion->distanciaAlPadre / (1.5 - 0.5 * cos360(cuerpoCeleste->posicion->anguloTraslacion)), 0.0, 0.0);
            }
            else {
                glTranslated(cuerpoCeleste->posicion->distanciaAlPadre, 0.0, 0.0);
            }
        }

        glPushMatrix(); // 1

        if (fpclassify(cuerpoCeleste->periodoRotacion) != FP_ZERO) {
            glRotated(cuerpoCeleste->posicion->anguloRotacion, 0.0, 5.0, 0.0);
        }



        if (cuerpoCeleste->numTexturaObjeto != INT_MIN) {
            //glPushMatrix();
            glEnable(GL_TEXTURE_2D);
            glBindTexture(GL_TEXTURE_2D, cuerpoCeleste->numTexturaObjeto);
        }
        else {
            glColor3f(cuerpoCeleste->color[0], cuerpoCeleste->color[1], cuerpoCeleste->color[2]);

        }

        glScalef(cuerpoCeleste->posicion->radio, cuerpoCeleste->posicion->radio, cuerpoCeleste->posicion->radio);

        glCallList(cuerpoCeleste->numListaObjeto);


        if (cuerpoCeleste->numTexturaObjeto != INT_MIN) {
            glDisable(GL_TEXTURE_2D);
        }


        glPopMatrix(); // 1


        //myEjes();
        // glutSolidSphere(cuerpoCeleste->posicion->radio, 20, 20);
        // glutWireSphere(cuerpoCeleste->posicion->radio, 20, 20);

        switch (cuerpoCeleste->quienSoy) {
            case BOVEDA_CELESTIAL:
            case SOL:
                loDelResto(cs.potenciaIluminacion);
                break;

            default:
                break;
        }

        if (cuerpoCeleste->numHijos > 0) {

            for (int pos = 0; pos < cuerpoCeleste->numHijos; pos++) {

                representaCuerpoCeleste(&cuerpoCeleste->hijos[pos], tipoCuerpoCeleste + 1, configuracionCamara);

            }

        }

    }

    glPopMatrix(); // 2

}
