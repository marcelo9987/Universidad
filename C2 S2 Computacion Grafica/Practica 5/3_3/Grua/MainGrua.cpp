#include <glad.h>
#include <glfw3.h>
#include <stdio.h>
#include <windows.h>
#include <iostream>
#include "esfera.h"
#include "lecturaShader_0_9.h"
//Movimiento
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

//

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#define ARADIANES 0.0174

void processInput(GLFWwindow* window);

// settings
unsigned int SCR_WIDTH = 720;
unsigned int SCR_HEIGHT = 720;

extern float vertices_esfera[];
extern GLuint setShaders(const char* nVertx, const char* nFrag);
GLuint shaderProgram;

//VAO
unsigned int VAO;
unsigned int VAOEsfera;
unsigned int VAOCubo;
unsigned int VAOCuboDestapado;
unsigned int VAOCuadrado;
//Angulo plano
float angulo;
//Variables para el moviminto de la grua
float velocidad;
float ang_giro;
int camara = 1;
float grados = 25.0;
glm::mat4 transform;
glm::mat4 transformtemp;
int fondo;

unsigned int texturaPiscina[16] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
unsigned int texturaSuelo = 0;
unsigned int texturaEstadio = 0;

// Animacion piscia
int instante = 0;
int contador = 0;

typedef struct {
	float px, py, pz;			//posicion inicial
	float angulo_trans;			//angulo giro x
	float angulo_trans_2;		//angulo giro z
	float sx, sy, sz;			//escalado en los ejes
	unsigned int listarender;	//VAO
	float colx, coly, colz;     //Color
	int articulacion;
	unsigned int textura;
	int isbase;
}objeto;

objeto base = { 0 ,0 ,0.15 ,0 ,0 ,.3  ,.2  ,.2  ,0 ,1.0 ,1.0 ,0.0, 0, 0, 1 };
objeto baseA1 = { 0 ,0 ,0.10 ,0 ,0 ,.07 ,.07 ,.07 ,0 ,0.0 ,1.0 ,1.0, 1, 0, 0 };
objeto base1 = { 0 ,0 ,0.10 ,0 ,0 ,.05 ,.05 ,.3  ,0 ,1.0 ,1.0 ,0.0, 0, 0, 0 };
objeto baseA2 = { 0 ,0 ,0.15 ,0 ,0 ,.05 ,.05 ,.05 ,0 ,0.0 ,1.0 ,1.0, 1, 0, 0 };
objeto base2 = { 0 ,0 ,0.11 ,0 ,0 ,.05 ,.05 ,.3  ,0 ,1.0 ,1.0 ,0.0, 0, 0, 0 };
objeto foco = { 0 ,0 ,0.25 ,0 ,0 ,.05 ,.05 ,.05 ,0 ,0.0 ,1.0 ,0.0, 0, 0, 0 };

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);

void myCamara() {

	glViewport(0, 0, SCR_WIDTH, SCR_HEIGHT);
	glm::mat4 view;
	view = glm::mat4();
	view = glm::lookAt(glm::vec3(0.0, 0.0, 3.0), glm::vec3(0.0, 0.0, 0.0), glm::vec3(0.0, 1.0, 0.0));
	unsigned int viewLoc = glGetUniformLocation(shaderProgram, "view");
	glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
	unsigned int viewPosLoc = glGetUniformLocation(shaderProgram, "viewPos");
	glUniform3f(viewPosLoc, 0.0f, 0.0f, 3.0f);

	glm::mat4 projection;
	projection = glm::mat4();
	projection = glm::perspective(glm::radians(60.0f), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.01f, 5.0f);
	unsigned int projectionLoc = glGetUniformLocation(shaderProgram, "projection");
	glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, glm::value_ptr(projection));
}

