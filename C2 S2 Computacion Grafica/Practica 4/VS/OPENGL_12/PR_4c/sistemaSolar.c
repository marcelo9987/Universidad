#include "controles.h"

#include "sistemaSolar.h"
#include "figurasGeometricas.h"

// --

extern float fAngulo;

// --


void actualizaDatosCuerpoCeleste(CuerpoCeleste* cuerpoCeleste)
{
    float chronos_segundosRealesPorDiaSimulado = K_VELOCIDAD_SPD_ARRAY[cs.chronos_segundosRealesPorDiaSimulado_posicionSeleccionada];

    if (cuerpoCeleste->periodoTraslacion > 0.0f && cs.chronos_segundosRealesPorDiaSimulado_posicionSeleccionada != 0)
    {

        /*
        float deltaTraslacion = 360.0f / (cuerpoCeleste->periodoTraslacion * chronos_segundosRealesPorDiaSimulado * cs.chronos_framesPorSegundo);

        cuerpoCeleste->posicion->anguloTraslacion += deltaTraslacion;

        if (cuerpoCeleste->posicion->anguloTraslacion > 360.0f)
        {
            cuerpoCeleste->posicion->anguloTraslacion -= 360.0f;
        }
        */

        cuerpoCeleste->posicion->anguloTraslacion = cs.chronos_diaActualmenteSimulado * (360.0 / cuerpoCeleste->periodoTraslacion);

        cuerpoCeleste->posicion->anguloTraslacion = fmod(cuerpoCeleste->posicion->anguloTraslacion, 360);

    }

    // --

    if (cuerpoCeleste->periodoRotacion > 0.0f && cs.chronos_segundosRealesPorDiaSimulado_posicionSeleccionada != 0)
    {
        /*
        float deltaRotacion = 360.0f / (cuerpoCeleste->periodoRotacion * chronos_segundosRealesPorDiaSimulado * cs.chronos_framesPorSegundo);

        cuerpoCeleste->posicion->anguloRotacion += deltaRotacion;

        if (cuerpoCeleste->posicion->anguloRotacion > 360.0f)
        {
            cuerpoCeleste->posicion->anguloRotacion -= 360.0f;
        }
        */

        cuerpoCeleste->posicion->anguloRotacion = cs.chronos_diaActualmenteSimulado * (360.0 / cuerpoCeleste->periodoRotacion);

        cuerpoCeleste->posicion->anguloRotacion = fmod(cuerpoCeleste->posicion->anguloRotacion, 360);

    }

    if (cuerpoCeleste->numHijos > 0)
    {

        for (int pos = 0; pos < cuerpoCeleste->numHijos; pos++)
        {
            actualizaDatosCuerpoCeleste(&cuerpoCeleste->hijos[pos]);
        }
    }

}

