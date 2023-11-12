
#include <ctype.h>
#include <float.h>
#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "ETSEMaps.h"

// Defines

#define kPosicionVerticeFalso (-1)

//#define continue; {/*free(linea); linea=NULL; */continue;}

#define duracionCarretera(distancia) (distancia / VELOCIDADCARRETERA)
#define duracionAutopista(distancia) (distancia / VELOCIDADAUTOPISTA)
#define duracion(distancia, tipoVia) (tipoVia == CARRETERA ? duracionCarretera(distancia) : tipoVia == AUTOPISTA ? duracionAutopista(distancia) : 0)

// tipedefs y structs

//enum TipoVia
//{
//    NINGUNA = '.', CARRETERA = 'C', AUTOPISTA = 'A'
//};

struct TipoDatoP
{
    int siguienteVertice;
    enum TipoVia tipoVia;
};

// funciones privadas

void
_crearArco(grafo *G, tipovertice *vertice1, tipovertice *vertice2, double distancia, enum TipoVia tipoVia)
{
    if (!existe_vertice(*G, *vertice1))
    {
        insertar_vertice(G, *vertice1);
    }


    if (!existe_vertice(*G, *vertice2))
    {
        insertar_vertice(G, *vertice2);
    }


    crear_arco(G, posicion(*G, *vertice1), posicion(*G, *vertice2), distancia, tipoVia);
}

void _imprimirD(double matrix[][MAXVERTICES], int V)
{
    for (int i = 0; i < V; i++)
    {
        for (int j = 0; j < V; j++)
        {
            if (matrix[i][j] == INFINITY)
            {
                printf("%10s", "INF");
            } else
            {
                printf("%10.2lf", matrix[i][j]);
            }
        }

        printf("\n");
    }
}

void _imprimirP(struct TipoDatoP P[][MAXVERTICES], int V)
{
    for (int i = 0; i < V; i++)
    {
        for (int j = 0; j < V; ++j)
        {
            if (P[i][j].tipoVia == NINGUNA)
            {
                printf("     %c", P[i][j].tipoVia);
            } else
            {
                printf("%5d%c", P[i][j].siguienteVertice, P[i][j].tipoVia);
            }
        }
        printf("\n");
    }
}
// funciones públicas que no aparecen en el main

int
leerArchivo(FILE *archivoLectura, grafo *G)
{
    //compruebo que el archivo existe
    if (archivoLectura == NULL)
    {
        printf("Error al abrir el archivo\n");
        return -1;
    }


    //Leo el archivo
    // Según he diseñado el formato (Aún puede ser susceptible a cambios) lo primero que se leen son los vertices (puntos)
    // y luego las aristas (conexiones entre puntos)
    // Los comentarios (#) se ignoran
    // Las líneas en blanco se ignoran

    printf("Leyendo archivo...\n");

    char *linea = NULL;
    size_t tamLinea = 0;
    ssize_t tamanhoLinea;

    // getline se encarga de gestionar la memoria, es decir, reserva (con malloc) y amplía (con realloc)
    // esta según sea necesario.
    while ((tamanhoLinea = getline(&linea, &tamLinea, archivoLectura)) != -1)
    {
//        if (linea == NULL)
//        {
//            printf("Error al leer el archivo\n");
//            return -1;
//        }
//        printf("[DEBUG] Retrieved line of length %zu:\n", tamanhoLinea);
//        printf("%s", linea);

        int posicionLecturaActual = 0;

        // FASE 1: ignorar espacios en blanco y comentarios
        {
            // voy a inspeccionar la línea para buscar espacios en blanco
            char caracterActual = linea[posicionLecturaActual];
            while (caracterActual == ' ' || caracterActual == '\t')
            {
//                printf("[DEBUG] Espacio en blanco\n");
                posicionLecturaActual++;
                caracterActual = linea[posicionLecturaActual];
            }

            // Si la línea empieza por #, la ignoro
            if (caracterActual == '#')
            {
//                printf("[DEBUG] Comentario\n");
                continue;
            }
            // Si la línea está vacía, la ignoro
            if (caracterActual == '\n' || caracterActual == '\r')
            {
//                printf("[DEBUG] Linea en blanco\n");
                continue;
            }
        }
//        free(linea);




        // FASE 2: leer aristas
        if (true)
        {
//            printf("\n[DEBUG] ARISTA!!\n");

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
                        continue;
                    }
                    finNombreCiudad++;
                }

                if (finNombreCiudad == posicionLecturaActual)
                {
                    // Se encuentra en una cadena de longitud 0 o el primer caracter es <
                    printf("[ERROR] Linea mal formada\n");
                    continue;
                }

                linea[finNombreCiudad] = '\0';
                strcpy(infoCiudad1.nombre, linea + posicionLecturaActual);

                posicionLecturaActual = finNombreCiudad + 1;

            }

