#include "controles.h"

#include "sistemaSolar.h"
#include "figurasGeometricas.h"


// --


GLfloat sun_mat_ambient[]   /**/ = {0.5f, 0.5f, 0.5f, 0.5f}; // RGBA - reflectancia RGBA ambiental del material
GLfloat sun_mat_diffuse[]   /**/ = {1.0f, 1.0f, 1.0f, 1.0f}; // RGBA - reflectancia RGBA difusa del material
GLfloat sun_mat_specular[]  /**/ = {0.5f, 0.5f, 0.5f, 0.5f}; // RGBA - reflectancia RGBA especular del material
//GLfloat sun_mat_emission[]  /**/ = { 0.8f, 0.8f, 0.8f, 1.0f }; // RGBA - intensidad de luz emitida por material
GLfloat sun_mat_shininess   /**/ = 0.0f; // Exponente especular RGBA del material. Los valores enteros se asignan directamente. Solo se aceptan valores del intervalo [0, 128].


GLfloat rest_mat_ambient[]  /**/ = {0.5f, 0.5f, 0.5f, 1.0f}; // RGBA - reflectancia RGBA ambiental del material
GLfloat rest_mat_diffuse[]  /**/ = {1.0f, 1.0f, 1.0f, 1.0f}; // RGBA - reflectancia RGBA difusa del material
GLfloat rest_mat_specular[] /**/ = {0.0f, 0.0f, 1.0f, 1.0f}; // RGBA - reflectancia RGBA especular del material
//GLfloat rest_mat_emission[] /**/ = { 0.0f, 0.0f, 0.0f, 1.0f }; // RGBA - intensidad de luz emitida por el material
GLfloat rest_mat_shininess  /**/ = 0.0f; // Exponente especular RGBA del material. Los valores enteros se asignan directamente. Solo se aceptan valores del intervalo [0, 128].

// --

GLfloat posSol[] = {0, 0, 0, 1.0};

GLfloat direccionFocoSol0[] = {+0.5f, 0.0f, +0.0f, 1.0f};
GLfloat direccionFocoSol1[] = {-0.5f, 0.0f, +0.0f, 1.0f};
GLfloat direccionFocoSol2[] = {+0.0f, 0.0f, +0.5f, 1.0f};
GLfloat direccionFocoSol3[] = {+0.0f, 0.0f, -0.5f, 1.0f};


GLfloat lightAmb[] = {0.25f, 0.25f, 0.25f, 0.5f};
GLfloat lightDif[] = {1.0f, 1.0f, 1.0f, 1.0f};
GLfloat lightSpc[] = {1.0f, 1.0f, 1.0f, 1.0f};

// --


void apagaLuces() {
    //    if (cuerpoCeleste->quienSoy == SOL)
    // glClear(GL_LIGHTING_BIT);
    // glPushAttrib(GL_LIGHTING_BIT);
    // shade_model(GL_FLAT;)

    glDisable(GL_LIGHTING);
    glDisable(GL_LIGHT0);
    glDisable(GL_LIGHT1);
    glDisable(GL_LIGHT2);
    glDisable(GL_LIGHT3);

}