void terceraPersona(float posx, float posy, float posz, float angulo_base) {
	angulo = 0;
	glViewport(0, 0, SCR_WIDTH, SCR_HEIGHT);
	glm::mat4 view;
	view = glm::mat4();
	view = glm::lookAt(
		glm::vec3(posx - 0.5 * cos(angulo_base * ARADIANES), posy - 0.5 * sin(angulo_base * ARADIANES), posz + 0.4),
		glm::vec3(posx + 10 * cos(angulo_base * ARADIANES), posy + 10 * sin(angulo_base * ARADIANES), posz),
		glm::vec3(0.0, 0.0, 1.0));
	unsigned int viewLoc = glGetUniformLocation(shaderProgram, "view");
	glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
	unsigned int viewPosLoc = glGetUniformLocation(shaderProgram, "viewPos");
	glUniform3f(viewPosLoc, posx - 0.5 * cos(angulo_base * ARADIANES), posy - 0.5 * sin(angulo_base * ARADIANES), posz + 0.4);

	glm::mat4 projection;
	projection = glm::mat4();
	projection = glm::perspective(glm::radians(90.0f), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 5.0f);
	unsigned int projectionLoc = glGetUniformLocation(shaderProgram, "projection");
	glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, glm::value_ptr(projection));
}

void primeraPersona(float posx, float posy, float posz, float angulo_base) {
	angulo = 0;
	glViewport(0, 0, SCR_WIDTH, SCR_HEIGHT);
	glm::mat4 view;
	view = glm::mat4();
	view = glm::lookAt(
		glm::vec3(posx + 0.5 * cos(angulo_base * ARADIANES), posy + 0.5 * sin(angulo_base * ARADIANES), posz + 0.4),
		glm::vec3(posx + 10 * cos(angulo_base * ARADIANES), posy + 10 * sin(angulo_base * ARADIANES), posz),
		glm::vec3(0.0, 0.0, 1.0));
	unsigned int viewLoc = glGetUniformLocation(shaderProgram, "view");
	glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
	unsigned int viewPosLoc = glGetUniformLocation(shaderProgram, "viewPos");
	glUniform3f(viewPosLoc, posx + 0.5 * cos(angulo_base * ARADIANES), posy + 0.5 * sin(angulo_base * ARADIANES), posz + 0.4);

	glm::mat4 projection;
	projection = glm::mat4();
	projection = glm::perspective(glm::radians(60.0f), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 5.0f);
	unsigned int projectionLoc = glGetUniformLocation(shaderProgram, "projection");
	glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, glm::value_ptr(projection));
}


//Dibujamos la esfera
void dibujaEsfera() {
	unsigned int VBO;

	glGenVertexArrays(1, &VAOEsfera);
	glGenBuffers(1, &VBO);

	glBindVertexArray(VAOEsfera);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices_esfera), vertices_esfera, GL_STATIC_DRAW);

	//Normales
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(1);

	//Texture
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(2);

	//Vertices
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(5 * sizeof(float)));
	glEnableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
	glDeleteBuffers(1, &VBO);
}