//            printf("[DEBUG] Ciudad 1: '%s'\n", infoCiudad1.nombre);


//            printf("[DEBUG] Desplazamiento: %d\n", posicionLecturaActual);

//          if (linea[posicionLecturaActual] != '\0')
//          {
//              printf("[ERROR] Linea mal formada\n");
//              continue;
//          }
//
//          posicionLecturaActual++; //nos saltamos el <

            // FASE 2.2: leer distancia_carretera
            double distancia_carretera = 0.0;

            {
                char *endptr = NULL;
                distancia_carretera = strtod(linea + posicionLecturaActual, &endptr);

                if (endptr == &linea[posicionLecturaActual])
                {
//                    printf("[DEBUG] No ha habido conversión\n");
                } else
                {
                    hayCarretera = true;
                }

                posicionLecturaActual = endptr - linea;

                if (linea[posicionLecturaActual] != '|' && linea[posicionLecturaActual] != '>')
                {
                    printf("[ERROR] Linea mal formada\n");
                    continue;
                }


            }


            // FASE 2.3: leer distancia_autopista

            double distancia_autopista = 0.0;

            if (linea[posicionLecturaActual] == '|')
            {
                posicionLecturaActual++;

                char *endptr = NULL;
                distancia_autopista = strtod(linea + posicionLecturaActual, &endptr);

                if (endptr == &linea[posicionLecturaActual])
                {
//                    printf("[DEBUG] No ha habido conversión\n");
                } else
                {
                    hayAutopista = true;
                }

                posicionLecturaActual = endptr - linea;
            }

            if (linea[posicionLecturaActual] != '>')
            {
                printf("[ERROR] Linea mal formada\n");
                continue;
            }

            posicionLecturaActual++;



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
                    continue;
                }

                linea[finNombreCiudad] = '\0';
                strcpy(infoCiudad2.nombre, linea + posicionLecturaActual);
            }
//            printf("[DEBUG] Ciudad 2: %s\n ------------------- \n", infoCiudad2.nombre);

//            //cambio los \r y \n por \0s para que no me dé problemas al comparar e imprimir
//            ciudad1[strcspn(ciudad1, "\r\n")] = 0;
//            ciudad2[strcspn(ciudad2, "\r\n")] = 0;

//            sleep(2);
//            printf("Ciudad 2: %s\n", ciudad2);
//            printf("Distancia carretera: %d\n", distancia_carretera);
//            printf("Distancia autopista: %d\n", distancia_autopista);

            fprintf(stdout, "[INFO] '%s' < %lf | %lf > '%s'\n", infoCiudad1.nombre, distancia_carretera, distancia_autopista, infoCiudad2.nombre);

            if (hayCarretera)
            {
//                printf("[DEBUG] conectando %s con %s a modo de carretera con distancia %lf\n", infoCiudad1.nombre, infoCiudad2.nombre, distancia_carretera);
                _crearArco(G, &infoCiudad1, &infoCiudad2, distancia_carretera, CARRETERA);
            }
            if (hayAutopista)
            {
//                printf("[DEBUG] conectando %s con %s a modo de autopista\n", infoCiudad1.nombre, infoCiudad2.nombre);
                _crearArco(G, &infoCiudad1, &infoCiudad2, distancia_autopista, AUTOPISTA);
            }

        }
//        sleep(2);

//        printf("\n\n");

    }

    free(linea);
    linea = NULL;

//    printf("[DEBUG] Fin de lectura de archivo\n");

    fclose(archivoLectura);

    printf("\n\n");

    imprimir_grafo(*G);

    printf("\n\n");
    printf("\n\n");

    return 0;
}