void representaCuerpoCeleste(CuerpoCeleste* cuerpoCeleste, bool imprimirDatos)
{


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

    glPushMatrix();

    {
        //uno el nombre con "texturas/"
         /*char* nombre = "texturas/Luna.bmp";

             textura = cargaTextura(nombre);
             if(textura != 0)
             {
                 glEnable(GL_TEXTURE_2D);
                 glBindTexture(GL_TEXTURE_2D, textura);
             }*/





        if (cs.mostrarOrbitas && cuerpoCeleste->posicion->distanciaAlPadre > 0.0f)
        {
            //  myEllipse(0.0f, 0.0f, cuerpoCeleste->posicion->distanciaAlPadre, cuerpoCeleste->posicion->distanciaAlPadre / 2.0, 100);
            myEllipse(0.0f, 0.0f, cuerpoCeleste->posicion->distanciaAlPadre, cuerpoCeleste->posicion->distanciaAlPadre, 360);

        }

        if (cuerpoCeleste->periodoTraslacion > 0.0f)
        {
            glRotatef(cuerpoCeleste->posicion->anguloTraslacion, 0.0f, 1.0f, 0.0);
        }

        if (cuerpoCeleste->posicion->distanciaAlPadre > 0.0f)
        {
            glTranslatef(cuerpoCeleste->posicion->distanciaAlPadre, 0.0f, 0.0f);
        }

        if (cuerpoCeleste->periodoRotacion > 0.0f)
        {
            glRotatef(cuerpoCeleste->posicion->anguloRotacion, 0.0f, 5.0f, 0.0);
        }
        /*
        if (strcmp(cuerpoCeleste->nombre, "Sol") == 0)
        {
        */
        /*
        char* nombre = "texturas/Sol.bmp";

        textura = cargaTextura(nombre);
        if (textura != 0)
        {
            glEnable(GL_TEXTURE_2D);
            glBindTexture(GL_TEXTURE_2D, textura);
        }
        glEnable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D, textura);
        */

        glPushMatrix();

        glScalef(cuerpoCeleste->posicion->radio, cuerpoCeleste->posicion->radio, cuerpoCeleste->posicion->radio);
        /*
        glCallList(myEsfera());

        glPopMatrix();


        glDisable(GL_TEXTURE_2D);
        */

        if (cuerpoCeleste->posicion->numTexturaObjeto != INT_MIN)
        {

            glEnable(GL_TEXTURE_2D);
            glBindTexture(GL_TEXTURE_2D, cuerpoCeleste->posicion->numTexturaObjeto);
        }
        else
        {
            glColor3f(cuerpoCeleste->color[0], cuerpoCeleste->color[1], cuerpoCeleste->color[2]);
        }

        glCallList(cuerpoCeleste->posicion->numListaObjeto);

        if (cuerpoCeleste->posicion->numTexturaObjeto != INT_MIN)
        {
            glDisable(GL_TEXTURE_2D);
        }

        glPopMatrix();

        /*
            }
                else
                {

                    char* nombre = "texturas/Luna.jpg";

                    textura = cargaTextura(nombre);
                    if (textura != 0)
                    {
                        glEnable(GL_TEXTURE_2D);
                        glBindTexture(GL_TEXTURE_2D, textura);
                    }



                    glEnable(GL_TEXTURE_2D);
                    glBindTexture(GL_TEXTURE_2D, textura);

                    glPushMatrix();
                    glScalef(cuerpoCeleste->posicion->radio, cuerpoCeleste->posicion->radio, cuerpoCeleste->posicion->radio);
                    //glScalef(sqrt(cs.factorEscaladoCuerposCelestes), sqrt(cs.factorEscaladoCuerposCelestes), sqrt(cs.factorEscaladoCuerposCelestes) );
                    glCallList(cuerpoCeleste->posicion->numListaObjeto);
                    glPopMatrix();
                    glDisable(GL_TEXTURE_2D);

                    // glutSolidCube(cuerpoCeleste->posicion->radio);
                    //glutSolidSphere(cuerpoCeleste->posicion->radio*2*0.5f, 20, 20);


                }
            */
        /*
        if (cuerpoCeleste->tieneAnillos)
        {
            for (float distancia = cuerpoCeleste->posicion->radio * 1.2f; distancia <= cuerpoCeleste->posicion->radio * 2.0f; distancia += 0.2f)
            {
                myEllipse(0.0f, 0.0f, distancia, distancia, 360);
            }
        }
        */

        //glutSolidSphere(cuerpoCeleste->posicion->radio, 20, 20);
       //myEsfera();








       // myEjes();

        //myEsfera();
        //glutSolidSphere(cuerpoCeleste->posicion->radio, 20, 20);
        // glutWireSphere(cuerpoCeleste->posicion->radio, 20, 20);

        if (cuerpoCeleste->numHijos > 0)
        {

            for (int pos = 0; pos < cuerpoCeleste->numHijos; pos++)
            {
                representaCuerpoCeleste(&cuerpoCeleste->hijos[pos], imprimirDatos);
            }
        }

    }

    glPopMatrix();


    if (imprimirDatos)
    {
        printf("%20s - tamaño: %2.5f - distancia al centro: %2.5f\n", cuerpoCeleste->nombre, cuerpoCeleste->posicion->radio, cuerpoCeleste->posicion->distanciaAlPadre);
    }

}
