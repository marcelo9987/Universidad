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

        cuerpoCeleste->posicion->anguloTraslacion = cs.chronos_diaActualmenteSimulado * (360.0 / cuerpoCeleste->periodoTraslacion);

        cuerpoCeleste->posicion->anguloTraslacion = fmod(cuerpoCeleste->posicion->anguloTraslacion, 360);

    }

    // --

    if (cuerpoCeleste->periodoRotacion > 0.0f && cs.chronos_segundosRealesPorDiaSimulado_posicionSeleccionada != 0)
    {

        cuerpoCeleste->posicion->anguloRotacion = cs.chronos_diaActualmenteSimulado * (360.0 / cuerpoCeleste->periodoRotacion);

        cuerpoCeleste->posicion->anguloRotacion = fmod(cuerpoCeleste->posicion->anguloRotacion, 360);

    }

    cuerpoCeleste->posicion->posX = cosf360(cuerpoCeleste->posicion->anguloTraslacion) * cuerpoCeleste->posicion->distanciaAlPadre;
    cuerpoCeleste->posicion->posY = 0.0f;
    cuerpoCeleste->posicion->posZ = -sinf360(cuerpoCeleste->posicion->anguloTraslacion) * cuerpoCeleste->posicion->distanciaAlPadre;


    if (cuerpoCeleste->numHijos > 0)
    {

        for (int pos = 0; pos < cuerpoCeleste->numHijos; pos++)
        {
            actualizaDatosCuerpoCeleste(&cuerpoCeleste->hijos[pos]);
        }
    }

}

int ft = true;

void representaCuerpoCeleste(CuerpoCeleste* cuerpoCeleste)
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
    if(/*cuerpoCeleste->quienSoy!=ISS && */cuerpoCeleste->quienSoy!=TIERRA && cuerpoCeleste->quienSoy!=LUNA )
    {
        glPushMatrix();
    }

    {
        if (cs.camaraPrincipal.mostrarOrbitas && cuerpoCeleste->posicion->distanciaAlPadre > 0.0f)
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

        
        
        

        glPushMatrix();


        if (cuerpoCeleste->posicion->numTexturaObjeto != INT_MIN)
        {
            //glPushMatrix();
            glEnable(GL_TEXTURE_2D);
            glBindTexture(GL_TEXTURE_2D, cuerpoCeleste->posicion->numTexturaObjeto);
        }
        else
        {
            //Color3f(cuerpoCeleste->color[0], cuerpoCeleste->color[1], cuerpoCeleste->color[2]);

        }

        //glPushMatrix();
       
            glScalef(cuerpoCeleste->posicion->radio, cuerpoCeleste->posicion->radio, cuerpoCeleste->posicion->radio);
          
            glCallList(cuerpoCeleste->posicion->numListaObjeto);
       


            if (cuerpoCeleste->posicion->numTexturaObjeto != INT_MIN)
            {
                glDisable(GL_TEXTURE_2D);
            }
           
           
        glPopMatrix();

        

        // myEjes();
        // glutSolidSphere(cuerpoCeleste->posicion->radio, 20, 20);
        // glutWireSphere(cuerpoCeleste->posicion->radio, 20, 20);

        if (cuerpoCeleste->numHijos > 0)
        {

            for (int pos = 0; pos < cuerpoCeleste->numHijos; pos++)
            {

                representaCuerpoCeleste(&cuerpoCeleste->hijos[pos]);
            }
           
        }

    }

    if (cuerpoCeleste->quienSoy != TIERRA && cuerpoCeleste->quienSoy != LUNA)
    {
        glPopMatrix();
    }


    if (ft < 9)
    {
        printf("%20s - tamaño: %2.5f - distancia al centro: %2.5f\n", cuerpoCeleste->nombre, cuerpoCeleste->posicion->radio, cuerpoCeleste->posicion->distanciaAlPadre);
    }

    ft++;
   
}
