#include "cargasIniciales.h"
#include "controles.h"

#include "camaras.h"
#include "piscina.h"

#include <stdio.h>
#include <windows.h>
#include <iostream>
#include "esfera.h"
#include "lecturaShader_0_9.h"


//


extern float vertices_esfera[];

// extern GLuint setShaders(const char *nVertx, const char *nFrag);


glm::mat4 transform;
glm::mat4 transformtemp;
int fondo;


//Dibujamos la esfera
void dibujaEsfera() {
    unsigned int VBO;

    glGenVertexArrays(1, &VAOEsfera);
    glGenBuffers(1, &VBO);

    glBindVertexArray(VAOEsfera);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices_esfera), vertices_esfera, GL_STATIC_DRAW);

    //Normales
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void *) 0);
    glEnableVertexAttribArray(1);

    //Texture
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void *) (3 * sizeof(float)));
    glEnableVertexAttribArray(2);

    //Vertices
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void *) (5 * sizeof(float)));
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
    glDeleteBuffers(1, &VBO);
}

//Dibujamos el cuadrado
void dibujaCuadrado() {
    unsigned int VBO, EBO;


    float vertices[] = {
            0.5f, -0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f,
            -0.5f, -0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f,
            -0.5f, 0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f,

            -0.5f, 0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f,
            0.5f, 0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f,
            0.5f, -0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f,
    };


    glGenVertexArrays(1, &VAOCuadrado);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);
    // bind the Vertex Array Object first.
    glBindVertexArray(VAOCuadrado);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void *) 0);
    glEnableVertexAttribArray(0);

    // normales
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void *) (3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    // texture
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void *) (6 * sizeof(float)));
    glEnableVertexAttribArray(2);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);

}

int dibujaCubo() {
    unsigned int VBO, EBO;


    float vertices[] = {
            //CARA DELANTERA
            -0.5f, 0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f,
            0.5f, 0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f,
            0.5f, 0.5f, 0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f,

            0.5f, 0.5f, 0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f,
            -0.5f, 0.5f, 0.5f, 0.0f, 1.0f, 0.0f, 1.0f, 1.0f,
            -0.5f, 0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f,

            //CARA TRASERA
            0.5f, -0.5f, -0.5f, 0.0f, -1.0f, 0.0f, 1.0f, 0.0f,
            -0.5f, -0.5f, -0.5f, 0.0f, -1.0f, 0.0f, 0.0f, 0.0f,
            0.5f, -0.5f, 0.5f, 0.0f, -1.0f, 0.0f, 1.0f, 1.0f,

            -0.5f, -0.5f, 0.5f, 0.0f, -1.0f, 0.0f, 0.0f, 1.0f,
            0.5f, -0.5f, 0.5f, 0.0f, -1.0f, 0.0f, 1.0f, 1.0f,
            -0.5f, -0.5f, -0.5f, 0.0f, -1.0f, 0.0f, 0.0f, 0.0f,

            //CARA SUPERIOR
            0.5, -0.5, 0.5f, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f,
            -0.5f, -0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f,
            -0.5, 0.5, 0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f,

            -0.5, 0.5, 0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f,
            0.5, 0.5, 0.5f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f,
            0.5f, -0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f,

            //CARA DERECHA
            0.5, -0.5, -0.5f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f,
            0.5, -0.5, 0.5f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f,
            0.5, 0.5, 0.5f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f,

            0.5, 0.5, 0.5f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f,
            0.5, 0.5, -0.5f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f,
            0.5, -0.5, -0.5f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f,

            //CARA IZQUIERDA
            -0.5f, -0.5f, 0.5f, -1.0f, 0.0f, 0.0f, 1.0f, 1.0f,
            -0.5f, -0.5f, -0.5f, -1.0f, 0.0f, 0.0f, 1.0f, 0.0f,
            -0.5f, 0.5f, -0.5f, -1.0f, 0.0f, 0.0f, 0.0f, 0.0f,

            -0.5f, 0.5f, -0.5f, -1.0f, 0.0f, 0.0f, 0.0f, 0.0f,
            -0.5f, 0.5f, 0.5f, -1.0f, 0.0f, 0.0f, 0.0f, 1.0f,
            -0.5f, -0.5f, 0.5f, -1.0f, 0.0f, 0.0f, 1.0f, 1.0f,


            //CARA INFERIOR
            -0.5f, -0.5f, -0.5f, 0.0f, 0.0f, -1.0f, 1.0f, 0.0f,
            0.5f, -0.5f, -0.5f, 0.0f, 0.0f, -1.0f, 0.0f, 0.0f,
            0.5f, 0.5f, -0.5f, 0.0f, 0.0f, -1.0f, 0.0f, 1.0f,

            0.5f, 0.5f, -0.5f, 0.0f, 0.0f, -1.0f, 0.0f, 1.0f,
            -0.5f, 0.5f, -0.5f, 0.0f, 0.0f, -1.0f, 1.0f, 1.0f,
            -0.5f, -0.5f, -0.5f, 0.0f, 0.0f, -1.0f, 1.0f, 0.0f,
    };

    glGenVertexArrays(1, &VAOCubo);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);
    // bind the Vertex Array Object first.
    glBindVertexArray(VAOCubo);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);


    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void *) 0);
    glEnableVertexAttribArray(0);

    //position Color
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void *) (3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    //texture
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void *) (6 * sizeof(float)));
    glEnableVertexAttribArray(2);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);

    return (VAOCubo);

}