void enciendeLuces() {


    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_LIGHT1);
    glEnable(GL_LIGHT2);
    glEnable(GL_LIGHT3);


    glMatrixMode(GL_MODELVIEW);
    //glLoadIdentity();



    glLightfv(GL_LIGHT0, GL_POSITION, posSol); // Set light position
    glLightfv(GL_LIGHT1, GL_POSITION, posSol); // Set light position
    glLightfv(GL_LIGHT2, GL_POSITION, posSol); // Set light position
    glLightfv(GL_LIGHT3, GL_POSITION, posSol); // Set light position

    glLightfv(GL_LIGHT0, GL_SPOT_DIRECTION, direccionFocoSol0);
    glLightfv(GL_LIGHT1, GL_SPOT_DIRECTION, direccionFocoSol1);
    glLightfv(GL_LIGHT2, GL_SPOT_DIRECTION, direccionFocoSol2);
    glLightfv(GL_LIGHT3, GL_SPOT_DIRECTION, direccionFocoSol3);

    // glLighti(GL_LIGHT0, GL_SPOT_CUTOFF, 180);
    glLightfv(GL_LIGHT0, GL_AMBIENT, lightAmb);
    glLightfv(GL_LIGHT1, GL_AMBIENT, lightAmb);
    glLightfv(GL_LIGHT2, GL_AMBIENT, lightAmb);
    glLightfv(GL_LIGHT3, GL_AMBIENT, lightAmb);

    glLightfv(GL_LIGHT0, GL_DIFFUSE, lightDif);
    glLightfv(GL_LIGHT1, GL_DIFFUSE, lightDif);
    glLightfv(GL_LIGHT2, GL_DIFFUSE, lightDif);
    glLightfv(GL_LIGHT3, GL_DIFFUSE, lightDif);

    glLightfv(GL_LIGHT0, GL_SPECULAR, lightSpc);
    glLightfv(GL_LIGHT1, GL_SPECULAR, lightSpc);
    glLightfv(GL_LIGHT2, GL_SPECULAR, lightSpc);
    glLightfv(GL_LIGHT3, GL_SPECULAR, lightSpc);

    glLighti(GL_LIGHT0, GL_SPOT_CUTOFF, 90);
    glLighti(GL_LIGHT1, GL_SPOT_CUTOFF, 90);
    glLighti(GL_LIGHT2, GL_SPOT_CUTOFF, 90);
    glLighti(GL_LIGHT3, GL_SPOT_CUTOFF, 90);



    /*glEnable(GL_LIGHT0);
    glEnable(GL_LIGHTING);*/


}


void actualizaDatosCuerpoCeleste(CuerpoCeleste *cuerpoCeleste) {
    float chronos_segundosRealesPorDiaSimulado = K_VELOCIDAD_SPD_ARRAY[cs.chronos_segundosRealesPorDiaSimulado_posicionSeleccionada];

    if (cuerpoCeleste->periodoTraslacion > 0.0f && cs.chronos_segundosRealesPorDiaSimulado_posicionSeleccionada != 0) {

        cuerpoCeleste->posicion->anguloTraslacion = cs.chronos_diaActualmenteSimulado * (360.0 / cuerpoCeleste->periodoTraslacion);

        cuerpoCeleste->posicion->anguloTraslacion = fmod(cuerpoCeleste->posicion->anguloTraslacion, 360);

    }

    // --

    if (cuerpoCeleste->periodoRotacion > 0.0f && cs.chronos_segundosRealesPorDiaSimulado_posicionSeleccionada != 0) {

        cuerpoCeleste->posicion->anguloRotacion = cs.chronos_diaActualmenteSimulado * (360.0 / cuerpoCeleste->periodoRotacion);

        cuerpoCeleste->posicion->anguloRotacion = fmod(cuerpoCeleste->posicion->anguloRotacion, 360);

    }

    cuerpoCeleste->posicion->posX = cosf360(cuerpoCeleste->posicion->anguloTraslacion) * cuerpoCeleste->posicion->distanciaAlPadre;
    cuerpoCeleste->posicion->posY = 0.0f;
    cuerpoCeleste->posicion->posZ = -sinf360(cuerpoCeleste->posicion->anguloTraslacion) * cuerpoCeleste->posicion->distanciaAlPadre;


    if (cuerpoCeleste->numHijos > 0) {

        for (int pos = 0; pos < cuerpoCeleste->numHijos; pos++) {
            actualizaDatosCuerpoCeleste(&cuerpoCeleste->hijos[pos]);
        }
    }


}

int ft = 0;


