#include "ETSEMaps.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <math.h>
#include <ctype.h>

#define liberarYcontinuar(linea) {free(linea); linea=NULL; continue;}

void
_crearArco(grafo *G, tipovertice *vertice1, tipovertice *vertice2, double distancia, char tipoConexion)
{
    if (!existe_vertice(*G, *vertice1))
    {
        insertar_vertice(G, *vertice1);
    }


    if (!existe_vertice(*G, *vertice2))
    {
        insertar_vertice(G, *vertice2);
    }


    crear_arco(G, posicion(*G, *vertice1), posicion(*G, *vertice2), distancia, tipoConexion);
}


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
    // Los comentarios (#) se ignoran
    // Las líneas en blanco se ignoran
    // Vamos a ello

    printf("Leyendo archivo...\n");

    char *linea = NULL;
    size_t tamLinea=0;
    ssize_t tamanhoLinea;

    while ((tamanhoLinea = getline(&linea, &tamLinea, archivoLectura)) != -1)
    {
        if(linea==NULL)
        {
            printf("Error al leer el archivo\n");
            return -1;
        }
        printf("Retrieved line of length %zu:\n", tamanhoLinea);
        printf("%s", linea);

        int posicionLecturaActual = 0;

        // FASE 1: ignorar espacios en blanco y comentarios
        {
            // voy a inspeccionar la línea para buscar espacios en blanco
            register char caracterActual = linea[posicionLecturaActual];
            while (caracterActual == ' ' || caracterActual == '\t')
            {
                printf("[DEBUG] Espacio en blanco\n");
                posicionLecturaActual++;
                caracterActual = linea[posicionLecturaActual];
            }

            // Si la línea empieza por #, la ignoro
            if (caracterActual == '#')
            {
                printf("[DEBUG] Comentario\n");
                liberarYcontinuar(linea);
            }
            // Si la línea está vacía, la ignoro
            if (caracterActual == '\n' || caracterActual == '\r')
            {
                printf("[DEBUG] Linea en blanco\n");
                liberarYcontinuar(linea);;
            }
        }




        // FASE 2: leer aristas
        if (true)
        {
            printf("\n[DEBUG] ARISTA!!\n");

            // dada la complejidad de la lectura de aristas, lo voy a hacer a mano, sin usar strtok
            // el formato es: ciudad<distancia_carretera(opcional)|distancia_autopista(opcional)>ciudad 2
            // o bien: ciudad<|distancia_autopista(opcional)>ciudad 2 --> esto es una autopista
            // o bien: ciudad<distancia_carretera(opcional)>ciudad 2  --> esto es una carretera

            tipovertice infoCiudad1;
            tipovertice infoCiudad2;

            bool hayCarretera = false, hayAutopista = false;

            // FASE 2.1: leer ciudad1
            {
                int finNombreCiudad = posicionLecturaActual;
                while (linea[finNombreCiudad] != '<')
                {
                    if (linea[finNombreCiudad] == '\0' || linea[finNombreCiudad] == '\n' || linea[finNombreCiudad] == '\r')
                    {
                        printf("[ERROR] Linea mal formada\n");
                        liberarYcontinuar(linea);
                    }
                    finNombreCiudad++;
                }

                if (finNombreCiudad == posicionLecturaActual)
                {
                    printf("[ERROR] Linea mal formada\n");
                    liberarYcontinuar(linea);
                }

                linea[finNombreCiudad] = '\0';
                strcpy(infoCiudad1.nombre, linea + posicionLecturaActual);

                posicionLecturaActual = finNombreCiudad;

            }

            printf("[DEBUG] Ciudad 1: '%s'\n", infoCiudad1.nombre);


            printf("[DEBUG] Desplazamiento: %d\n", posicionLecturaActual);

            if (linea[posicionLecturaActual] != '\0')
            {
                printf("[ERROR] Linea mal formada\n");
                liberarYcontinuar(linea);
            }

            posicionLecturaActual++; //nos saltamos el <

            // FASE 2.2: leer distancia_carretera
            double distancia_carretera = 0.0;

            {
                char *endptr = NULL;
                distancia_carretera = strtod(linea + posicionLecturaActual, &endptr);

                if (endptr == &linea[posicionLecturaActual])
                {
                    printf("[DEBUG] No ha habido conversión\n");
                }else
                {
                    hayCarretera = true;
                }

                posicionLecturaActual = endptr - linea;

                if (linea[posicionLecturaActual] != '|' && linea[posicionLecturaActual] != '>')
                {
                    printf("[ERROR] Linea mal formada\n");
                    liberarYcontinuar(linea);
                }

                if(linea[posicionLecturaActual] == '|')
                {
                    posicionLecturaActual++;
                }

            }


            // FASE 2.3: leer distancia_autopista

            double distancia_autopista = 0.0;

            {
                char *endptr = NULL;
                distancia_autopista = strtod(linea + posicionLecturaActual, &endptr);

                if (endptr == &linea[posicionLecturaActual])
                {
                    printf("[DEBUG] No ha habido conversión\n");
                }else
                {
                    hayAutopista = true;
                }

                posicionLecturaActual = endptr - linea;

                if ( linea[posicionLecturaActual] != '>')
                {
                    printf("[ERROR] Linea mal formada\n");
                    liberarYcontinuar(linea);
                }

                posicionLecturaActual++;

            }


            // FASE 2.4: leer ciudad2
            // Aquí tengo que tener en cuenta que puede haber un salto de línea o un retorno de carro
//            sscanf(linea + posicionLecturaActual + 1, "%m[^>]", &ciudad2);
            {
                int finNombreCiudad = posicionLecturaActual;
                while (linea[finNombreCiudad] != '\0' && linea[finNombreCiudad] != '\n' && linea[finNombreCiudad] != '\r')
                {
                    finNombreCiudad++;
                }

                if (finNombreCiudad == posicionLecturaActual)
                {
                    printf("[ERROR] Linea mal formada\n");
                    liberarYcontinuar(linea);
                }

                linea[finNombreCiudad] = '\0';
                strcpy(infoCiudad2.nombre, linea + posicionLecturaActual);
            }
            printf("[DEBUG] Ciudad 2: %s\n ------------------- \n", infoCiudad2.nombre);

//            //cambio los \r y \n por \0s para que no me dé problemas al comparar e imprimir
//            ciudad1[strcspn(ciudad1, "\r\n")] = 0;
//            ciudad2[strcspn(ciudad2, "\r\n")] = 0;

//            sleep(2);
//            printf("Ciudad 2: %s\n", ciudad2);
//            printf("Distancia carretera: %d\n", distancia_carretera);
//            printf("Distancia autopista: %d\n", distancia_autopista);


            if (hayCarretera)
            {
                printf("[DEBUG] conectando %s con %s a modo de carretera con distancia %lf\n", infoCiudad1.nombre, infoCiudad2.nombre, distancia_carretera);
                _crearArco(G, &infoCiudad1, &infoCiudad2, distancia_carretera, 'C');
            }
            if (hayAutopista)
            {
                printf("[DEBUG] conectando %s con %s a modo de autopista\n", infoCiudad1.nombre, infoCiudad2.nombre);
                _crearArco(G, &infoCiudad1, &infoCiudad2, distancia_autopista, 'A');
            }

        }
//        sleep(2);
        free(linea);
        linea = NULL;
        printf("\n\n");

    }

    printf("[DEBUG] Fin de lectura de archivo\n");


    fclose(archivoLectura);
    printf("\n\n");
    imprimir_grafo(*G);
    printf("\n\n");
    printf("\n\n");

    return 0;
}