//Dibujamos el cuadrado
void dibujaCuadrado() {
	unsigned int VBO, EBO;


	float vertices[] = {
		 0.5f, -0.5f, 0.5f,		0.0f, 0.0f, 1.0f,		1.0f, 0.0f,
		-0.5f, -0.5f, 0.5f,		0.0f, 0.0f, 1.0f,		0.0f, 0.0f,
		-0.5f,  0.5f, 0.5f,		0.0f, 0.0f, 1.0f,		0.0f, 1.0f,

		-0.5f,  0.5f, 0.5f,		0.0f, 0.0f, 1.0f,		0.0f, 1.0f,
		 0.5f,  0.5f, 0.5f,		0.0f, 0.0f, 1.0f,		1.0f, 1.0f,
		 0.5f, -0.5f, 0.5f,		0.0f, 0.0f, 1.0f,		1.0f, 0.0f,
	};


	glGenVertexArrays(1, &VAOCuadrado);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);
	// bind the Vertex Array Object first.
	glBindVertexArray(VAOCuadrado);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	// normales
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	// texture
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
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
		-0.5f, 0.5f, -0.5f,		0.0f, 1.0f, 0.0f,		1.0f, 0.0f,
		 0.5f, 0.5f, -0.5f,		0.0f, 1.0f, 0.0f,		0.0f, 0.0f,
		 0.5f, 0.5f, 0.5f,		0.0f, 1.0f, 0.0f,		0.0f, 1.0f,

		 0.5f, 0.5f, 0.5f,		0.0f, 1.0f, 0.0f,		0.0f, 1.0f,
		-0.5f, 0.5f, 0.5f,		0.0f, 1.0f, 0.0f,		1.0f, 1.0f,
		-0.5f, 0.5f, -0.5f,		0.0f, 1.0f, 0.0f,		1.0f, 0.0f,

		//CARA TRASERA
		 0.5f, -0.5f, -0.5f,	0.0f, -1.0f, 0.0f,		1.0f, 0.0f,
		-0.5f, -0.5f, -0.5f,	0.0f, -1.0f, 0.0f,		0.0f, 0.0f,
		 0.5f, -0.5f, 0.5f,		0.0f, -1.0f, 0.0f,		1.0f, 1.0f,

		-0.5f, -0.5f, 0.5f,		0.0f, -1.0f, 0.0f,		0.0f, 1.0f,
		 0.5f, -0.5f, 0.5f,		0.0f, -1.0f, 0.0f,		1.0f, 1.0f,
		-0.5f, -0.5f, -0.5f,	0.0f, -1.0f, 0.0f,		0.0f, 0.0f,

		//CARA SUPERIOR
		  0.5, -0.5, 0.5f,		0.0f, 0.0f, 1.0f,		1.0f, 0.0f,
		 -0.5f, -0.5f, 0.5f,		0.0f, 0.0f, 1.0f,		0.0f, 0.0f,
		 -0.5, 0.5, 0.5f,		0.0f, 0.0f, 1.0f,		0.0f, 1.0f,

		 -0.5, 0.5, 0.5f,		0.0f, 0.0f, 1.0f,		0.0f, 1.0f,
		  0.5, 0.5, 0.5f,		0.0f, 0.0f, 1.0f,		1.0f, 1.0f,
		  0.5f, -0.5f, 0.5f,		0.0f, 0.0f, 1.0f,		1.0f, 0.0f,

		//CARA DERECHA
		 0.5, -0.5, -0.5f,		1.0f, 0.0f, 0.0f,		0.0f, 0.0f,
		 0.5, -0.5, 0.5f,		1.0f, 0.0f, 0.0f,		0.0f, 1.0f,
		 0.5, 0.5, 0.5f,		1.0f, 0.0f, 0.0f,		1.0f, 1.0f,

		 0.5, 0.5, 0.5f,		1.0f, 0.0f, 0.0f,		1.0f, 1.0f,
		 0.5, 0.5, -0.5f,		1.0f, 0.0f, 0.0f,		1.0f, 0.0f,
		 0.5, -0.5, -0.5f,		1.0f, 0.0f, 0.0f,		0.0f, 0.0f,

		 //CARA IZQUIERDA
		 -0.5f, -0.5f, 0.5f,		-1.0f, 0.0f, 0.0f,		1.0f, 1.0f,
		 -0.5f, -0.5f, -0.5f,	-1.0f, 0.0f, 0.0f,		1.0f, 0.0f,
		 -0.5f, 0.5f, -0.5f,		-1.0f, 0.0f, 0.0f,		0.0f, 0.0f,

		 -0.5f, 0.5f, -0.5f,		-1.0f, 0.0f, 0.0f,		0.0f, 0.0f,
		 -0.5f, 0.5f, 0.5f,		-1.0f, 0.0f, 0.0f,		0.0f, 1.0f,
		 -0.5f, -0.5f, 0.5f,		-1.0f, 0.0f, 0.0f,		1.0f, 1.0f,


		 //CARA INFERIOR
		 -0.5f,-0.5f,-0.5f,		0.0f, 0.0f, -1.0f,		1.0f, 0.0f,
		  0.5f,-0.5f,-0.5f,		0.0f, 0.0f, -1.0f,		0.0f, 0.0f,
		  0.5f,0.5f,-0.5f,		0.0f, 0.0f, -1.0f,		0.0f, 1.0f,

		  0.5f, 0.5f, -0.5f,		0.0f, 0.0f, -1.0f,		0.0f, 1.0f,
		 -0.5f,0.5f,-0.5f,		0.0f, 0.0f, -1.0f,		1.0f, 1.0f,
		 -0.5f,-0.5f,-0.5f,		0.0f, 0.0f, -1.0f,		1.0f, 0.0f,
	};

	glGenVertexArrays(1, &VAOCubo);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);
	// bind the Vertex Array Object first.
	glBindVertexArray(VAOCubo);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);


	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	//position Color
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	//texture
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
	glEnableVertexAttribArray(2);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
	glDeleteBuffers(1, &VBO);
	glDeleteBuffers(1, &EBO);

	return(VAOCubo);

}

