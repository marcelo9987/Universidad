#include "piscina.h"
#include "comun.h"


//void ajustarAnimacionPiscina();
void ajustarAnimacionPiscina() {
    piscina_contador++;
    if (piscina_contador == 60) {
        if (piscina_instante == 10) {
            piscina_instante = 12;
        }
        else if (piscina_instante < 15) {
            piscina_instante++;
        }
        else {
            piscina_instante = 0;
        }
        piscina_contador = 0;
    }
}

void activarTexturasPiscina() {
    switch (piscina_instante) {
    case 0:
        glActiveTexture(GL_TEXTURE1);
        break;
    case 1:
        glActiveTexture(GL_TEXTURE2);
        break;
    case 2:
        glActiveTexture(GL_TEXTURE3);
        break;
    case 3:
        glActiveTexture(GL_TEXTURE4);
        break;
    case 4:
        glActiveTexture(GL_TEXTURE5);
        break;
    case 5:
        glActiveTexture(GL_TEXTURE6);
        break;
    case 6:
        glActiveTexture(GL_TEXTURE7);
        break;
    case 7:
        glActiveTexture(GL_TEXTURE8);
        break;
    case 8:
        glActiveTexture(GL_TEXTURE9);
        break;
    case 9:
        glActiveTexture(GL_TEXTURE10);
        break;
    case 10:
        glActiveTexture(GL_TEXTURE11);
        break;
    case 11:
        glActiveTexture(GL_TEXTURE12);
        break;
    case 12:
        glActiveTexture(GL_TEXTURE13);
        break;
    case 13:
        glActiveTexture(GL_TEXTURE14);
        break;
    case 14:
        glActiveTexture(GL_TEXTURE15);
        break;
    case 15:
        glActiveTexture(GL_TEXTURE16);
        break;

    }
}

//Función que dibuja la piscina
void dibujaPiscina(int transformLoc) {
    activarTexturasPiscina();

    glBindTexture(GL_TEXTURE_2D, texturaPiscina[piscina_instante]);
    glUniform1i(glGetUniformLocation(myShaderProgram, "piscina_instante"), piscina_instante);

    // Ajustamos la animacion para que sea mas fluida
    ajustarAnimacionPiscina();


    glUniform1i(glGetUniformLocation(myShaderProgram, "piscina"), 1);
    glm::mat4 transform1;
    transform1 = glm::mat4();
    transform1 = glm::translate(transform1, glm::vec3(-1.0f, 0.0f, -0.44f));
    transform1 = glm::scale(transform1, glm::vec3(1.0f, 1.0f, 1.0f));
    glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(transform1));

    glBindVertexArray(VAOCuadrado);
    glDrawArrays(GL_TRIANGLES, 0, 6);
}
