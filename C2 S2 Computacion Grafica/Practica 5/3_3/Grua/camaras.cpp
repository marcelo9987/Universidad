#include "comun.h"

void myCamara() {

    glViewport(0, 0, SCR_WIDTH, SCR_HEIGHT);
    glm::mat4 view;
    view = glm::mat4();
    view = glm::lookAt(glm::vec3(0.0, 0.0, 3.0), glm::vec3(0.0, 0.0, 0.0), glm::vec3(0.0, 1.0, 0.0));
    unsigned int viewLoc = glGetUniformLocation(myShaderProgram, "view");
    glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
    unsigned int viewPosLoc = glGetUniformLocation(myShaderProgram, "viewPos");
    glUniform3f(viewPosLoc, 0.0f, 0.0f, 3.0f);

    glm::mat4 projection;
    projection = glm::mat4();
    projection = glm::perspective(glm::radians(60.0f), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.01f, 5.0f);
    unsigned int projectionLoc = glGetUniformLocation(myShaderProgram, "projection");
    glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, glm::value_ptr(projection));
}

void myCamaraTerceraPersona(float posx, float posy, float posz, float angulo_base) {
    anguloPlano = 0;
    glViewport(0, 0, SCR_WIDTH, SCR_HEIGHT);
    glm::mat4 view;
    view = glm::mat4();
    view = glm::lookAt(
        glm::vec3(posx - 0.5 * cos360(angulo_base), posy - 0.5 * sin360(angulo_base), posz + 0.4),
        glm::vec3(posx + 10 * cos360(angulo_base), posy + 10 * sin360(angulo_base), posz),
        glm::vec3(0.0, 0.0, 1.0));
    unsigned int viewLoc = glGetUniformLocation(myShaderProgram, "view");
    glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
    unsigned int viewPosLoc = glGetUniformLocation(myShaderProgram, "viewPos");
    glUniform3f(viewPosLoc, posx - 0.5f * (float) cos360(angulo_base), posy - 0.5f * (float) sin360(angulo_base), posz + 0.4f);

    glm::mat4 projection;
    projection = glm::mat4();
    projection = glm::perspective(glm::radians(90.0f), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 5.0f);
    unsigned int projectionLoc = glGetUniformLocation(myShaderProgram, "projection");
    glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, glm::value_ptr(projection));
}

void myCamaraPrimeraPersona(float posx, float posy, float posz, float angulo_base) {
    anguloPlano = 0;
    glViewport(0, 0, SCR_WIDTH, SCR_HEIGHT);
    glm::mat4 view;
    view = glm::mat4();
    view = glm::lookAt(
        glm::vec3(posx + 0.5 * cos360(angulo_base), posy + 0.5 * sin360(angulo_base), posz + 0.4),
        glm::vec3(posx + 10 * cos360(angulo_base), posy + 10 * sin360(angulo_base), posz),
        glm::vec3(0.0, 0.0, 1.0));
    unsigned int viewLoc = glGetUniformLocation(myShaderProgram, "view");
    glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
    unsigned int viewPosLoc = glGetUniformLocation(myShaderProgram, "viewPos");
    glUniform3f(viewPosLoc, posx + 0.5f * (float)cos360(angulo_base), posy + 0.5f * (float) sin360(angulo_base), posz + 0.4f);

    glm::mat4 projection;
    projection = glm::mat4();
    projection = glm::perspective(glm::radians(60.0f), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 5.0f);
    unsigned int projectionLoc = glGetUniformLocation(myShaderProgram, "projection");
    glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, glm::value_ptr(projection));
}