int dibujaCuboDestapado() {
    unsigned int VBO, EBO;


    float vertices[] = {
            //CARA DELANTERA
            -0.5f, 0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f,
            0.5f, 0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f,
            0.5f, 0.5f, 0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f,

            0.5f, 0.5f, 0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f,
            -0.5f, 0.5f, 0.5f, 0.0f, 1.0f, 0.0f, 1.0f, 1.0f,
            -0.5f, 0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f,

            //CARA TRASERA
            0.5f, -0.5f, -0.5f, 0.0f, -1.0f, 0.0f, 1.0f, 0.0f,
            -0.5f, -0.5f, -0.5f, 0.0f, -1.0f, 0.0f, 0.0f, 0.0f,
            0.5f, -0.5f, 0.5f, 0.0f, -1.0f, 0.0f, 1.0f, 1.0f,

            -0.5f, -0.5f, 0.5f, 0.0f, -1.0f, 0.0f, 0.0f, 1.0f,
            0.5f, -0.5f, 0.5f, 0.0f, -1.0f, 0.0f, 1.0f, 1.0f,
            -0.5f, -0.5f, -0.5f, 0.0f, -1.0f, 0.0f, 0.0f, 0.0f,

            //CARA DERECHA
            0.5, -0.5, -0.5f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f,
            0.5, -0.5, 0.5f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f,
            0.5, 0.5, 0.5f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f,

            0.5, 0.5, 0.5f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f,
            0.5, 0.5, -0.5f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f,
            0.5, -0.5, -0.5f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f,

            //CARA IZQUIERDA
            -0.5f, -0.5f, 0.5f, -1.0f, 0.0f, 0.0f, 1.0f, 1.0f,
            -0.5f, -0.5f, -0.5f, -1.0f, 0.0f, 0.0f, 1.0f, 0.0f,
            -0.5f, 0.5f, -0.5f, -1.0f, 0.0f, 0.0f, 0.0f, 0.0f,

            -0.5f, 0.5f, -0.5f, -1.0f, 0.0f, 0.0f, 0.0f, 0.0f,
            -0.5f, 0.5f, 0.5f, -1.0f, 0.0f, 0.0f, 0.0f, 1.0f,
            -0.5f, -0.5f, 0.5f, -1.0f, 0.0f, 0.0f, 1.0f, 1.0f,

            //CARA INFERIOR
            -0.5f, -0.5f, -0.5f, 0.0f, 0.0f, -1.0f, 1.0f, 0.0f,
            0.5f, -0.5f, -0.5f, 0.0f, 0.0f, -1.0f, 0.0f, 0.0f,
            0.5f, 0.5f, -0.5f, 0.0f, 0.0f, -1.0f, 0.0f, 1.0f,

            0.5f, 0.5f, -0.5f, 0.0f, 0.0f, -1.0f, 0.0f, 1.0f,
            -0.5f, 0.5f, -0.5f, 0.0f, 0.0f, -1.0f, 1.0f, 1.0f,
            -0.5f, -0.5f, -0.5f, 0.0f, 0.0f, -1.0f, 1.0f, 0.0f,

            //Falta la cara superior
    };


    glGenVertexArrays(1, &VAOCuboDestapado);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAOCuboDestapado);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);


    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void *) 0);
    glEnableVertexAttribArray(0);

    //position Color
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void *) (3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    //texture
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void *) (6 * sizeof(float)));
    glEnableVertexAttribArray(2);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);

    return (VAOCubo);


}