int dibujaCuboDestapado() {
	unsigned int VBO, EBO;


	float vertices[] = {
		//CARA DELANTERA
		-0.5f, 0.5f, -0.5f,		0.0f, 1.0f, 0.0f,		1.0f, 0.0f,
		 0.5f, 0.5f, -0.5f,		0.0f, 1.0f, 0.0f,		0.0f, 0.0f,
		 0.5f, 0.5f,  0.5f,		0.0f, 1.0f, 0.0f,		0.0f, 1.0f,

		 0.5f, 0.5f,  0.5f,		0.0f, 1.0f, 0.0f,		0.0f, 1.0f,
		-0.5f, 0.5f,  0.5f,		0.0f, 1.0f, 0.0f,		1.0f, 1.0f,
		-0.5f, 0.5f, -0.5f,		0.0f, 1.0f, 0.0f,		1.0f, 0.0f,

		//CARA TRASERA
		 0.5f, -0.5f, -0.5f,	0.0f, -1.0f, 0.0f,		1.0f, 0.0f,
		-0.5f, -0.5f, -0.5f,	0.0f, -1.0f, 0.0f,		0.0f, 0.0f,
		 0.5f, -0.5f,  0.5f,	0.0f, -1.0f, 0.0f,		1.0f, 1.0f,

		-0.5f, -0.5f, 0.5f,		0.0f, -1.0f, 0.0f,		0.0f, 1.0f,
		 0.5f, -0.5f, 0.5f,		0.0f, -1.0f, 0.0f,		1.0f, 1.0f,
		-0.5f, -0.5f, -0.5f,	0.0f, -1.0f, 0.0f,		0.0f, 0.0f,

		//CARA DERECHA
		 0.5, -0.5, -0.5f,		1.0f, 0.0f, 0.0f,		0.0f, 0.0f,
		 0.5, -0.5, 0.5f,		1.0f, 0.0f, 0.0f,		0.0f, 1.0f,
		 0.5, 0.5, 0.5f,		1.0f, 0.0f, 0.0f,		1.0f, 1.0f,

		 0.5, 0.5, 0.5f,		1.0f, 0.0f, 0.0f,		1.0f, 1.0f,
		 0.5, 0.5, -0.5f,		1.0f, 0.0f, 0.0f,		1.0f, 0.0f,
		 0.5, -0.5, -0.5f,		1.0f, 0.0f, 0.0f,		0.0f, 0.0f,

		 //CARA IZQUIERDA
		 -0.5f, -0.5f, 0.5f,	-1.0f, 0.0f, 0.0f,		1.0f, 1.0f,
		 -0.5f, -0.5f, -0.5f,	-1.0f, 0.0f, 0.0f,		1.0f, 0.0f,
		 -0.5f, 0.5f, -0.5f,	-1.0f, 0.0f, 0.0f,		0.0f, 0.0f,

		 -0.5f, 0.5f, -0.5f,	-1.0f, 0.0f, 0.0f,		0.0f, 0.0f,
		 -0.5f, 0.5f, 0.5f,		-1.0f, 0.0f, 0.0f,		0.0f, 1.0f,
		 -0.5f, -0.5f, 0.5f,	-1.0f, 0.0f, 0.0f,		1.0f, 1.0f,

		  //CARA INFERIOR
		  -0.5f,-0.5f,-0.5f,	0.0f, 0.0f, -1.0f,		1.0f, 0.0f,
		   0.5f,-0.5f,-0.5f,	0.0f, 0.0f, -1.0f,		0.0f, 0.0f,
		   0.5f, 0.5f,-0.5f,	0.0f, 0.0f, -1.0f,		0.0f, 1.0f,

		   0.5f, 0.5f, -0.5f,	0.0f, 0.0f, -1.0f,		0.0f, 1.0f,
		  -0.5f,0.5f,-0.5f,		0.0f, 0.0f, -1.0f,		1.0f, 1.0f,
		  -0.5f,-0.5f,-0.5f,	0.0f, 0.0f, -1.0f,		1.0f, 0.0f,

		  //Falta la cara superior
	};


	glGenVertexArrays(1, &VAOCuboDestapado);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);
	
	glBindVertexArray(VAOCuboDestapado);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);


	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	//position Color
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	//texture
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
	glEnableVertexAttribArray(2);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
	glDeleteBuffers(1, &VBO);
	glDeleteBuffers(1, &EBO);

	return(VAOCubo);


}

