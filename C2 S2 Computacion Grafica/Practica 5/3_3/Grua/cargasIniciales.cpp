#include "comun.h"

#include <iostream>

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

// Texturas
unsigned int texturaPiscina[16] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
unsigned int texturaSuelo = 0;
unsigned int texturaEstadio = 0;


// Animacion piscia
int piscina_instante = 0;
int piscina_contador = 0;

// Elementos de la grúa
ElementoGrua base   /**/ = { 0, 0, 0.15f, 0, 0, .30f, .20f, .20f, 0, 1.0f, 1.0f, 0.0f, 0, 0, 1 };
ElementoGrua baseA1 /**/ = { 0, 0, 0.10f, 0, 0, .07f, .07f, .07f, 0, 0.0f, 1.0f, 1.0f, 1, 0, 0 };
ElementoGrua base1  /**/ = { 0, 0, 0.10f, 0, 0, .05f, .05f, .30f, 0, 1.0f, 1.0f, 0.0f, 0, 0, 0 };
ElementoGrua baseA2 /**/ = { 0, 0, 0.15f, 0, 0, .05f, .05f, .05f, 0, 0.0f, 1.0f, 1.0f, 1, 0, 0 };
ElementoGrua base2  /**/ = { 0, 0, 0.11f, 0, 0, .05f, .05f, .30f, 0, 1.0f, 1.0f, 0.0f, 0, 0, 0 };
ElementoGrua foco   /**/ = { 0, 0, 0.25f, 0, 0, .05f, .05f, .05f, 0, 0.0f, 1.0f, 0.0f, 0, 0, 0 };


// Settings
unsigned int SCR_WIDTH = 720;
unsigned int SCR_HEIGHT = 720;

// My Shader
// My Shader
GLuint myShaderProgram;

//Angulo plano
float anguloPlano = 0.0;


//VAOs
unsigned int VAO;
unsigned int VAOEsfera;
unsigned int VAOCubo;
unsigned int VAOCuboDestapado;
unsigned int VAOCuadrado;

//Variables para el control de la cámara
int camaraSeleccionada = 1;

//Variables para el moviminto de la grúa
float velocidadGrua = 0.0;
// float anguloGiroGrua = 0.0;
float gradosSpotCutoff = 25.0;

// --

void myOpenGlInit() {
    //Habilito aqui el depth en vez de arriba para los usuarios de linux y mac mejor arriba
    //Incializaciones varias
    glClearDepth(1.0f); //Valor z-buffer
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);  // valor limpieza buffer color
    glEnable(GL_DEPTH_TEST); // z-buffer
    //glEnable(GL_CULL_FACE); //ocultacion caras back
    glEnable(GL_TEXTURE_2D);
    glCullFace(GL_BACK);

}

void cargaUnaTextura(const char* nombreTextura, unsigned int* textura, int formato) {

    // Cargamos y creamos la textura
    glGenTextures(1, textura);
    // Ahora todas las operaciones GL_TEXTURE_2D tienen efecto sobre este ElementoGrua texture
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


void cargaTexturas() {
    //texturaSuelo = Carga_Texturas("Texturas/hierba.jpg");
    cargaUnaTextura("Texturas/hierba.jpg", &texturaSuelo, GL_RGB);
    //texturaObra = Carga_Texturas("Texturas/obra.jpg"); todo
    cargaUnaTextura("Texturas/bernabeu.jpg", &texturaEstadio, GL_RGB);


    //base.textura = base1.textura = base2.textura = Carga_Texturas("Texturas/brazos.jpg");
    cargaUnaTextura("Texturas/brazos.jpg", &base.textura, GL_RGB);
    cargaUnaTextura("Texturas/brazos.jpg", &base1.textura, GL_RGB);
    cargaUnaTextura("Texturas/brazos.jpg", &base2.textura, GL_RGB);

    //baseA1.textura = baseA2.textura = foco.textura = Carga_Texturas("Texturas/metal.jpg");
    cargaUnaTextura("Texturas/metal.jpg", &baseA1.textura, GL_RGB);
    cargaUnaTextura("Texturas/metal.jpg", &baseA2.textura, GL_RGB);
    cargaUnaTextura("Texturas/metal.jpg", &foco.textura, GL_RGB);

    //texturaActual = texturaPiscina[0];
}


void cargaTexturasPiscina() {
    cargaUnaTextura("Texturas/caust00.png", &texturaPiscina[0], GL_RGBA);
    cargaUnaTextura("Texturas/caust01.png", &texturaPiscina[1], GL_RGBA);
    cargaUnaTextura("Texturas/caust02.png", &texturaPiscina[2], GL_RGBA);
    cargaUnaTextura("Texturas/caust03.png", &texturaPiscina[3], GL_RGBA);
    cargaUnaTextura("Texturas/caust04.png", &texturaPiscina[4], GL_RGBA);
    cargaUnaTextura("Texturas/caust05.png", &texturaPiscina[5], GL_RGBA);
    cargaUnaTextura("Texturas/caust06.png", &texturaPiscina[6], GL_RGBA);
    cargaUnaTextura("Texturas/caust07.png", &texturaPiscina[7], GL_RGBA);
    cargaUnaTextura("Texturas/caust08.png", &texturaPiscina[8], GL_RGBA);
    cargaUnaTextura("Texturas/caust09.png", &texturaPiscina[9], GL_RGBA);
    cargaUnaTextura("Texturas/caust10.png", &texturaPiscina[10], GL_RGBA);
    cargaUnaTextura("Texturas/caust11.png", &texturaPiscina[11], GL_RGBA);
    cargaUnaTextura("Texturas/caust12.png", &texturaPiscina[12], GL_RGBA);
    cargaUnaTextura("Texturas/caust13.png", &texturaPiscina[13], GL_RGBA);
    cargaUnaTextura("Texturas/caust14.png", &texturaPiscina[14], GL_RGBA);
    cargaUnaTextura("Texturas/caust15.png", &texturaPiscina[15], GL_RGBA);
}