glm::vec3 nuevaPos(glm::mat4 transfm) {

    return glm::vec3(transfm * glm::vec4(0.0f, 0.0f, 0.0f, 1.0f));
}

void texShader() {
    glUniform1i(glGetUniformLocation(myShaderProgram, "Texturas[0]"), 0);
    glUniform1i(glGetUniformLocation(myShaderProgram, "Texturas[1]"), 1);
    glUniform1i(glGetUniformLocation(myShaderProgram, "Texturas[2]"), 2);
    glUniform1i(glGetUniformLocation(myShaderProgram, "Texturas[3]"), 3);
    glUniform1i(glGetUniformLocation(myShaderProgram, "Texturas[4]"), 4);
    glUniform1i(glGetUniformLocation(myShaderProgram, "Texturas[5]"), 5);
    glUniform1i(glGetUniformLocation(myShaderProgram, "Texturas[6]"), 6);
    glUniform1i(glGetUniformLocation(myShaderProgram, "Texturas[7]"), 7);
    glUniform1i(glGetUniformLocation(myShaderProgram, "Texturas[8]"), 8);
    glUniform1i(glGetUniformLocation(myShaderProgram, "Texturas[9]"), 9);
    glUniform1i(glGetUniformLocation(myShaderProgram, "Texturas[10]"), 10);
    glUniform1i(glGetUniformLocation(myShaderProgram, "Texturas[11]"), 11);
    glUniform1i(glGetUniformLocation(myShaderProgram, "Texturas[12]"), 12);
    glUniform1i(glGetUniformLocation(myShaderProgram, "Texturas[13]"), 13);
    glUniform1i(glGetUniformLocation(myShaderProgram, "Texturas[14]"), 14);
    glUniform1i(glGetUniformLocation(myShaderProgram, "Texturas[15]"), 15);
    glUniform1i(glGetUniformLocation(myShaderProgram, "Texturas[16]"), 16);
}


//Función que dibuja el suelo
void dibujasuelo(int transformLoc) {
    //Color suelo
    unsigned int colorLocSuelo = glGetUniformLocation(myShaderProgram, "objectColor");
    glUniform3f(colorLocSuelo, 0.5, 0.5, 0.5);

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, texturaSuelo);

    float i, j;
    float escalasuelo = 10;

    for (i = -2; i <= 2; i += (1 / escalasuelo)) {
        for (j = -2; j <= 2; j += (1 / escalasuelo)) {
            transform = glm::mat4();
            transform = glm::rotate(transform, (float) gradosARadianes(anguloPlano), glm::vec3(1.0f, 0.0f, 0.0f));
            transform = glm::translate(transform, glm::vec3(i, j, 0.0f));
            transform = glm::scale(transform, glm::vec3((1 / escalasuelo), (1 / escalasuelo), (1 / escalasuelo)));
            glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(transform));
            glBindVertexArray(VAOCuadrado);
            glDrawArrays(GL_TRIANGLES, 0, 6);
        }
    }
}

