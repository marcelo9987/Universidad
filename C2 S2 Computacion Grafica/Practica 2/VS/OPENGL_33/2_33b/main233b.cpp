

#include <glad.h>

#include <stdio.h>
#include <iostream>
#include <lecturaShader.h>
#include <glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#define radianes 3.14159265/180.0


#pragma comment(lib, "glfw3.lib")


void processInput(GLFWwindow* window);

// settings
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 800;


extern GLuint setShaders(const char* nVertx, const char* nFrag);
GLuint shaderProgram;

unsigned int VAO;
unsigned int VAOCuadrado;

void dibujaEjes()
{
    unsigned int VBO, EBO;
    // set up vertex data (and buffer(s)) and configure vertex attributes
    // ------------------------------------------------------------------
    float vertices[] = {
        //Vertices          //Colores
        0.0f, 0.0f, 0.0f,	 1.0f, 1.0f, 1.0f,  // 0
        .5f, 0.0f, 0.0f,	 1.0f, 0.0f, 0.0f, //x
        0.0f, .5f, 0.0f,	 0.0f, 1.0f, 0.0f,// y
        0.0f, .5f, 0.0f,	 0.0f, 0.0f, 1.0f, // z  
        .5f , .5f, 0.5f,	1.0f, 1.0f, 1.0f // 1,1,1 bueno realmente la mitad
    };
    unsigned int indices[] = {  // empieza desde cero
        0, 1,
        0, 2,
        0, 3,
        0, 4
    };

    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    // position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    // position Color

    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);



    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    glBindVertexArray(0);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);

}

void dibujaCuadrado()
{
    unsigned int VBO, EBO;


    float vertices[] = {
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f, 0.0f,	//A 0
         0.5f, -0.5f,  0.5f,  1.0f, 0.0f, 0.0f,	//B 1 
         0.5f,  0.5f,  0.5f,  1.0f, 1.0f, 0.0f,	//C	2
        -0.5f,  0.5f,  0.5f,  1.0f, 0.0f, 0.0f, //D	3
         0.5f,	-0.5,  0.0,   0.0f, 0.0f, 1.0f, //E	4
         0.5f,	 0.5,  0.0,   1.0f, 0.0f, 0.0f  //F	5

    };

    unsigned int indices[] = {  // empieza desde cero
        1,2,0,
        3,0,2,
        5,2,4,
        1,4,2

    };



    glGenVertexArrays(1, &VAOCuadrado);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);
    // bind the Vertex Array Object first.
    glBindVertexArray(VAOCuadrado);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);


    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    // position Color

    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);



    glBindBuffer(GL_ARRAY_BUFFER, 0);
    //glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);


    glBindVertexArray(0);

    //glDeleteBuffers(1, &VBO);
    //glDeleteBuffers(1, &EBO);

}

void myTerceraPersona(float x, float y, float z, float angulo)
{
    glViewport(0, 0, SCR_WIDTH, SCR_HEIGHT);
    glm::mat4 view = glm::mat4();
    view = glm::lookAt(glm::vec3(0.0, 0.0, 2.0f),
        glm::vec3(0.0, 0.0, 1.0),
        glm::vec3(0.0f, 1.0f, 0.0f));
    glm::mat4 view2 = glm::mat4();

    view2 = glm::lookAt(glm::vec3(1.5, 0.0, .0f),
        glm::vec3(0.0, 0.0, .0),
        glm::vec3(0.0f, 1.0f, 0.0f));

    unsigned int viewLoc = glGetUniformLocation(shaderProgram, "view");
    glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));

    glm::mat4 projection = glm::mat4();
    projection = glm::perspective(glm::radians(100.0f), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 5.0f);
    unsigned int projectionLoc = glGetUniformLocation(shaderProgram, "projection");
    glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, glm::value_ptr(projection));

    glm::mat4 transform;
    transform = glm::mat4();
    //transform = glm::translate(transform, glm::vec3(0.5f, 0.5f, 0.0f));
    //transform = glm::rotate(transform, glm::radians(45.0f), glm::vec3(0.0, 0.0, 1.0));
    unsigned int transformLoc = glGetUniformLocation(shaderProgram, "transform");
    glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(transform));

}

void openGlInit()
{
    //Habilito aqui el depth en vez de arriba para los usuarios de linux y mac mejor arriba
    //Incializaciones varias
    glClearDepth(1.0f); //Valor z-buffer
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);  // valor limpieza buffer color
    glEnable(GL_DEPTH_TEST); // z-buffer
    glEnable(GL_CULL_FACE); //ocultacion caras back
    glCullFace(GL_BACK);

}


int main()
{
    // glfw: initialize and configure
    // ------------------------------
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);



    //Creo la ventana

    GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "Clases", NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);

    // glad: load all OpenGL function pointers
    // ---------------------------------------
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }


    //generarShader();
    shaderProgram = setShaders("camara.vert", "camara.frag");

    //dibujaEjes();
    dibujaCuadrado();
    //dibujaCuadrado();	
    openGlInit();


    // Lazo de la ventana mientras no la cierre
    // -----------
    while (!glfwWindowShouldClose(window))
    {
        // input
        // -----
        processInput(window);

        // render
        // ------
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f); //Borro el Buffer the la ventana
        glClear(GL_COLOR_BUFFER_BIT);
        glClear(GL_DEPTH_BUFFER_BIT);



        // ¿Uso los shaders?
        glUseProgram(shaderProgram);

        myTerceraPersona(0.0f, 0.0f, 1.0f, 45.0f);


        glEnable(GL_BLEND);




        // Medio cuadrado relleno

                // Medio cuadrado
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
        glBindVertexArray(VAOCuadrado);

        //glDrawArrays(GL_TRIANGLES, 3, 3);
        glDrawElements(GL_TRIANGLES, 12, GL_UNSIGNED_INT, (void*)(0 * sizeof(unsigned int)));


        //		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
                //glBindVertexArray(VAOCuadrado);
                //glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, (void*)(3 * sizeof(unsigned int))); // Nota a futuro: la forma de conseguir imprimir los indices a partir de n es usando el 
                                                                                                    // puntero (void*)(n * sizeof(unsigned int)) en el ultimo parametro indices por muy poco sentido que tenga

                //glDrawRangeElements(GL_TRIANGLES, 0, 2, 3, GL_UNSIGNED_INT, (void*)(6 * sizeof(unsigned int)));

        glBindVertexArray(0); // no need to unbind it every time 

        glDisable(GL_BLEND);




        // glfw: swap 
        // -------------------------------------------------------------------------------
        glfwSwapBuffers(window);
        glfwPollEvents();
    }


    glDeleteVertexArrays(1, &VAO);



    glfwTerminate();
    return 0;
}

void processInput(GLFWwindow* window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}

