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

//        printf("Retrieved line of length %zu:\n", read);
        if (linea[posicionLecturaActual] == '?')
        {
            printf("Comentario\n");
            continue;
        }
        if (linea[posicionLecturaActual] == '\n' || linea[posicionLecturaActual] == '\r')
        {
            printf("Linea en blanco\n");
            continue;
        }
        printf("%s", linea);

        // cuando me encuentre con '$' significa que empiezan las aristas
        if (linea[posicionLecturaActual] == '$')
        {
            printf("Empiezan las aristas\n");
            char *cadena;
            cadena = strdup(linea);
            char *token;
            while ((token = strtok(cadena, "$")) != NULL)
            {
                tipovertice vertice;
                printf("Ciudad: %s\n", token);
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
                printf("Linea en blanco\n");
                continue;
            }
            printf("\nARISTA!!\n");

            // dada la complejidad de la lectura de aristas, lo voy a hacer a mano, sin usar strtok
            // el formato es: ciudad<distancia_carretera(opcional)|distancia_autopista(opcional)>ciudad 2
            // o bien: ciudad<|distancia_autopista(opcional)>ciudad 2 --> esto es una autopista
            // o bien: ciudad<distancia_carretera(opcional)>ciudad 2  --> esto es una carretera
            //vamos al lío

            char *ciudad1 = NULL;
            char *ciudad2 = NULL;
            float distancia_carretera = FLT_MAX;
            float distancia_autopista = FLT_MAX;;
            int desplazamiento = posicionLecturaActual;
            int tempDesplazamiento = 0;
            tipovertice vertice1, vertice2;
            bool hayCarretera = false, hayAutopista = false;

            // FASE 2.1: leer ciudad1
            sscanf((linea+posicionLecturaActual), "%m[^<]%n", &ciudad1, &tempDesplazamiento);
            desplazamiento += tempDesplazamiento;
            printf("Ciudad 1: %s\n", ciudad1);

            printf("Desplazamiento: %d\n", desplazamiento);

            // FASE 2.2: leer distancia_carretera
            if (linea[desplazamiento] == '<' && linea[desplazamiento + 1] != '|')
            {
                int desplazamiento_anhadido = 0;
                printf("Hay distancia_carretera\n");
                printf("cadena en desplazamiento: %c\n", linea[desplazamiento + 1]);
                //aqui parece que se complica... voy a coger las dos partes como enteros y luego las divido
                int parte_entera = 0;
                int parte_decimal = 0;
                int tam_entero = 0;
                sscanf(linea + desplazamiento + 1, "%d%n.%d%n", &parte_entera,&tam_entero, &parte_decimal, &desplazamiento_anhadido);

                printf("Total leido: %d\n", desplazamiento_anhadido-1);
                printf(" Total entero: %d\n", tam_entero);
                printf("Parte entera: %d\n", parte_entera);
                printf("Parte decimal: %d\n", parte_decimal);
                distancia_carretera = (float)parte_entera + ((parte_decimal!=0) ? (parte_decimal / (pow(10, desplazamiento_anhadido-tam_entero-1))) : 0);

                if(desplazamiento_anhadido==0)
                {
                    while(linea[desplazamiento+1+desplazamiento_anhadido]!='|' && linea[desplazamiento+1+desplazamiento_anhadido]!='>')
                    {
                        desplazamiento_anhadido++;
                    }
                }
                printf("Desplazamiento anhadido: %d\n", desplazamiento_anhadido);
                desplazamiento += desplazamiento_anhadido+1;

//                sscanf(linea + desplazamiento + 1, "%3f%n", &distancia_carretera, &desplazamiento_anhadido);
//                desplazamiento += desplazamiento_anhadido;
                printf("Distancia carretera: %f\n", distancia_carretera);

                hayCarretera = true;

            } else
            {
                printf("No hay distancia_carretera\n");
                distancia_carretera = 0;
            }


            // FASE 2.3: leer distancia_autopista

            printf("desplazamiento: %d\n", desplazamiento);
            printf("linea[desplazamiento]: %c\n", linea[desplazamiento]);

            if (linea[desplazamiento] == '|')
            {
                printf("Hay distancia_autopista\n");
                sscanf(linea + desplazamiento + 1, "%f", &distancia_autopista);
                printf("Distancia autopista: %.1f\n", distancia_autopista);
//                desplazamiento++;
                //busco el punto en el que se acaba la distancia_autopista
                while(linea[desplazamiento]!='>')
                {
                    desplazamiento++;
                }
                hayAutopista = true;
            } else
            {
                printf("No hay distancia_autopista\n");
                distancia_autopista = 0;
            }


            // FASE 2.4: leer ciudad2
            sscanf(linea + desplazamiento + 1, "%m[^>]", &ciudad2);
            printf("Ciudad 2: %s\n\n ------------------- \n", ciudad2);

            //cambio los \r y \n por \0s
            // voy a usar strcsp
            ciudad1[strcspn(ciudad1, "\r\n")] = 0;
            ciudad2[strcspn(ciudad2, "\r\n")] = 0;

//            sleep(2);
//            printf("Ciudad 2: %s\n", ciudad2);
//            printf("Distancia carretera: %d\n", distancia_carretera);
//            printf("Distancia autopista: %d\n", distancia_autopista);




            strcpy(vertice1.nombre, ciudad1);

            //le quito al nombre de la ciudad1 el salto de línea o el retorno de carro

            strcpy(vertice2.nombre, ciudad2);

            if(hayCarretera)
            {
                printf("Debug: conectando %s con %s a modo de carretera\n", vertice1.nombre, vertice2.nombre);
                crear_arco(G, posicion(*G, vertice1), posicion(*G, vertice2), distancia_carretera, 'C');
            }
            if(hayAutopista)
            {
                printf("Debug: conectando %s con %s a modo de autopista\n", vertice1.nombre, vertice2.nombre);
                crear_arco(G, posicion(*G, vertice1), posicion(*G, vertice2), distancia_autopista, 'A');
            }

            free(ciudad1);
            free(ciudad2);
            imprimir_grafo(*G);
        }
//        sleep(2);


    }

    printf("Fin de lectura de archivo\n");

    free(linea);
    fclose(archivoLectura);
    return 0;
}