void openGlInit() {
	//Habilito aqui el depth en vez de arriba para los usuarios de linux y mac mejor arriba
	//Incializaciones varias
	glClearDepth(1.0f); //Valor z-buffer
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);  // valor limpieza buffer color
	glEnable(GL_DEPTH_TEST); // z-buffer
	//glEnable(GL_CULL_FACE); //ocultacion caras back
	glEnable(GL_TEXTURE_2D);
	glCullFace(GL_BACK);

}

glm::vec3 nuevaPos(glm::mat4 transfm) {

	return glm::vec3(transfm * glm::vec4(0.0f, 0.0f, 0.0f, 1.0f));
}

void cargarTextura(const char* nombreTextura, unsigned int* textura, int formato) {

	// Cargamos y creamos la textura
	glGenTextures(1, textura);
	// Ahora todas las operaciones GL_TEXTURE_2D tienen efecto sobre este objeto texture
	glBindTexture(GL_TEXTURE_2D, *textura);
	// Establecemos los parámetros de wrapping
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	// Establecemos los parametros de filtering
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	// Cargamos la imagen, creamos la textura y generamos mipmaps
	int width, height, nrChannels;
	unsigned char* data = stbi_load(nombreTextura, &width, &height, &nrChannels, 0);
	if (data) {
		glTexImage2D(GL_TEXTURE_2D, 0, formato, width, height, 0, formato, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else {
		std::cout << "Error al cargar la textura" << std::endl;
	}
	stbi_image_free(data);

}


void texturas() {
	//texturaSuelo = Carga_Texturas("Texturas/hierba.jpg");
	cargarTextura("Texturas/hierba.jpg", &texturaSuelo, GL_RGB);
	//texturaObra = Carga_Texturas("Texturas/obra.jpg"); todo
	cargarTextura("Texturas/bernabeu.jpg", &texturaEstadio, GL_RGB);


	//base.textura = base1.textura = base2.textura = Carga_Texturas("Texturas/brazos.jpg");
	cargarTextura("Texturas/brazos.jpg", &base.textura, GL_RGB);
	cargarTextura("Texturas/brazos.jpg", &base1.textura, GL_RGB);
	cargarTextura("Texturas/brazos.jpg", &base2.textura, GL_RGB);

	//baseA1.textura = baseA2.textura = foco.textura = Carga_Texturas("Texturas/metal.jpg");
	cargarTextura("Texturas/metal.jpg", &baseA1.textura, GL_RGB);
	cargarTextura("Texturas/metal.jpg", &baseA2.textura, GL_RGB);
	cargarTextura("Texturas/metal.jpg", &foco.textura, GL_RGB);

	//texturaActual = texturaPiscina[0];
}


void texturasPiscina() {
	cargarTextura("Texturas/caust00.png", &texturaPiscina[0], GL_RGBA);
	cargarTextura("Texturas/caust01.png", &texturaPiscina[1], GL_RGBA);
	cargarTextura("Texturas/caust02.png", &texturaPiscina[2], GL_RGBA);
	cargarTextura("Texturas/caust03.png", &texturaPiscina[3], GL_RGBA);
	cargarTextura("Texturas/caust04.png", &texturaPiscina[4], GL_RGBA);
	cargarTextura("Texturas/caust05.png", &texturaPiscina[5], GL_RGBA);
	cargarTextura("Texturas/caust06.png", &texturaPiscina[6], GL_RGBA);
	cargarTextura("Texturas/caust07.png", &texturaPiscina[7], GL_RGBA);
	cargarTextura("Texturas/caust08.png", &texturaPiscina[8], GL_RGBA);
	cargarTextura("Texturas/caust09.png", &texturaPiscina[9], GL_RGBA);
	cargarTextura("Texturas/caust10.png", &texturaPiscina[10], GL_RGBA);
	cargarTextura("Texturas/caust11.png", &texturaPiscina[11], GL_RGBA);
	cargarTextura("Texturas/caust12.png", &texturaPiscina[12], GL_RGBA);
	cargarTextura("Texturas/caust13.png", &texturaPiscina[13], GL_RGBA);
	cargarTextura("Texturas/caust14.png", &texturaPiscina[14], GL_RGBA);
	cargarTextura("Texturas/caust15.png", &texturaPiscina[15], GL_RGBA);
}


void texShader() {
	glUniform1i(glGetUniformLocation(shaderProgram, "Texturas[0]"), 0);
	glUniform1i(glGetUniformLocation(shaderProgram, "Texturas[1]"), 1);
	glUniform1i(glGetUniformLocation(shaderProgram, "Texturas[2]"), 2);
	glUniform1i(glGetUniformLocation(shaderProgram, "Texturas[3]"), 3);
	glUniform1i(glGetUniformLocation(shaderProgram, "Texturas[4]"), 4);
	glUniform1i(glGetUniformLocation(shaderProgram, "Texturas[5]"), 5);
	glUniform1i(glGetUniformLocation(shaderProgram, "Texturas[6]"), 6);
	glUniform1i(glGetUniformLocation(shaderProgram, "Texturas[7]"), 7);
	glUniform1i(glGetUniformLocation(shaderProgram, "Texturas[8]"), 8);
	glUniform1i(glGetUniformLocation(shaderProgram, "Texturas[9]"), 9);
	glUniform1i(glGetUniformLocation(shaderProgram, "Texturas[10]"), 10);
	glUniform1i(glGetUniformLocation(shaderProgram, "Texturas[11]"), 11);
	glUniform1i(glGetUniformLocation(shaderProgram, "Texturas[12]"), 12);
	glUniform1i(glGetUniformLocation(shaderProgram, "Texturas[13]"), 13);
	glUniform1i(glGetUniformLocation(shaderProgram, "Texturas[14]"), 14);
	glUniform1i(glGetUniformLocation(shaderProgram, "Texturas[15]"), 15);
	glUniform1i(glGetUniformLocation(shaderProgram, "Texturas[16]"), 16);
}

void activarTexturasPiscina() {
	switch (instante) {
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
//void ajustarAnimacion();
void ajustarAnimacion() {
	contador++;
	if (contador == 60) {
		if (instante == 10) {
			instante = 12; //Nos saltamos el 11 porque estropea la animacion
		}
		else if (instante < 15) {
			instante++;
		}
		else {
			instante = 0;
		}
		contador = 0;
	}
}

//Función que dibuja la piscina
void dibujaPiscina(int transformLoc) {
	activarTexturasPiscina();

	glBindTexture(GL_TEXTURE_2D, texturaPiscina[instante]);
	glUniform1i(glGetUniformLocation(shaderProgram, "instante"), instante);

	// Ajustamos la animacion para que sea mas fluida
	ajustarAnimacion();


	glUniform1i(glGetUniformLocation(shaderProgram, "piscina"), 1);
	glm::mat4 transform1;
	transform1 = glm::mat4();
	transform1 = glm::translate(transform1, glm::vec3(-1.0f, 0.0f, -0.44f));
	transform1 = glm::scale(transform1, glm::vec3(1.0f, 1.0f, 1.0f));
	glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(transform1));

	glBindVertexArray(VAOCuadrado);
	glDrawArrays(GL_TRIANGLES, 0, 6);
}

//Función que dibuja el suelo
void dibujasuelo(int transformLoc) {
	//Color suelo
	unsigned int colorLocSuelo = glGetUniformLocation(shaderProgram, "objectColor");
	glUniform3f(colorLocSuelo, 0.5, 0.5, 0.5);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texturaSuelo);

	float i, j;
	float escalasuelo = 10;

	for (i = -2; i <= 2; i += (1 / escalasuelo)) {
		for (j = -2; j <= 2; j += (1 / escalasuelo)) {
			transform = glm::mat4();
			transform = glm::rotate(transform, (float)(angulo * ARADIANES), glm::vec3(1.0f, 0.0f, 0.0f));
			transform = glm::translate(transform, glm::vec3(i, j, 0.0f));
			transform = glm::scale(transform, glm::vec3((1 / escalasuelo), (1 / escalasuelo), (1 / escalasuelo)));
			glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(transform));
			glBindVertexArray(VAOCuadrado);
			glDrawArrays(GL_TRIANGLES, 0, 6);
		}
	}
}

//Dibujamos la base de la grua
void dibujabase(int transformLoc, int colorLoBase) {
	//glUniform3f(colorLoBase, base.colx, base.coly, base.colz);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, base.textura);

	transform = glm::mat4();
	transform = glm::rotate(transform, (float)(angulo * ARADIANES), glm::vec3(1.0f, 0.0f, 0.0f));
	transform = glm::translate(transform, glm::vec3(base.px, base.py, base.pz));
	transform = glm::rotate(transform, (float)(base.angulo_trans * ARADIANES), glm::vec3(0.0f, 0.0f, 1.0f));
	transformtemp = transform;
	transform = glm::scale(transform, glm::vec3(base.sx, base.sy, base.sz));
	glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(transform));
	glBindVertexArray(base.listarender);
	glDrawArrays(GL_TRIANGLES, 0, 36);
}

