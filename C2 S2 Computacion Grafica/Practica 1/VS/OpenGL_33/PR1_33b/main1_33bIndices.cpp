#include <glad.h>
#include <glfw3.h>

#include <iostream>

GLuint setShaders(const char *nVertx, const char *nFrag);
void processInput(GLFWwindow *window);

// settings
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

int shaderProgram; //defino esta variable como globla por comodidad
unsigned int VAO,VBO,  EBO; // las uso globales por comodidad.



void medianteIndices(){

		//Configuro los vertices y los atributos que no hay
	// ------------------------------------------------------------------
	float vertices[] = {
		0.0f, 0.0f, 0.0f, // 0
		.5f, 0.0f, 0.0f, //x
		0.0f, .5f, 0.0f, // y
		0.0f, 0.0f, .5f // z  
	};
	unsigned int indices[] = {  // coloco los indices, empiezan en 0 y los vertices a usar.
		0, 1,
		0, 2,
		0, 3 
	};
	
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);
	// bind the Vertex Array Object Para saber sobre que arrary de vertices se trabaja. A continuacion los atributos.
	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO); //hago el bind buffer al vertexArray de trabajo
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW); //indico el formato

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO); //GL_ELEMENT_ARRAY_BUFFER indica que son los indices es otro buffer
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);


	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	
	
	glBindVertexArray(0); // nos hace un unbind the VAO hay que hacerlo siempre por si en otra funcion nos cargamos más inforamcion de vertices
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

// Funcion main.

int main()
{
	//Genero ventana
	// ------------------------------
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);



														 // Creo la ventana
														 // --------------------
	GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "LearnOpenGL", NULL, NULL);
	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);
	

	//Leo el gald
	// ---------------------------------------
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}
	
	shaderProgram = setShaders("ejes.vert", "ejes.frag");
	
	// Tengo dos funciones que me permite eleguir entre glVertexAttribPointer (para indices) o glDrawElements (el array de vertices)
	openGlInit();
	medianteIndices();
	

	
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE); //Dibujo lineas

	// Lazo principal
	// -----------
	while (!glfwWindowShouldClose(window))
	{
		// input
		// -----
		processInput(window);

		// render
		// ------
		//limpieza de los buffers
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		glClear(GL_DEPTH_BUFFER_BIT);

		
	
		glUseProgram(shaderProgram); // leemos el shader
		glBindVertexArray(VAO);		//hacemos un bind al array 
		//glDrawArrays(GL_LINES, 0, 6); //Para dibuhar con array
		glDrawElements(GL_LINES, 6, GL_UNSIGNED_INT, 0); // Utilianzo los indices.
		 glBindVertexArray(0); // no need to unbind it every time 

		// glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
		// -------------------------------------------------------------------------------
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	//Como se acabo vacio los buffers
	// ------------------------------------------------------------------------
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);

	// Termino todo.
	// ------------------------------------------------------------------
	glfwTerminate();
	return 0;
}

// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
// ---------------------------------------------------------------------------------------------------------
void processInput(GLFWwindow *window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
}

