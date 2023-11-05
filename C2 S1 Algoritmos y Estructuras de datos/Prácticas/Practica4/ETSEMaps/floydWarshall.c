//
// Created by imarc on 31/10/2023.
//

#include <stdio.h>
#include <math.h>
#include <stdbool.h>
#include "grafo.h"
#include "ETSEMaps.h"

enum medios
{
    CARRETERA, AUTOPISTA
};

struct tipodatoP
{
    int dato;
    int tipoConexion;
};

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

void _imprimirP(struct tipodatoP P[][MAXVERTICES],int V)
{
    for (int i = 0; i < V; i++)
    {
        for (int j = 0; j < V; ++j)
        {
            printf("%5d%s", P[i][j].dato, P[i][j].tipoConexion == CARRETERA ? "C" : P[i][j].tipoConexion == AUTOPISTA ? "A" : "N");
        }
        printf("\n");
    }
}


void imprimirCamino(grafo *G, struct tipodatoP P[][MAXVERTICES], int origen, int destino)//, int carreteraOAutopista[][MAXVERTICES])
{
    // Para evitar que se imprima el nodo inicial dos veces hay tres opciones:
    // Indicar mediante un parámetro si se ha empezado o no a imprimir
    // Crear una variable estática que indique si se ha empezado a imprimir
    // Crear una variable global que indique si se ha empezado a imprimir

    // Como la opción 3 es inaceptable y la 1 añade ruido al código, se ha optado por la opción 2
    static bool heEmpezado = false;

    if (heEmpezado == false)
    {
//        printf("NODO INICIAL: %s con id: %d\n", array_vertices(*G)[origen].nombre, origen);
//        printf("NODO FINAL: %s con id: %d\n", array_vertices(*G)[destino].nombre, destino);
        printf("%s  ", array_vertices(*G)[origen].nombre);
    }

    heEmpezado = true;

    int destinoIntermedio = P[origen][destino].dato;
    if ((origen != destino))
    {
        imprimirCamino(G, P, origen, destinoIntermedio);
    }else
    {
        return;
    }

//        printf("(%d)%s (%d) %s ",destinoIntermedio, P[origen][destino].tipoConexion == CARRETERA ? "-->" : P[origen][destino].tipoConexion == AUTOPISTA ? "==>" : "/>", destino, array_vertices(*G)[destino].nombre);
          printf("%s %s ", P[origen][destino].tipoConexion == CARRETERA ? "-->" : P[origen][destino].tipoConexion == AUTOPISTA ? "==>" : "/>", array_vertices(*G)[destino].nombre);
    heEmpezado = false;

}

/**
 * Calcula la distancia/precio/tiempo entre dos vértices y escoge el medio de transporte más adecuado
 * @param G grafo
 * @param i
 * @param j
 * @param tipoDeConexion
 * @return distancia/precio/tiempo mas óptimo según el parámetro entre dos vértices.
 * @pre *medioEscogido DEBE SER NO NULO. De serlo, se dará comportamiento indefinido
 */