//Dibujamos la base de la grúa
void dibujabase(int transformLoc, int colorLoBase) {
    //glUniform3f(colorLoBase, base.colx, base.coly, base.colz);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, base.textura);

    transform = glm::mat4();
    transform = glm::rotate(transform, (float) gradosARadianes(anguloPlano), glm::vec3(1.0f, 0.0f, 0.0f));
    transform = glm::translate(transform, glm::vec3(base.px, base.py, base.pz));
    transform = glm::rotate(transform, (float) gradosARadianes(base.angulo_trans), glm::vec3(0.0f, 0.0f, 1.0f));
    transformtemp = transform;
    transform = glm::scale(transform, glm::vec3(base.sx, base.sy, base.sz));
    glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(transform));
    glBindVertexArray(base.listarender);
    glDrawArrays(GL_TRIANGLES, 0, 36);
}

//Dibujamos las articulaciones de la grúa
void dibujaArtBra(ElementoGrua parte, int transformLoc, int colorLoBase) {

    //glUniform3f(colorLoBase, parte.colx, parte.coly, parte.colz);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, parte.textura);

    transform = glm::mat4();
    transform = transformtemp;
    transform = glm::translate(transform, glm::vec3(parte.px, parte.py, parte.pz));
    if (parte.articulacion == 1) {
        transform = glm::rotate(transform, (float) gradosARadianes(parte.angulo_trans), glm::vec3(1.0f, 0.0f, 0.0f));
        transform = glm::rotate(transform, (float) gradosARadianes(parte.angulo_trans_2), glm::vec3(0.0f, 1.0f, 0.0f));
    }
    transformtemp = transform;
    transform = glm::scale(transform, glm::vec3(parte.sx, parte.sy, parte.sz));
    glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(transform));
    glBindVertexArray(parte.listarender);
    if (parte.articulacion == 1) {
        glDrawArrays(GL_TRIANGLES, 0, 1080);
    } else {
        glDrawArrays(GL_TRIANGLES, 0, 36);
    }
}

//Dibujamos el foco de iluinación
void dibujaFoco(int transformLoc) {
    //Foco
    transform = glm::mat4(); // identity matrix
    transform = transformtemp;
    transform = glm::translate(transform, glm::vec3(foco.px, foco.py, foco.pz));
    transformtemp = transform;
    transform = glm::scale(transform, glm::vec3(foco.sx, foco.sy, foco.sz));
    glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(transform));
}