//Dibujamos las articulaciones de la grua
void dibujaArtBra(objeto parte, int transformLoc, int colorLoBase) {

	//glUniform3f(colorLoBase, parte.colx, parte.coly, parte.colz);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, parte.textura);

	transform = glm::mat4();
	transform = transformtemp;
	transform = glm::translate(transform, glm::vec3(parte.px, parte.py, parte.pz));
	if (parte.articulacion == 1) {
		transform = glm::rotate(transform, (float)(parte.angulo_trans * ARADIANES), glm::vec3(1.0f, 0.0f, 0.0f));
		transform = glm::rotate(transform, (float)(parte.angulo_trans_2 * ARADIANES), glm::vec3(0.0f, 1.0f, 0.0f));
	}
	transformtemp = transform;
	transform = glm::scale(transform, glm::vec3(parte.sx, parte.sy, parte.sz));
	glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(transform));
	glBindVertexArray(parte.listarender);
	if (parte.articulacion == 1) {
		glDrawArrays(GL_TRIANGLES, 0, 1080);
	}
	else {
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

	//'Z,X,C'->Cambiar vista, 'L,K'-> mover la camara, 'T,F,G,H'-> mover brazo arriba, 'A,D,S,W'-> mover brazo abajo
	// 
	//Creo la ventana													
	GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "Grúa Riazor", NULL, NULL);
	if (window == NULL) {
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

	// glad: load all OpenGL function pointers
	// ---------------------------------------
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}

	glfwSetKeyCallback(window, keyCallback);
	openGlInit();

	//generarShader();
	shaderProgram = setShaders("Shaders/shader.vert", "Shaders/shader.frag");

	glUniform1i(glGetUniformLocation(shaderProgram, "textura1"), 0);
	//glUniform1i(glGetUniformLocation(shaderProgram, "textura2"), 1);

	dibujaCuadrado();
	dibujaCubo();
	dibujaCuboDestapado();
	dibujaEsfera();

	base.listarender = base1.listarender = base2.listarender = fondo = VAOCubo;
	baseA1.listarender = baseA2.listarender = VAOEsfera;
	fondo = VAOCuboDestapado;

	//inicializarTexturas();

	texturas();

	texturasPiscina();

	glUseProgram(shaderProgram);

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
		processInput(window);
		// render
		// ------
		glClearColor(0.0f, 0.5f, 1.0f, 1.0f); //Borro el Buffer the la ventana
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		//Diferentes tipos de camara
		if (camara == 1) {
			myCamara();
		}
		if (camara == 2) {
			terceraPersona(base.px, base.py, base.pz, base.angulo_trans);
		}
		if (camara == 3) {
			primeraPersona(base.px, base.py, base.pz, base.angulo_trans);
		}

		//Dibujamos en GL_FILL
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

		//Transformaciones
		unsigned int transformLoc = glGetUniformLocation(shaderProgram, "transform");
		//Luz
		unsigned int lightColorLoc = glGetUniformLocation(shaderProgram, "lightColor");
		glUniform3f(lightColorLoc, 1.0f, 1.0f, 1.0f);


		//Dibujamos el suelo
		dibujasuelo(transformLoc);

		//Movimiento de la base con aceleración
		base.px += velocidad * cos(base.angulo_trans * ARADIANES);
		base.py += velocidad * sin(base.angulo_trans * ARADIANES);

		//Color para la base
		unsigned int colorLoGrua = glGetUniformLocation(shaderProgram, "objectColor");

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
		glBindTexture(GL_TEXTURE_2D, texturaPiscina[instante]);
		glDisable(GL_TEXTURE_2D);
		glEnable(GL_TEXTURE_2D);
		dibujaPiscina(transformLoc);

		//Desactivamos piscina
		glUniform1i(glGetUniformLocation(shaderProgram, "piscina"), 0);

		unsigned int lightPosLoc = glGetUniformLocation(shaderProgram, "lightPos");
		glm::vec3 pos_linterna = nuevaPos(transform);
		glUniform3f(lightPosLoc, pos_linterna.x, pos_linterna.y, pos_linterna.z);

		float spotCutoffLoc = glGetUniformLocation(shaderProgram, "spotCutoff");
		glUniform1f(spotCutoffLoc, grados);

		// glfw: swap 
		// -------------------------------------------------------------------------------
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glDeleteVertexArrays(1, &VAO);
	glfwTerminate();
	return 0;
}

