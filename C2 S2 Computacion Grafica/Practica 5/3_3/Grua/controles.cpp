#include "controles.h"

#include <iostream>

void myProcessInput(GLFWwindow *window) {
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}


void myKeyCallback(GLFWwindow *window, int key, int scancode, int action, int mods) {
    // std::cout << key << std::endl;

    //Primera arti
    if (key == 'A' && baseA1.angulo_trans >= -85) { //A
        baseA1.angulo_trans--;
    } else if (key == 'S' && baseA1.angulo_trans_2 >= -90) { //S
        baseA1.angulo_trans_2--;
    } else if (key == 'W' && baseA1.angulo_trans_2 <= 90) { //W
        baseA1.angulo_trans_2++;
    } else if (key == 'D' && baseA1.angulo_trans <= 85) { //D
        baseA1.angulo_trans++;
    }
        //Segunda arti
    else if (key == 'T') { //T
        baseA2.angulo_trans_2++;
    } else if (key == 'G') { //G
        baseA2.angulo_trans_2--;
    } else if (key == 'F') { //F
        baseA2.angulo_trans--;
    } else if (key == 'H') { //H
        baseA2.angulo_trans++;
    }
        //Plano
    else if (key == 'K') { //K
        anguloPlano++;
    } else if (key == 'L') { //L
        anguloPlano--;
    }
        //Movimiento de la base (<^>)
    else if (key == 262) { //HACIA LA DERECHA
        base.angulo_trans--;
    } else if (key == 263) { //HACIA LA IZQUIERDA
        base.angulo_trans++;
    } else if (key == 265) { //HACIA LA DERECHA
        velocidadGrua += 0.001f;
    } else if (key == 264) { //HACIA LA IZQUIERDA
        velocidadGrua -= 0.001f;
    }
        //Elegir camaraSeleccionada
    else if (key == 'Z') { //Z
        //Cámara externa
        camaraSeleccionada = 1;
    } else if (key == 'X') { //X
        //Tercera persona
        camaraSeleccionada = 2;
    } else if (key == 'C') { //C
        //Primera persona
        camaraSeleccionada = 3;
    }
}


void myFramebufferSizeCallback(GLFWwindow* window, int width, int height) {
    // make sure the viewport matches the new window dimensions; note that width and
    // height will be significantly larger than specified on retina displays.
    SCR_WIDTH = width;
    SCR_HEIGHT = height;
    //glViewport(0, 0, width, height);
}
