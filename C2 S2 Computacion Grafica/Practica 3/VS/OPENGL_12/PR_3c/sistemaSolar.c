#include "sistemaSolar.h"

extern float fAngulo;

int myEsfera();


void actualizaDatosUnPlaneta(planeta *unPlaneta)
{
    unPlaneta->anguloTaslacionActual += 365.0f/ unPlaneta->periodoTranslacion;

    if (unPlaneta->anguloTaslacionActual > 360.0f)
    {
        unPlaneta->anguloTaslacionActual -= 360.0f;
    }
}

void representaUnPlaneta(planeta *unPlaneta)
{
    /*
    glPushMatrix();

    glColor3f(1.0, 0.0, 0);

    glRotatef(fAngulo, 0.0f, 5.0f, 0.0);

    //La hago mas pequeña
    glScalef(0.05, 0.05, 0.05);

    glTranslatef(10.0f, 0.0f, 0.0f);

    myEsfera();

    glPopMatrix();

    */

    // --

    glPushMatrix();

    glColor3f(unPlaneta->color[0], unPlaneta->color[1], unPlaneta->color[2]);

    glRotatef(unPlaneta->anguloTaslacionActual, 0.0f, 5.0f, 0.0);
 //   glRotatef(fAngulo, 0.0f, 5.0f, 0.0);

    //La hago mas pequeña
    glScalef(0.05, 0.05, 0.05);

    glTranslatef(unPlaneta->distanciaMaximaAlSol, 0.0f, 0.0f);

    // glutWireCube(10);
    myEsfera();

    glPopMatrix();
    
}
