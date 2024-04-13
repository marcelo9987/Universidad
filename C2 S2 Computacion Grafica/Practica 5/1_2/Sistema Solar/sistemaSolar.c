#include "controles.h"

#include "sistemaSolar.h"
#include "figurasGeometricas.h"


// --

void loDelSol() {


    //glClear(GL_LIGHTING_BIT);

    //shade_model(GL_FLAT;)
    glDisable(GL_LIGHTING);
    glDisable(GL_LIGHT0);
    glDisable(GL_LIGHT1);
    //glDisable(GL_LIGHT2);
    //glDisable(GL_LIGHT3);


    GLfloat sun_mat_ambient[] = { 0.5f, 0.5f, 0.5f, 0.5f };
    GLfloat sun_mat_diffuse[] = { 1.0f, 1.0f, 1.0f, 1.0f };
    GLfloat sun_mat_specular[] = { 0.5f, 0.5f, 0.5f, 0.5f };
    //GLfloat sun_mat_emission[] = { 0.8f, 0.8f, 0.8f, 1.0f };
    //GLfloat sun_mat_shininess = 0.0f;

    glMaterialfv(GL_FRONT, GL_AMBIENT, sun_mat_ambient);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, sun_mat_diffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR, sun_mat_specular);
    //glMaterialfv(GL_FRONT, GL_EMISSION, sun_mat_emission);
    //glMaterialf(GL_FRONT, GL_SHININESS, sun_mat_shininess);
}

void loDelResto() {

    glClearColor(0.0, 0.0, 0.0, 0.0);

    //glEnable(GL_DEPTH_TEST);
    //glEnable(GL_SMOOTH);
    //glShadeModel(GL_SMOOTH);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_LIGHT1);
    //glEnable(GL_LIGHT2);
    //glEnable(GL_LIGHT3);

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

    glLighti(GL_LIGHT0, GL_SPOT_CUTOFF, 90);
    glLighti(GL_LIGHT1, GL_SPOT_CUTOFF, 90);
    //glLighti(GL_LIGHT2, GL_SPOT_CUTOFF, 90);
    //glLighti(GL_LIGHT3, GL_SPOT_CUTOFF, 0);


    /*glEnable(GL_LIGHT0);
    glEnable(GL_LIGHTING);*/

    GLfloat mat_ambient[] = { 0.5f, 0.5f, 0.5f, 1.0f };
    GLfloat mat_diffuse[] = { 0.9f, 0.9f, 0.9f, 1.0f };
    //GLfloat mat_specular[] = { 0.0f, 0.0f, 1.0f, 1.0f };
    //GLfloat mat_emission[] = { 0.0f, 0.0f, 0.0f, 1.0f };
    GLfloat mat_shininess = 0.0f;

    glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
    //glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
    //glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, mat_emission);
    glMaterialf(GL_FRONT, GL_SHININESS, mat_shininess);

}


void actualizaCuerpoCeleste(CuerpoCeleste* cuerpoCeleste) {
    float chronos_segundosRealesPorDiaSimulado = K_VELOCIDAD_SPD_ARRAY[cs.chronos_segundosRealesPorDiaSimulado_posicionSeleccionada];

    if (fpclassify(cuerpoCeleste->periodoTraslacion) != FP_ZERO && cs.chronos_segundosRealesPorDiaSimulado_posicionSeleccionada != 0) {

        cuerpoCeleste->posicion->anguloTraslacion = cs.chronos_diaActualmenteSimulado * (360.0 / cuerpoCeleste->periodoTraslacion);

        cuerpoCeleste->posicion->anguloTraslacion = fmod(cuerpoCeleste->posicion->anguloTraslacion, 360);

    }

    // --

    if (fpclassify(cuerpoCeleste->periodoRotacion) != FP_ZERO && cs.chronos_segundosRealesPorDiaSimulado_posicionSeleccionada != 0) {

        cuerpoCeleste->posicion->anguloRotacion = cs.chronos_diaActualmenteSimulado * (360.0 / cuerpoCeleste->periodoRotacion);

        cuerpoCeleste->posicion->anguloRotacion = fmod(cuerpoCeleste->posicion->anguloRotacion, 360);

    }

    // --

    cuerpoCeleste->posicion->posX = cosf360(cuerpoCeleste->posicion->anguloTraslacion) * cuerpoCeleste->posicion->distanciaAlPadre;
    cuerpoCeleste->posicion->posY = 0.0f;
    cuerpoCeleste->posicion->posZ = -sinf360(cuerpoCeleste->posicion->anguloTraslacion) * cuerpoCeleste->posicion->distanciaAlPadre;

    // --

    if (cuerpoCeleste->numHijos > 0) {

        for (int pos = 0; pos < cuerpoCeleste->numHijos; pos++) {
            actualizaCuerpoCeleste(&cuerpoCeleste->hijos[pos]);
        }
    }

    // --


}

//int ft = 0;