int main() {
    // glfw: initialize and configure
    // ------------------------------
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    //'Z,X,C'->Cambiar vista, 'L,K'-> mover la camaraSeleccionada, 'T,F,G,H'-> mover brazo arriba, 'A,D,S,W'-> mover brazo abajo
    //
    //Creo la ventana
    GLFWwindow *window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "Grúa Riazor", NULL, NULL);
    if (window == NULL) {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, myFramebufferSizeCallback);

    // glad: load all OpenGL function pointers
    // ---------------------------------------
    if (!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress)) {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    glfwSetKeyCallback(window, myKeyCallback);
    myOpenGlInit();

    //generarShader();
    myShaderProgram = setShaders("Shaders/shader.vert", "Shaders/shader.frag");

    glUniform1i(glGetUniformLocation(myShaderProgram, "textura1"), 0);
    //glUniform1i(glGetUniformLocation(myShaderProgram, "textura2"), 1);

    dibujaCuadrado();
    dibujaCubo();
    dibujaCuboDestapado();
    dibujaEsfera();

    base.listarender = base1.listarender = base2.listarender = fondo = VAOCubo;
    baseA1.listarender = baseA2.listarender = VAOEsfera;
    fondo = VAOCuboDestapado;

    //inicializarTexturas();

    cargaTexturas();

    cargaTexturasPiscina();

    glUseProgram(myShaderProgram);

    // Pasamos las texturas al shader
    texShader();

    // Habilitamos la mezcla de texturas
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    // Lazo de la ventana mientras no la cierre
    // -----------
    while (!glfwWindowShouldClose(window)) {
        // input
        // -----
        myProcessInput(window);
        // render
        // ------
        glClearColor(0.0f, 0.5f, 1.0f, 1.0f); //Borro el Buffer the la ventana
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        //Diferentes tipos de camaraSeleccionada
        if (camaraSeleccionada == 1) {
            myCamara();
        }
        if (camaraSeleccionada == 2) {
            myCamaraTerceraPersona(base.px, base.py, base.pz, base.angulo_trans);
        }
        if (camaraSeleccionada == 3) {
            myCamaraPrimeraPersona(base.px, base.py, base.pz, base.angulo_trans);
        }

        //Dibujamos en GL_FILL
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

        //Transformaciones
        unsigned int transformLoc = glGetUniformLocation(myShaderProgram, "transform");
        //Luz
        unsigned int lightColorLoc = glGetUniformLocation(myShaderProgram, "lightColor");
        glUniform3f(lightColorLoc, 1.0f, 1.0f, 1.0f);


        //Dibujamos el suelo
        dibujasuelo(transformLoc);

        //Movimiento de la base con aceleración
        base.px += velocidadGrua * (float) cos360(base.angulo_trans);
        base.py += velocidadGrua * (float) sin360(base.angulo_trans);

        //Color para la base
        unsigned int colorLoGrua = glGetUniformLocation(myShaderProgram, "objectColor");

        //Base
        dibujabase(transformLoc, colorLoGrua);
        //Primera articulación
        dibujaArtBra(baseA1, transformLoc, colorLoGrua);
        //Primer brazo
        dibujaArtBra(base1, transformLoc, colorLoGrua);
        //Segunda articulación
        dibujaArtBra(baseA2, transformLoc, colorLoGrua);
        //Segundo brazo
        dibujaArtBra(base2, transformLoc, colorLoGrua);
        //Dibujamos el foco
        dibujaFoco(transformLoc);

        //Fondo
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, texturaEstadio);
        glDisable(GL_TEXTURE_2D);
        glm::mat4 transform1;
        transform1 = glm::mat4();
        transform1 = glm::translate(transform1, glm::vec3(0.0f, 0.0f, 0.0f));
        transform1 = glm::scale(transform1, glm::vec3(4.0f, 4.0f, 4.0f));
        glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(transform1));
        glBindVertexArray(fondo);
        glDrawArrays(GL_TRIANGLES, 0, 36);
        glEnable(GL_TEXTURE_2D);

        //Dibujamos la piscina
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, texturaPiscina[piscina_instante]);
        glDisable(GL_TEXTURE_2D);
        glEnable(GL_TEXTURE_2D);
        dibujaPiscina(transformLoc);

        //Desactivamos piscina
        glUniform1i(glGetUniformLocation(myShaderProgram, "piscina"), 0);

        GLint lightPosLoc = glGetUniformLocation(myShaderProgram, "lightPos");
        glm::vec3 pos_linterna = nuevaPos(transform);
        glUniform3f(lightPosLoc, pos_linterna.x, pos_linterna.y, pos_linterna.z);

        GLint spotCutoffLoc = glGetUniformLocation(myShaderProgram, "spotCutoff");
        glUniform1f(spotCutoffLoc, gradosSpotCutoff);

        // glfw: swap
        // -------------------------------------------------------------------------------
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glDeleteVertexArrays(1, &VAO);
    glfwTerminate();
    return 0;
}