//FUNCIONES DEL PROGRAMA DE PRUEBA DE GRAFOS

//Opción a del menú, introducir un vértice en el grafo

void introducir_vertice(grafo *G)
{
    tipovertice v1;
    printf("Introduce vértice: ");
    scanf("%s", v1.nombre);
    if (existe_vertice(*G, v1))
    {
        printf("Ese vértice ya esta en el grafo\n");
    } else
    {
        insertar_vertice(G, v1);
    }
}
//Opción 'b' del menú, eliminar un vértice del grafo

void eliminar_vertice(grafo *G)
{
    tipovertice v1;
    printf("Introduce vértice: ");
    scanf(" %s", v1.nombre);
    if (existe_vertice(*G, v1))
    {
        borrar_vertice(G, v1);
    } else
    {
        printf("Ese vértice no existe en el grafo\n");
    }
}

//Opción 'c' del menú, crear una relación entre dos vértices

void nuevo_arco(grafo *G)
{
    tipovertice v1, v2;
    //Insertamos una nueva relación pidiendo los datos al usuario controlando que existan los vértices
    printf("Nueva relación vertice1-->vertice2\n");
    //Vértice origen del arco
    printf("Introduce vértice origen: ");
    scanf("%s", v1.nombre);
    if (!existe_vertice(*G, v1))
    {
        printf("El vértice %s no existe en el grafo\n", v1.nombre);
        return;
    }
    //Vértice destino del arco
    printf("Introduce vértice destino: ");
    scanf("%s", v2.nombre);
    if (!existe_vertice(*G, v2))
    {
        printf("El vértice %s no existe en el grafo\n", v2.nombre);
        return;
    }

    char tipoVia;
    printf("Introduce el tipo de conexion: ");
    scanf(" %c", &tipoVia);
    tipoVia = (char) toupper(tipoVia);
    if (tipoVia != AUTOPISTA && tipoVia != CARRETERA)
    {
        printf("El tipo de conexion no es valido\n");
        return;
    }

    double valorArco;
    printf("Introduce el valor del arco: ");
    scanf("%lf", &valorArco);
    if (valorArco <= 0)
    {
        printf("El valor del arco no es valido\n");
        return;
    }

    //Creación del arco
    if (!distancia(*G, posicion(*G, v1), posicion(*G, v2), tipoVia))
    {
        crear_arco(G, posicion(*G, v1), posicion(*G, v2), valorArco, tipoVia);
    }
}

//Opción d del menú, eliminar una relación entre dos vértices
void eliminar_arco(grafo *G)
{
    tipovertice v1, v2;
    //Eliminamos una relación pidiendo los datos al usuario controlando que existan los vértices
    printf("Eliminar relacion vertice1-->vertice2\n");
    //Vértice origen del arco
    printf("Introduce vértice origen: ");
    scanf("%s", v1.nombre);
    if (!existe_vertice(*G, v1))
    {
        printf("El vértice %s no existe en el grafo\n", v1.nombre);
        return;
    }
    //Vértice destino del arco
    printf("Introduce vértice destino: ");
    scanf("%s", v2.nombre);
    if (!existe_vertice(*G, v2))
    {
        printf("El vértice %s no existe en el grafo\n", v2.nombre);
        return;
    }

    char tipoVia;
    printf("Introduce el tipo de conexión: ");
    scanf(" %c", &tipoVia);

    tipoVia = toupper(tipoVia);

    // Eliminación del arco


    switch (tipoVia)
    {

        case AUTOPISTA:
        case CARRETERA:
            if (distancia(*G, posicion(*G, v1), posicion(*G, v2), tipoVia))
            {
                borrar_arco(G, posicion(*G, v1), posicion(*G, v2), tipoVia);
            }
            break;

        default:
            printf("El tipo de conexión no es valido\n");
            return;
    }

}

//Opción 'i' del menú, imprimir el grafo
//Función que imprime el grafo utilizando num_vertices para saber cuántos vértices tiene
//y array_vertices para recuperar el vector de vértices y recorrerlo