void representaCuerpoCeleste(CuerpoCeleste* cuerpoCeleste, enum TipoCuerpoCeleste tipoCuerpoCeleste) {

    // --

//    glColor3f(cuerpoCeleste->color[0], cuerpoCeleste->color[1], cuerpoCeleste->color[2]);

    /*

    glPushMatrix();

    {
        glRotatef(90.0f, 1.0f, 0.0f, 0.0);

        glutWireTorus(cuerpoCeleste->posicion->radio/24.0f, cuerpoCeleste->posicion->distanciaAlPadre,  3, 360);

    }

    glPopMatrix();

    */



    //    iluminaCuerpoCeleste(cuerpoCeleste);
    if (cuerpoCeleste->quienSoy == SOL) {
        //loDelResto();
        loDelSol();
    }
    else {
        //loDelResto();
    }


    glPushMatrix(); // 3

    //if (false) {
    //    if (/*cuerpoCeleste->quienSoy!=ISS && */cuerpoCeleste->quienSoy != TIERRA && cuerpoCeleste->quienSoy != LUNA) {
    //        glPushMatrix(); // 2
    //    }
    //}

    {
        if (cs.camaraPrincipal.mostrarOrbitas && cuerpoCeleste->posicion->distanciaAlPadre > 0.0f) {
            //myElipse(0.0f, 0.0f, cuerpoCeleste->posicion->distanciaAlPadre, cuerpoCeleste->posicion->distanciaAlPadre / 2.0, 10);
            myElipse(0.0f, 0.0f, cuerpoCeleste->posicion->distanciaAlPadre, cuerpoCeleste->posicion->distanciaAlPadre, 360, tipoCuerpoCeleste/*cuerpoCeleste->quienSoy < LUNA ? O_ORBITASOLAR : O_ORBITAPLANETARIA*/);

        }

        if (fpclassify(cuerpoCeleste->periodoTraslacion) != FP_ZERO)
        {
            if (cuerpoCeleste->quienSoy == ISS) {
                glRotatef(cuerpoCeleste->posicion->anguloTraslacion, 0.5f, 1.0f, -0.2f);
            }
            else {
                glRotatef(cuerpoCeleste->posicion->anguloTraslacion, 0.0f, 1.0f, 0.0);
            }


        }

        if (cuerpoCeleste->posicion->distanciaAlPadre > 0.0f) {
            glTranslatef(cuerpoCeleste->posicion->distanciaAlPadre, 0.0f, 0.0f);
        }

        glPushMatrix(); // 1

        if (fpclassify(cuerpoCeleste->periodoRotacion) != FP_ZERO) {
            glRotatef(cuerpoCeleste->posicion->anguloRotacion, 0.0f, 5.0f, 0.0);
        }



        if (cuerpoCeleste->posicion->numTexturaObjeto != INT_MIN) {
            //glPushMatrix();
            glEnable(GL_TEXTURE_2D);
            glBindTexture(GL_TEXTURE_2D, cuerpoCeleste->posicion->numTexturaObjeto);
        }
        else {
            //Color3f(cuerpoCeleste->color[0], cuerpoCeleste->color[1], cuerpoCeleste->color[2]);

        }

        //glPushMatrix();

        glScalef(cuerpoCeleste->posicion->radio, cuerpoCeleste->posicion->radio, cuerpoCeleste->posicion->radio);

        glCallList(cuerpoCeleste->posicion->numListaObjeto);


        if (cuerpoCeleste->posicion->numTexturaObjeto != INT_MIN) {
            glDisable(GL_TEXTURE_2D);
        }


        glPopMatrix(); // 1



        //myEjes();
        // glutSolidSphere(cuerpoCeleste->posicion->radio, 20, 20);
        // glutWireSphere(cuerpoCeleste->posicion->radio, 20, 20);

        if (cuerpoCeleste->quienSoy == SOL) {
            //loDelSol();
            loDelResto();
        }
        else {
            //loDelResto();
        }

        if (cuerpoCeleste->numHijos > 0) {

            for (int pos = 0; pos < cuerpoCeleste->numHijos; pos++) {

                representaCuerpoCeleste(&cuerpoCeleste->hijos[pos], tipoCuerpoCeleste + 1);

            }

        }

    }

    //if (false) {
    //    if (cuerpoCeleste->quienSoy != TIERRA && cuerpoCeleste->quienSoy != LUNA) {
    //        glPopMatrix(); // 2
    //    }
    //}

    glPopMatrix(); // 3


    //    iluminaCuerpoCeleste(cuerpoCeleste);
        /*
        if (cuerpoCeleste->quienSoy == SOL) {
            loDelSol();
        } else {
            loDelResto();
        }
        */

        //if(cuerpoCeleste->quienSoy==ISS)
        //{

        //}


    /*
        if (ft < 9) {
            printf("%20s - tamaño: %2.5f - distancia al centro: %2.5f\n", cuerpoCeleste->nombre, cuerpoCeleste->posicion->radio, cuerpoCeleste->posicion->distanciaAlPadre);
        }

        ft++;
    */

}