double calcularDistanciaCombinada(grafo G, const int i, const int j, const int distanciaTiempoDinero, int *medioEscogido)
{
    // El modificador register indica al compilador que la variable se usará mucho y que es mejor que la guarde en un registro.
    // El compilador puede ignorar esta indicación, pero es interesante la posible optimización que puede hacer.
    register double distanciaC = calcularAdyacencia(G, i, j, 'C');
    register double distanciaA = calcularAdyacencia(G, i, j, 'A');

    //Aquí se hace la conversión de distancia a distancia (sin operación), tiempo o dinero
    switch (distanciaTiempoDinero)
    {
        case DISTANCIA:
            break;

        case TIEMPO:
            distanciaC /= VELOCIDADCARRETERA;
            distanciaA /= VELOCIDADAUTOPISTA;
            break;

        case DINERO:
            distanciaC *= PRECIOPORKMCARRETERA;
            distanciaA *= PRECIOPORKMAUTOPISTA;
            break;

        default:
            break;


    }

    // Si no existe ninguna conexión por carretera pero sí por autopista, se devuelve la distancia por autopista
    if (distanciaC <= 0 && distanciaA > 0)
    {
        *medioEscogido = AUTOPISTA;
        printf("[DEBUG] he escogido autopista para %s y %s\n", array_vertices(G)[i].nombre,
               array_vertices(G)[j].nombre);
        printf ("[DEBUG] val %lf vs %lf\n\n", distanciaC, distanciaA);
        return distanciaA;
    }
    //Si después de la conversión no hay distancia por autopista pero sí por carretera, se devuelve la distancia por carretera
    if (distanciaA <= 0 && distanciaC > 0)
    {
        *medioEscogido = CARRETERA;
        printf("[DEBUG] he escogido carretera para %s y %s\n", array_vertices(G)[i].nombre,
               array_vertices(G)[j].nombre);
        printf ("[DEBUG] val %lf vs %lf\n\n", distanciaC, distanciaA);
        return distanciaC;
    }

    //Si no hay conexión por carretera ni por autopista, se devuelve 0
    if (distanciaA <= 0 && distanciaC <= 0)
    {
        *medioEscogido = -1;
        printf("[DEBUG] no hay camino\n");

        return 0.00;
    }


    // En el caso de que haya conexión por carretera y por autopista, se escoge la más óptima
    // Elige la distancia mínima entre C y D
    if (distanciaC < distanciaA)
    {
        *medioEscogido = CARRETERA;
//        printf("[DEBUG] he escogido carretera para %s y %s\n", array_vertices(G)[i].nombre,
//               array_vertices(G)[j].nombre);
//        printf ("[DEBUG] val %lf vs %lf\n\n", distanciaC, distanciaA);
        return distanciaC;
    } else
    {
        *medioEscogido = AUTOPISTA;
//        printf("[DEBUG] he escogido autopista para %s y %s\n", array_vertices(G)[i].nombre,
//               array_vertices(G)[j].nombre);
//        printf ("[DEBUG] val %lf vs %lf\n\n", distanciaC, distanciaA);
        return distanciaA;
    }
}

// función para calcular floyd warshall
void floydWarshall(grafo G, int modo)
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
    const int origen = posicion(G, vertice1);
    const int destino = posicion(G, vertice2);
    if (origen == destino)
    {
        printf("[ERROR] El origen y el destino son el mismo\n");
        return;
    }

    register const int V = num_vertices(G);

    printf("V es %d\n", V);

    double D[MAXVERTICES][MAXVERTICES];


//    int carreteraOAutopista[MAXVERTICES][MAXVERTICES];// 0 si es carretera, 1 si es autopista -1 si no hay camino




    struct tipodatoP P[MAXVERTICES][MAXVERTICES];

    //voy a rellenar la matriz
    for (int i = 0; i < V; i++)
    {
        for (int j = 0; j < V; j++)
        {
            if (i == j)
            {
                D[i][j] = 0;
            } else if ((calcularDistanciaCombinada(G, i, j, modo, &P[i][j].tipoConexion)!= 0) && i != j)
            {
                D[i][j] = calcularDistanciaCombinada(G, i, j, modo, &P[i][j].tipoConexion);
                P[i][j].dato = i;
            } else
            {
                D[i][j] = INFINITY;
            }
        }
    }

    printf("Matriz D (0):\n");
    _imprimirD(D, V);



    printf("Matriz P(0):\n");
    _imprimirP(P, V);


    //Analizamos matriz D k
    for (int k = 0; k < V; k++)
    {
        //arco ik
        for (int i = 0; i < V; i++)
        {
            //arco k->
            for (int j = 0; j < V; j++)
            {
                if (D[i][j] > D[i][k] + D[k][j])
                {
                    D[i][j] = D[i][k] + D[k][j];
                    P[i][j].dato = P[k][j].dato;
                    P[i][j].tipoConexion = P[k][j].tipoConexion;
                }
            }
        }
    }

    printf("P final:\n");
    _imprimirP(P, V);


    printf("Matriz D:\n");
    _imprimirD(D, V);


    printf("El camino más %s entre %s y %s es de %.2lf", modo == 0 ? "corto" : modo == 1 ? "rápido" : "barato",
           array_vertices(G)[origen].nombre, array_vertices(G)[destino].nombre, D[origen][destino]);

    printf("%s\n", modo == 0 ? " Kms\n" : modo == 1 ? " Horas\n" : " €\n");

    imprimirCamino(&G, P, origen, destino);//, carreteraOAutopista);

}