void imprimir_grafo(grafo G)
{
    tipovertice *VECTOR; //Para almacenar el vector de vértices del grafo
    int N; //número de vértices del grafo

    //Para recorrerla, simplemente vamos a recorrer la matriz de adyacencia
    N = num_vertices(G);
    VECTOR = array_vertices(G);

    int i, j;
    printf("El grafo actual es:\n");
    for (i = 0; i < N; i++)
    {
        //Imprimo el vértice
        printf("vértice(%i): %s\n", i, VECTOR[i].nombre);
        //Chequeo sus arcos
        for (j = 0; j < N; j++)
        {
            if (distancia(G, i, j, CARRETERA))
            {
                printf("\t--> %s con valor %lf\n", VECTOR[j].nombre, calcularAdyacencia(G, i, j, CARRETERA));
            }

            if (distancia(G, i, j, AUTOPISTA))
            {
                printf("\t==> %s con valor %lf\n", VECTOR[j].nombre, calcularAdyacencia(G, i, j, AUTOPISTA));
            }
        }
    }
}

//todo: mirar esta función
void imprimirCamino(grafo G, struct TipoDatoP P[][100], const int posVerticeOrigen, int posVerticeDestino)
{

    const int posVerticeDestinoIntermedio = P[posVerticeOrigen][posVerticeDestino].siguienteVertice;



    if ((posVerticeOrigen != posVerticeDestino))
    {
        if(posVerticeDestinoIntermedio == kPosicionVerticeFalso)
        {
            printf("[No hay camino] ");
            return;
        }
        imprimirCamino(G, P, posVerticeOrigen, posVerticeDestinoIntermedio);
    }
//    else
//    {
//        printf("\n XXX \n");
//    }

//    printf("\n[DEBUG] pos origen: %d [%s], pos destino: %d [%s] ", posVerticeOrigen, array_vertices(G)[posVerticeOrigen].nombre, posVerticeDestino, array_vertices(G)[posVerticeDestino].nombre);

//    printf("%s %s ", P[posVerticeOrigen][posVerticeDestino].tipoVia == CARRETERA ? "-->" : P[posVerticeOrigen][posVerticeDestino].tipoVia == AUTOPISTA ? "==>" : "/>", array_vertices(G)[posVerticeDestino].nombre);
    if (posVerticeOrigen != posVerticeDestino)
    {
        printf("%s ", P[posVerticeOrigen][posVerticeDestino].tipoVia == CARRETERA ? "-->" : P[posVerticeOrigen][posVerticeDestino].tipoVia == AUTOPISTA ? "==>" : "/>");
    }
    printf("%s ", array_vertices(G)[posVerticeDestino].nombre);

}

/**
 * Calcula la distancia/precio/tiempo entre dos vértices y escoge el medio de transporte más adecuado
 * @param G grafo
 * @param posVerticeOrigen
 * @param posVerticeDestino
 * @param tipoDeConexion
 * @return distancia/precio/tiempo mas óptimo según el parámetro entre dos vértices.
 * @pre *medioEscogido DEBE SER NO NULO. De serlo, se dará comportamiento indefinido
 */