void processInput(GLFWwindow* window) {
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
	// make sure the viewport matches the new window dimensions; note that width and 
	// height will be significantly larger than specified on retina displays.
	SCR_WIDTH = width;
	SCR_HEIGHT = height;
	//glViewport(0, 0, width, height);
}

void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods) {
	std::cout << key << std::endl;

	//Primera arti
	if (key == 65 && baseA1.angulo_trans >= -85) { //A
		baseA1.angulo_trans--;
	}
	if (key == 83 && baseA1.angulo_trans_2 >= -90) { //S
		baseA1.angulo_trans_2--;
	}
	if (key == 87 && baseA1.angulo_trans_2 <= 90) { //W
		baseA1.angulo_trans_2++;
	}
	if (key == 68 && baseA1.angulo_trans <= 85) { //D
		baseA1.angulo_trans++;
	}
	//Segunda arti
	if (key == 84) { //T
		baseA2.angulo_trans_2++;
	}
	if (key == 71) { //G
		baseA2.angulo_trans_2--;
	}
	if (key == 70) { //F
		baseA2.angulo_trans--;
	}
	if (key == 72) { //H
		baseA2.angulo_trans++;
	}
	//Plano
	if (key == 75) { //K
		angulo++;
	}
	if (key == 76) { //L
		angulo--;
	}

	//Movimiento de la base (<^>)
	if (key == 262) { //HACIA LA DERECHA
		base.angulo_trans--;
	}
	if (key == 263) { //HACIA LA IZQUIERDA
		base.angulo_trans++;
	}
	if (key == 265) { //HACIA LA DERECHA
		velocidad += 0.001;
	}
	if (key == 264) { //HACIA LA IZQUIERDA
		velocidad -= 0.001;
	}

	//Elegir camara
	//Cámara externa
	if (key == 90) { //Z
		camara = 1;
	}
	//Tercera persona
	if (key == 88) { //X
		camara = 2;
	}
	//Primera persona
	if (key == 67) { //C
		camara = 3;
	}
}