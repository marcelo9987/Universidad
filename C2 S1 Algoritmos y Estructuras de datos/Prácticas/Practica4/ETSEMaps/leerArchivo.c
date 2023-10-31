#include "ETSEMaps.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <float.h>
#include <math.h>
#include <ctype.h>



int
leerArchivo(FILE *archivoLectura, grafo *G)
{
    //Empieza la odisea
    //compruebo que el archivo existe
    if (archivoLectura == NULL)
    {
        printf("Error al abrir el archivo\n");
        return -1;
    }


    //Leo el archivo
    // Según he diseñado el formato (Aun puede ser susceptible a cambios) lo primero que se leen son los vertices (puntos)
    // y luego las aristas (conexiones entre puntos)
    // Los comentarios (?) se ignoran
    // Las líneas en blanco se ignoran
    // Vamos a ello

    printf("Leyendo archivo...\n");

    char *linea = NULL;
    size_t len = 0; // va a ser ignorado por getline, que va a reservar la memoria que necesite
    ssize_t read;
    bool verticesLeidos = false;

    while ((read = getline(&linea, &len, archivoLectura)) != -1)
    {
        int posicionLecturaActual = 0;
        // voy a inspeccionar la linea para buscar espacios en blanco
        while (posicionLecturaActual< read && linea[posicionLecturaActual]==32)
        {
            printf("Espacio en blanco  ");
            posicionLecturaActual++;
        }
        printf("\n");

        if(linea[posicionLecturaActual] !='?' && linea[posicionLecturaActual]!='\n' && linea[posicionLecturaActual]!='\r' && linea[posicionLecturaActual]!='$' && verticesLeidos==false)
        {
            printf("[ERROR] En el formato del archivo :: Carácter inesperado:%c\n", linea[posicionLecturaActual]);
            printf("\t->Linea: %s\n", linea);
            printf("\t->Posición de lectura actual: %d\n", posicionLecturaActual);

            exit(-1);
        }

//        printf("Retrieved line of length %zu:\n", read);
        if (linea[posicionLecturaActual] == '?')
        {
            printf("[DEBUG] Comentario\n");
            continue;
        }
        if (linea[posicionLecturaActual] == '\n' || linea[posicionLecturaActual] == '\r')
        {
            printf("[DEBUG] Linea en blanco\n");
            continue;
        }
        printf("[DEBUG] Aristas (sin procesar): %s", linea);

        // cuando me encuentre con '$' significa que empiezan las aristas
        if (linea[posicionLecturaActual] == '$')
        {
            printf("[DEBUG] Empiezan las aristas\n");
            char *cadena;
            cadena = strdup(linea);
            char *token;
            while ((token = strtok(cadena, "$")) != NULL)
            {
                tipovertice vertice;
                printf("[DEBUG] Ciudad: %s\n", token);
                strcpy(vertice.nombre, token);
                vertice.nombre[strcspn(vertice.nombre, "\r\n")] = 0;
                insertar_vertice(G, vertice);

                cadena = NULL;
            }

            verticesLeidos = true;
        }

        if (verticesLeidos && linea[posicionLecturaActual] != '$')
        {
            if (linea[posicionLecturaActual] == '\n' || linea[posicionLecturaActual] == '\r')
            {
                printf("[DEBUG] Linea en blanco\n");
                continue;
            }
            printf("\n[DEBUG] ARISTA!!\n");

            // dada la complejidad de la lectura de aristas, lo voy a hacer a mano, sin usar strtok
            // el formato es: ciudad<distancia_carretera(opcional)|distancia_autopista(opcional)>ciudad 2
            // o bien: ciudad<|distancia_autopista(opcional)>ciudad 2 --> esto es una autopista
            // o bien: ciudad<distancia_carretera(opcional)>ciudad 2  --> esto es una carretera


            char *ciudad2 = NULL;


            int desplazamiento = posicionLecturaActual;
            int tempDesplazamiento = 0;
            tipovertice vertice1, vertice2;
            bool hayCarretera = false, hayAutopista = false;

            // FASE 2.1: leer ciudad1
            char *ciudad1 = NULL;
            sscanf((linea+posicionLecturaActual), "%m[^<]%n", &ciudad1, &tempDesplazamiento);
            desplazamiento += tempDesplazamiento;
            printf("[DEBUG] Ciudad 1: %s\n", ciudad1);

            printf("[DEBUG] Desplazamiento: %d\n", desplazamiento);


            // FASE 2.2: leer distancia_carretera
            float distancia_carretera = 0;

            // Si sabemos que ya ha terminado de leer el nombre y que hay distancia_carretera (es decir, no hay solo autopista):
            if (linea[desplazamiento] == '<' && linea[desplazamiento + 1] != '|')
            {

                printf("[DEBUG] Hay distancia_carretera\n");
                printf("[DEBUG] cadena en desplazamiento: %c\n", linea[desplazamiento + 1]);

                int parte_entera = 0;
                int parte_decimal = 0;
                int tam_entero = 0;
                int desplazamiento_anhadido = 0;
                //aquí parece que se complica por el bodrio de los flotantes... voy a coger las dos partes como enteros y luego las divido
                // menos mal que sscanf permite hacer un poco de magia negra y me dice la distancia que ha leído.
                sscanf(linea + desplazamiento + 1, "%d%n.%d%n", &parte_entera,&tam_entero, &parte_decimal, &desplazamiento_anhadido);

                printf("[DEBUG] Total leido: %d\n", desplazamiento_anhadido-1);
                printf("[DEBUG] Total entero: %d\n", tam_entero);
                printf("[DEBUG] Parte entera: %d\n", parte_entera);
                printf("[DEBUG] Parte decimal: %d\n", parte_decimal);
                distancia_carretera = (float)parte_entera + ((parte_decimal!=0) ? (parte_decimal / (pow(10, desplazamiento_anhadido-tam_entero-1))) : 0);

                // En el caso de que en el archivo de entrada haya un número sin decimales, sscanf no me devuelve el número de caracteres leídos
                // Esto conllevaría que el desplazamiento no se actualiza y se queda en el '<' y no avanza
                // Por lo que tengo que buscar el '>' a mano
                if(desplazamiento_anhadido==0)
                {
                    while(linea[desplazamiento+1+desplazamiento_anhadido]!='|' && linea[desplazamiento+1+desplazamiento_anhadido]!='>')
                    {
                        desplazamiento_anhadido++;
                    }
                }
                printf("[DEBUG] Desplazamiento anhadido: %d\n", desplazamiento_anhadido);
                desplazamiento += desplazamiento_anhadido+1;

//                sscanf(linea + desplazamiento + 1, "%3f%n", &distancia_carretera, &desplazamiento_anhadido);
//                desplazamiento += desplazamiento_anhadido;
                printf("[DEBUG] Distancia carretera: %f\n", distancia_carretera);

                hayCarretera = true;

            } else
            {
                printf("[DEBUG] No hay distancia_carretera\n");
                distancia_carretera = 0;
            }


            // FASE 2.3: leer distancia_autopista

            float distancia_autopista = 0;
            printf("[DEBUG] desplazamiento: %d\n", desplazamiento);
            printf("[DEBUG] linea[desplazamiento]: %c\n", linea[desplazamiento]);

            if (linea[desplazamiento] == '|')
            {
                printf("[DEBUG] Hay distancia_autopista\n");
                //Aquí al ser la ultima parte, no me veo obligado a hacer magia negra aritmética, pues no tengo que mirar si hay continuaciones
                sscanf(linea + desplazamiento + 1, "%f", &distancia_autopista);
                printf("[DEBUG] Distancia autopista: %.1f\n", distancia_autopista);

                //busco el punto en el que se acaba la distancia_autopista si float ha hecho de las suyas
                while(linea[desplazamiento]!='>')
                {
                    desplazamiento++;
                }
                hayAutopista = true;
            } else
            {
                printf("[DEBUG] No hay distancia_autopista\n");
                distancia_autopista = 0;
            }


            // FASE 2.4: leer ciudad2
            // Aquí tengo que tener en cuenta que puede haber un salto de línea o un retorno de carro
            sscanf(linea + desplazamiento + 1, "%m[^>]", &ciudad2);
            printf("[DEBUG] Ciudad 2: %s\n\n ------------------- \n", ciudad2);

            //cambio los \r y \n por \0s para que no me de problemas al comparar e imprimir
            ciudad1[strcspn(ciudad1, "\r\n")] = 0;
            ciudad2[strcspn(ciudad2, "\r\n")] = 0;

//            sleep(2);
//            printf("Ciudad 2: %s\n", ciudad2);
//            printf("Distancia carretera: %d\n", distancia_carretera);
//            printf("Distancia autopista: %d\n", distancia_autopista);




            strcpy(vertice1.nombre, ciudad1);


            strcpy(vertice2.nombre, ciudad2);

            if(hayCarretera)
            {
                printf("[DEBUG] conectando %s con %s a modo de carretera\n", vertice1.nombre, vertice2.nombre);
                crear_arco(G, posicion(*G, vertice1), posicion(*G, vertice2), distancia_carretera, 'C');
            }
            if(hayAutopista)
            {
                printf("[DEBUG] conectando %s con %s a modo de autopista\n", vertice1.nombre, vertice2.nombre);
                crear_arco(G, posicion(*G, vertice1), posicion(*G, vertice2), distancia_autopista, 'A');
            }

            free(ciudad1);
            free(ciudad2);
        }
//        sleep(2);


    }

    printf("[DEBUG] Fin de lectura de archivo\n");

    free(linea);
    fclose(archivoLectura);
    printf("\n\n");
    imprimir_grafo(*G);
    printf("\n\n");
    printf("\n\n");

    return 0;
}