void representaCuerpoCeleste(CuerpoCeleste *cuerpoCeleste) {


    if (cuerpoCeleste->quienSoy == SOL) {
        // iluminaCuerpoCelesteEmisor();
        // iluminaCuerpoCelesteNoEmisor();

        // https://learn.microsoft.com/es-es/windows/win32/opengl/glmaterialfv
        glMaterialfv(GL_FRONT, GL_AMBIENT, sun_mat_ambient);        // Add lighting (ambient)
        //   glMaterialfv(GL_FRONT, GL_DIFFUSE, sun_mat_diffuse);        // Add lighting (diffuse)
        glMaterialfv(GL_FRONT, GL_SPECULAR, sun_mat_specular);      // Add lighting (specular)
        //glMaterialfv(GL_FRONT, GL_EMISSION, sun_mat_emission);
        glMaterialf(GL_FRONT, GL_SHININESS, sun_mat_shininess);

    } else {
        // iluminaCuerpoCelesteNoEmisor();

        glMaterialfv(GL_FRONT, GL_AMBIENT, rest_mat_ambient);
        //   glMaterialfv(GL_FRONT, GL_DIFFUSE, rest_mat_diffuse);
        glMaterialfv(GL_FRONT, GL_SPECULAR, rest_mat_specular);
        //glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, rest_mat_emission);
        glMaterialf(GL_FRONT, GL_SHININESS, rest_mat_shininess);
    }


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

    // --

    // --

    glPushMatrix();


    if (/*cuerpoCeleste->quienSoy!=ISS && */cuerpoCeleste->quienSoy != TIERRA && cuerpoCeleste->quienSoy != LUNA) {
        glPushMatrix();
    }


    {
        if (cs.camaraPrincipal.mostrarOrbitas && cuerpoCeleste->posicion->distanciaAlPadre > 0.0f) {
            //  myEllipse(0.0f, 0.0f, cuerpoCeleste->posicion->distanciaAlPadre, cuerpoCeleste->posicion->distanciaAlPadre / 2.0, 100);
            myEllipse(0.0f, 0.0f, cuerpoCeleste->posicion->distanciaAlPadre, cuerpoCeleste->posicion->distanciaAlPadre, 360);

        }

        if (cuerpoCeleste->periodoTraslacion > 0.0f) {
            glRotatef(cuerpoCeleste->posicion->anguloTraslacion, 0.0f, 1.0f, 0.0);
        }

        if (cuerpoCeleste->posicion->distanciaAlPadre > 0.0f) {
            glTranslatef(cuerpoCeleste->posicion->distanciaAlPadre, 0.0f, 0.0f);
        }

        if (cuerpoCeleste->periodoRotacion > 0.0f) {
            glRotatef(cuerpoCeleste->posicion->anguloRotacion, 0.0f, 5.0f, 0.0);
        }

        glPushMatrix();


        if (cuerpoCeleste->posicion->numTexturaObjeto != INT_MIN) {
            //glPushMatrix();
            glEnable(GL_TEXTURE_2D);
            glBindTexture(GL_TEXTURE_2D, cuerpoCeleste->posicion->numTexturaObjeto);
        } else {
            //Color3f(cuerpoCeleste->color[0], cuerpoCeleste->color[1], cuerpoCeleste->color[2]);

        }

        //glPushMatrix();

        glScalef(cuerpoCeleste->posicion->radio, cuerpoCeleste->posicion->radio, cuerpoCeleste->posicion->radio);

        glCallList(cuerpoCeleste->posicion->numListaObjeto);


        if (cuerpoCeleste->posicion->numTexturaObjeto != INT_MIN) {
            glDisable(GL_TEXTURE_2D);
        }


        glPopMatrix();



        //myEjes();
        // glutSolidSphere(cuerpoCeleste->posicion->radio, 20, 20);
        // glutWireSphere(cuerpoCeleste->posicion->radio, 20, 20);

        if (cuerpoCeleste->numHijos > 0) {

            for (int pos = 0; pos < cuerpoCeleste->numHijos; pos++) {

                representaCuerpoCeleste(&cuerpoCeleste->hijos[pos]);

            }

        }

    }


    if (cuerpoCeleste->quienSoy != TIERRA && cuerpoCeleste->quienSoy != LUNA) {
        glPopMatrix();
    }


    //iluminaCuerpoCeleste(cuerpoCeleste);

    //if(cuerpoCeleste->quienSoy==ISS)
    //{

    //}



    if (ft < 9) {
        printf("%20s - tama�o: %2.5f - distancia al centro: %2.5f\n", cuerpoCeleste->nombre, cuerpoCeleste->posicion->radio, cuerpoCeleste->posicion->distanciaAlPadre);
    }

    ft++;


}
