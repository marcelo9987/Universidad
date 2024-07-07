

#include <glad.h>
#include <glfw3.h>
#include <stdio.h>
#include <iostream>
#include <lecturaShader.h>


#pragma comment(lib, "glfw3.lib")


void processInput(GLFWwindow *window);

// settings
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 800;


extern GLuint setShaders(const char *nVertx, const char *nFrag);
GLuint shaderProgram;

// unsigned int VBO, VAO, EBO;
unsigned int VAO;

unsigned int VAOTriangulo;
unsigned int VAOTriangulo2;
unsigned int VAOTriangulo3;

void dibujaEjes() {
	unsigned int VBO, EBO;
	
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
	// bind the Vertex Array Object 
	glBindVertexArray(VAO);

	// bind the Vertex buffers
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	// position de los attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	// position del color Color
	
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	
	// ya no no necesito el VAo y hago el un unbind
	glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindVertexArray(0);
	//Borro los buffers
	glDeleteBuffers(1, &VBO);
	glDeleteBuffers(1, &EBO);

}

void dibujaTriangulo1() {
	unsigned int VBO, EBO;
	// set up vertex data and buffer 

	float vertices[] = {
		//Vertices          //Colores
		 0.0f, 0.00f,  0.0f,     1.0f, 1.0f, 1.0f,  // origen
		 1.0f, 0.00f, -1.5f,     1.0f, 0.0f, 0.0f, //1
		-0.5f, 0.86f, -3.0f,     0.0f, 1.0f, 0.0f, //2
		
		
	};
	unsigned int indices[] = {  // empieza desde cero
		0, 1, 2,
		
	};

	glGenVertexArrays(1, &VAOTriangulo);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);
	// bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
	glBindVertexArray(VAOTriangulo);

		// bind the Vertex buffers
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
	
	// position de los attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	// position del color Color
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);


	// ya no no necesito el VAo y hago el un unbind
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
	//Borro los buffers
	glDeleteBuffers(1, &VBO);
	glDeleteBuffers(1, &EBO);

}

void dibujaTriangulo2() {
	unsigned int VBO, EBO;
	// set up vertex data and buffer 

	float vertices[] = {
		//Vertices          //Colores
		-0.5f,  0.86f, 0.0f,     0.0f, 1.0f, 0.0f, //Origen ^
		-0.5f, -0.86f, 0.0f,     0.0f, 0.0f, 1.0f, //1 \/
		 0.0f,  0.00f, 0.0f,     1.0f, 1.0f, 1.0f,  // 2 -->


	};
	unsigned int indices[] = {  // empieza desde cero
		0, 1, 2,

	};

	glGenVertexArrays(1, &VAOTriangulo2);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);
	// bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
	glBindVertexArray(VAOTriangulo2);

	// bind the Vertex buffers
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	// position de los attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	// position del color Color
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);


	// ya no no necesito el VAo y hago el un unbind
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
	//Borro los buffers
	glDeleteBuffers(1, &VBO);
	glDeleteBuffers(1, &EBO);

}

void dibujaTriangulo3() {
	unsigned int VBO, EBO;
	// set up vertex data and buffer 

	float vertices[] = {
		//Vertices          //Colores
		 0.00f,  0.00f, 0.0f,	  1.0f, 1.0f, 1.0f, // 2 -->
		-0.50f, -0.86f, 1.5f,     0.0f, 0.0f, 1.0f, //1 \/
		 1.00f,  0.00f, 3.0f,	  1.0f, 0.0f, 0.0f, //1
		
		


	};
	unsigned int indices[] = {  // empieza desde cero
		0, 1, 2,

	};

	glGenVertexArrays(1, &VAOTriangulo3);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);
	// bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
	glBindVertexArray(VAOTriangulo3);

	// bind the Vertex buffers
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	// position de los attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	// position del color Color
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);


	// ya no no necesito el VAo y hago el un unbind
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
	//Borro los buffers
	glDeleteBuffers(1, &VBO);
	glDeleteBuffers(1, &EBO);

}

void openGlInit() {
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


	// glad
	// ---------------------------------------
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}


	
	//generarShader();
	shaderProgram = setShaders("shader.vert", "shader.frag");
	
	//dibujaEjes();
	dibujaTriangulo1();
	dibujaTriangulo2();
	dibujaTriangulo3();
	openGlInit();


	// uncomment this call to draw in wireframe polygons.
	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	// Lazo de la ventana mientras no la cierre
	// -----------
	while (!glfwWindowShouldClose(window))
	{
		// input
		// -----
		processInput(window);

		// render
		// ------
		glClear(GL_COLOR_BUFFER_BIT);
		glClear(GL_DEPTH_BUFFER_BIT);

		// dibujo los ejes
	
		glUseProgram(shaderProgram);
		//Dibujo tiangulos
		glBindVertexArray(VAOTriangulo);
		glDrawElements(GL_TRIANGLES, 3 , GL_UNSIGNED_INT, 0);

		glBindVertexArray(VAOTriangulo2);
		glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, 0);
		
		glBindVertexArray(VAOTriangulo3);
		glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, 0);

		//Dibujo ejes
		glBindVertexArray(VAO); // seeing as we only have a single VAO there's no need to bind it every time, but we'll do so to keep things a bit more organized
		glDrawElements(GL_LINES, 8, GL_UNSIGNED_INT, 0);
				
		glBindVertexArray(0); // no need to unbind it every time 
		 		
		// glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
		// -------------------------------------------------------------------------------
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	// optional: de-allocate all resources once they've outlived their purpose:

	glDeleteVertexArrays(1, &VAO);
	

	// glfw: terminate, clearing all 
	
	glfwTerminate();
	return 0;
}

// input

void processInput(GLFWwindow *window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
}