double calcularDistanciaCombinada(grafo G, const int posVerticeOrigen, const int posVerticeDestino, const enum TipoOptimizacionWarsall tipoOptimizacionWarsall, enum TipoVia *tipoViaEscogida)
{

    double distanciaC = calcularAdyacencia(G, posVerticeOrigen, posVerticeDestino, CARRETERA);
    double distanciaA = calcularAdyacencia(G, posVerticeOrigen, posVerticeDestino, AUTOPISTA);

    //Aquí se hace la conversión de distancia a distancia (sin operación), tiempo o dinero
    switch (tipoOptimizacionWarsall)
    {
        case TIEMPO:
            distanciaC /= VELOCIDADCARRETERA;
            distanciaA /= VELOCIDADAUTOPISTA;
            break;

        case DINERO:
            distanciaC *= PRECIOPORKMCARRETERA;
            distanciaA *= PRECIOPORKMAUTOPISTA;
            break;

        case DISTANCIA:
            //Caída intencional
        default:
            break;


    }

    // Si no existe ninguna conexión por carretera pero sí por autopista, se devuelve la distancia por autopista
    if (distanciaC <= 0 && distanciaA > 0)
    {
        *tipoViaEscogida = AUTOPISTA;
        printf("[DEBUG] he escogido autopista para %s y %s\n", array_vertices(G)[posVerticeOrigen].nombre,
               array_vertices(G)[posVerticeDestino].nombre);
        printf("[DEBUG] val %lf vs %lf\n\n", distanciaC, distanciaA);
        return distanciaA;
    }
    //Si después de la conversión no hay distancia por autopista, pero sí por carretera, se devuelve la distancia por carretera
    if (distanciaA <= 0 && distanciaC > 0)
    {
        *tipoViaEscogida = CARRETERA;
        printf("[DEBUG] he escogido carretera para %s y %s\n", array_vertices(G)[posVerticeOrigen].nombre,
               array_vertices(G)[posVerticeDestino].nombre);
        printf("[DEBUG] val %lf vs %lf\n\n", distanciaC, distanciaA);
        return distanciaC;
    }

    //Si no hay conexión por carretera ni por autopista, se devuelve 0
    if (distanciaA <= 0 && distanciaC <= 0)
    {
        *tipoViaEscogida = NINGUNA;
        printf("[DEBUG] no hay camino\n");

        return 0.00;
    }


    // En el caso de que haya conexión por carretera y por autopista, se escoge la más óptima
    // Elige la distancia mínima entre C y D
    if (distanciaC < distanciaA)
    {
        *tipoViaEscogida = CARRETERA;
        return distanciaC;
    } else
    {
        *tipoViaEscogida = AUTOPISTA;
        return distanciaA;
    }
}

// función para calcular floyd warshall
void floydWarshall(grafo G, const enum TipoOptimizacionWarsall tipoOptimizacionWarsall)
{

    printf("Escriba a continuación el nombre del origen y el destino\n");

    tipovertice vertice1;

    printf("Origen: ");
    scanf(" %s", vertice1.nombre);
    if (!existe_vertice(G, vertice1))
    {
        printf("[ERROR] El vértice %s no existe en el grafo\n", vertice1.nombre);
        return;
    }

    tipovertice vertice2;

    printf("Destino: ");
    scanf(" %s", vertice2.nombre);
    if (!existe_vertice(G, vertice2))
    {
        printf("[ERROR] El vértice %s no existe en el grafo\n", vertice2.nombre);
        return;
    }

    // Obtengo la posición de los vértices. Estos valores no deberían variar.
    const int posicionVerticeOrigen = posicion(G, vertice1);
    const int posicionVerticeDestino = posicion(G, vertice2);
    if (posicionVerticeOrigen == posicionVerticeDestino)
    {
        printf("[ERROR] El origen y el destino son el mismo\n");
        return;
    }

    const int numVertices = num_vertices(G);

    printf("V es %d\n", numVertices);

    double D[MAXVERTICES][MAXVERTICES];

    struct TipoDatoP P[MAXVERTICES][MAXVERTICES];

//    //inicializo la matriz P
//    for (int i = 0; i < V; i++)
//    {
//        for (int j = 0; j < V; ++j)
//        {
//            P[i][j].siguienteVertice = kPosicionVerticeFalso;
//            P[i][j].tipoVia = NINGUNA;
//        }
//    }

    //voy a rellenar la matriz
    for (int i = 0; i < numVertices; i++)
    {
        for (int j = 0; j < numVertices; j++)
        {
            P[i][j].siguienteVertice = kPosicionVerticeFalso;
            P[i][j].tipoVia = NINGUNA;

            if (i == j)
            {
                D[i][j] = 0;
            } else
            {
                enum TipoVia tipoViaEscogida = NINGUNA;
                double distancia = calcularDistanciaCombinada(G, i, j, tipoOptimizacionWarsall, &tipoViaEscogida);

                if (tipoViaEscogida != NINGUNA)
                {
                    D[i][j] = distancia;
                    P[i][j].siguienteVertice = i;
                    P[i][j].tipoVia = tipoViaEscogida;
                } else
                {
                    D[i][j] = INFINITY;
                }
            }
        }
    }

    printf("Matriz D (0):\n");
    _imprimirD(D, numVertices);


    printf("Matriz P(0):\n");
    _imprimirP(P, numVertices);


    //Analizamos matriz D k
    for (int k = 0; k < numVertices; k++)
    {
        //arco ik
        for (int i = 0; i < numVertices; i++)
        {
            //arco k->
            for (int j = 0; j < numVertices; j++)
            {
                if (D[i][j] > D[i][k] + D[k][j])
                {
                    D[i][j] = D[i][k] + D[k][j];
                    P[i][j].siguienteVertice = P[k][j].siguienteVertice;
                    P[i][j].tipoVia = P[k][j].tipoVia;
                }
            }
        }
    }

    printf("P final:\n");
    _imprimirP(P, numVertices);


    printf("Matriz D:\n");
    _imprimirD(D, numVertices);


    printf("El camino más %s entre %s y %s es de %.2lf", tipoOptimizacionWarsall == DISTANCIA ? "corto" : tipoOptimizacionWarsall == TIEMPO ? "rápido" : "barato",
           array_vertices(G)[posicionVerticeOrigen].nombre, array_vertices(G)[posicionVerticeDestino].nombre, D[posicionVerticeOrigen][posicionVerticeDestino]);

    printf("%s\n", tipoOptimizacionWarsall == DISTANCIA ? " km\n" : tipoOptimizacionWarsall == TIEMPO ? " h\n" : " €\n");

    imprimirCamino(G, P, posicionVerticeOrigen, posicionVerticeDestino);//, carreteraOAutopista);
}

