//
// Created by imarc on 31/10/2023.
//

#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <stdbool.h>
#include "grafo.h"
#include "ETSEMaps.h"


void imprimirMatriz(double matrix[][MAXVERTICES], int V)
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
                printf("%10.2f", matrix[i][j]);
            }
        }
        printf("\n");
    }
}


double calcularDistanciaCombinada(grafo G, int i, int j, int distanciaTiempoDinero)
{
    double distanciaC = calcularAdyacencia(G, i, j, 'C');
    double distanciaA = calcularAdyacencia(G, i, j, 'A');

    switch (distanciaTiempoDinero)
    {
        case 0:
            distanciaC /= 1;
            distanciaA /= 1;
            break;

        case 1:
            distanciaC /= VELOCIDADCARRETERA;
            distanciaA /= VELOCIDADAUTOPISTA;
            break;

        case 2:
            distanciaC *= PRECIOPORKMCARRETERA;
            distanciaA *= PRECIOPORKMAUTOPISTA;
            break;

        default:
            break;


    }


    if (distanciaC == 0 && distanciaA != 0)
    {
        return distanciaA;
    }
    if (distanciaA == 0 && distanciaC != 0)
    {
        return distanciaC;
    }

    if (distanciaA == 0 && distanciaC == 0)
    {
        return 0.00;
    }


    // Elige la distancia mínima entre C y D
    return (distanciaC < distanciaA) ? distanciaC : distanciaA;
}

// función para calcular floyd warshall
void floydWarshall(grafo G, int origen, int destino, int modo)
{

    register int V = num_vertices(G);

    printf("V es %d\n", V);

    double D[V][V];



    //voy a rellenar la matriz
    for (int i = 0; i < V; i++)
    {
        for (int j = 0; j < V; j++)
        {
            if (i == j)
            {
                printf("i: %d, j: %d\n", i, j);
                D[i][j] = 0;
            } else if ((calcularDistanciaCombinada(G, i, j, modo) != 0) && i != j)
            {
                D[i][j] = calcularDistanciaCombinada(G, i, j, modo);
            } else
            {
                D[i][j] = INFINITY;
            }
        }
    }

    double P[V][V];

    //voy a rellenar la matriz
    // i si D[i,j]!=0 y i!=j
    // 0 en otro caso

    for (int i = 0; i < V; i++)
    {
        for (int j = 0; j < V; j++)
        {
            if (calcularDistanciaCombinada(G, i, j, modo) != 0 && i != j)
            {
                P[i][j] = i;
            } else
            {
                P[i][j] = 0;
            }
        }
    }



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
                    P[i][j] = P[k][j];
                }
            }
        }
    }

    // Como la condenada función de imprimir matriz no funciona, voy a hacerlo a mano
    printf("Matriz D:\n");
    for (int i = 0; i < V; i++)
    {
        for (int j = 0; j < V; j++)
        {
            if (D[i][j] == INFINITY)
            {
                printf("%10s", "INF");
            } else
            {
                printf("%10.2f", D[i][j]);
            }
        }
        printf("\n");
    }


    printf("El camino más corto entre %s y %s es: %10.2f\n", array_vertices(G)[origen].nombre, array_vertices(G)[destino].nombre, D[origen][destino]);


}
