#include "comun.h"
#include "figurasGeometricas.h"
#include "sistemaSolar.h"

void myEjes()
{
    //glPushAttrib(GL_COLOR_BUFFER_BIT);

    // Eje X
    glColor3f(1.0f, 0.0f, 0.0f);    // Red
    //  glColor3f(0.0f, 0.0f, 1.0f);    // Blue
    glBegin(GL_LINES);
    {
        glVertex3f(0.0f, 0.0f, 0.0f);
        glVertex3f(10.0f, 0.0f, 0.0f);
    }
    glEnd();

    // Eje Y
    glColor3f(0.0f, 1.0f, 0.0f);    // Green
    //  glColor3f(1.0f, 0.0f, 0.0f);    // Red
    glBegin(GL_LINES);
    {
        glVertex3f(0.0f, 0.0f, 0.0f);
        glVertex3f(0.0f, 10.0f, 0.0f);
    }
    glEnd();

    // Eje Z
    glColor3f(0.0f, 0.0f, 1.0f);    // Blue
    //  glColor3f(0.0f, 1.0f, 0.0f);    // Green
    glBegin(GL_LINES);
    {
        glVertex3f(0.0f, 0.0f, 0.0f);
        glVertex3f(0.0f, 0.0f, 10.0f);
    }
    glEnd();

    // Diagonal - segmento (0,0,0) - (1,1,1)
    glColor3f(1.0f, 1.0f, 1.0f);    // White
    glBegin(GL_LINES);
    {
        glVertex3f(0.0f, 0.0f, 0.0f);
        glVertex3f(0.35f, 0.35f, 0.35f);
    }
    glEnd();

    //glPopAttrib();
}

// --

void myElipse(GLfloat cx, GLfloat cy, GLfloat rx, GLfloat ry, int num_segments, enum TipoCuerpoCeleste tipoCuerpoCeleste /*, int32_t flags*/)
{
    //glPushAttrib(GL_CURRENT_BIT | GL_LIGHTING_BIT | GL_COLOR_BUFFER_BIT | GL_ENABLE_BIT);

    /*
    bool centroSol = (1 == (flags & 1));

    bool centroPlaneta = (2 == (flags & 2));

    bool centroPlanetaAnillos =  (4 == (flags & 4));
    */


    float theta = 2.0 * M_PI / (float)num_segments;
    float c = cosf(theta);//precalculate the sine and cosine
    float s = sinf(theta);
    float t;

    float x = 1.0;//we start at angle = 0 
    float y = 0.0;

    // https://www.mathwarehouse.com/ellipse/focus-of-ellipse.php
    float focus1 = sqrt(rx * rx - ry * ry);

    if (tipoCuerpoCeleste == tccAnillos)
    {
        glDisable(GL_LIGHTING);
    }
    else {
        glDisable(GL_LIGHTING);
    }

    glColor3f(0.75f, 0.6f, 0.4f);

    // --

    glBegin(GL_LINE_LOOP);

    for (int ii = 0; ii < num_segments; ii++)
    {
        //glEnable(GL_NORMALIZE);rrr
        //apply radius and offset
        float posicionEnX = x * rx + cx + focus1 / 2.0;
        float posicionEnZ = y * ry + cy;

        glVertex3f(posicionEnX, 0.0, posicionEnZ);//output vertex 

        switch (tipoCuerpoCeleste) {
        case tccPlaneta: // Orbita alrededor del Sol

            //printf("planeta a la vista\n");
            //glNormal3f(-1 * posicionEnX, 0.0, -1 * posicionEnZ);
            break;

        case tccSatelite: // Orbita alrededor de la Tierra
        case tccAnillos: // Anillos de Saturno
            //glNormal3f(-1.0, 0.0, 1.0f);
            break;
        }


        // 
        //apply the rotation matrix
        t = x;
        x = c * x - s * y;
        y = s * t + c * y;
    }

    glEnd();

    glColor3f(1.0f, 1.0f, 1.0f);    // White

    // --

    if (tipoCuerpoCeleste == tccAnillos)
    {
        glEnable(GL_LIGHTING);
    }
    else {
        glEnable(GL_LIGHTING);
    }

    //glPopAttrib();
    

}


// --

// Draw a single point
void myEstrella(GLfloat x, GLfloat y, GLfloat z) {
    glBegin(GL_POINTS);
    {
        glColor3f(1.0, 1.0, 1.0);
        glVertex3f(x, y, z);
    }
    glEnd();
}