double prim(grafo G)
{
    int numArcos = 0;
    double duracionTrayecto = 0.0;

    const int numeroDeVertices = num_vertices(G);

    char *tipoDeConexion = (char *) malloc(sizeof(char) * numeroDeVertices);
    for (int i = 0; i < numeroDeVertices; i++)
    {
        tipoDeConexion[i] = NINGUNA;
    }

    bool *selected = (bool *) malloc(sizeof(bool) * numeroDeVertices);
    for (int i = 0; i < numeroDeVertices; i++)
    {
        selected[i] = false;
    }

    selected[0] = true;


    while (numArcos < numeroDeVertices - 1)
    {
        double minimo = DBL_MAX;
        int vX = kPosicionVerticeFalso;
        int vY = kPosicionVerticeFalso;

        for (int i = 0; i < numeroDeVertices; i++)
        {
            if (selected[i])
            {
                for (int j = 0; j < numeroDeVertices; j++)
                {
                    if (selected[j] != true)
                    {

                        const double distC = distancia(G, i, j, CARRETERA);
                        if (distC != 0)
                        {
                            const double duracionC = duracion(calcularAdyacencia(G, i, j, CARRETERA), CARRETERA);
                            if (duracionC < minimo)
                            {
                                minimo = duracionC;
                                tipoDeConexion[i] = CARRETERA;
                                vX = i;
                                vY = j;
                            }
                        }

                        const double distA = distancia(G, i, j, AUTOPISTA);
                        if (distA != 0)
                        {
                            const double duracionA = duracion(calcularAdyacencia(G, i, j, AUTOPISTA), AUTOPISTA);
                            if (duracionA < minimo)
                            {
                                minimo = duracionA;
                                tipoDeConexion[i] = AUTOPISTA;
                                vX = i;
                                vY = j;
                            }

                        }

                    }

                }
            }
        }

        numArcos++;

        if (vX >= 0 && vY >= 0)
        {
            selected[vY] = true;

            if (tipoDeConexion[vX] == CARRETERA)
            {
                printf("%10s -- %10s : %10.2lf\n", array_vertices(G)[vX].nombre, array_vertices(G)[vY].nombre, duracion((calcularAdyacencia(G, vX, vY, CARRETERA)), CARRETERA));
                duracionTrayecto += duracionCarretera(calcularAdyacencia(G, vX, vY, CARRETERA));
            } else if (tipoDeConexion[vX] == AUTOPISTA)
            {
                printf("%10s == %10s : %10.2lf\n", array_vertices(G)[vX].nombre, array_vertices(G)[vY].nombre, duracion(calcularAdyacencia(G, vX, vY, AUTOPISTA), AUTOPISTA));
                duracionTrayecto += duracionAutopista(calcularAdyacencia(G, vX, vY, AUTOPISTA));
            }
        }
    }

    printf("Tiempo del árbol de expansión de coste mínimo = %.2lf horas\n", duracionTrayecto);

    free(selected);
    free(tipoDeConexion);

    return duracionTrayecto;
}
