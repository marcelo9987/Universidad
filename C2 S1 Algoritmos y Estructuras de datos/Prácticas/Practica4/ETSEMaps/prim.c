#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "ETSEMaps.h"
#include <float.h>

// ---- DEFINICIONES Y MACROS ----

#define PRECIOPORKMCARRETERA 0.01
#define PRECIOPORKMAUTOPISTA 0.07

#define VELOCIDADCARRETERA 70
#define VELOCIDADAUTOPISTA 120

// voy a definir una macro que me calcule la duración de un trayecto por carretera, otro por autopista
// y otro dependiendo del tipo de conexión
#define duracionCarretera(distancia) (distancia / VELOCIDADCARRETERA)
#define duracionAutopista(distancia) (distancia / VELOCIDADAUTOPISTA)
#define duracion(distancia, tipoDeConexion) (tipoDeConexion == 'C' ? duracionCarretera(distancia) : tipoDeConexion == 'A' ? duracionAutopista(distancia) : 0)

// ---- PROGRAMA PRINCIPAL ----


void prim(grafo G)
{
    int numArcos = 0;
    float minimo = FLT_MAX, duracionTrayecto = 0;

    register int numeroDeVertices = num_vertices(G);

    int tipoDeConexion[numeroDeVertices];

    for (int i = 0; i < numeroDeVertices; i++)
    {
        tipoDeConexion[i] = 0;
    }

    int *Selected = (int *) malloc(sizeof(int) * numeroDeVertices);

    for (int i = 0; i < numeroDeVertices; i++)
    {
        Selected[i] = 0;
    }
    Selected[0] = 1;


    while (numArcos < numeroDeVertices - 1)
    {
        minimo = FLT_MAX;
        int vx = 0;
        int vy = 0;
        for (int i = 0; i < numeroDeVertices; i++)
        {
            if (Selected[i] == 1)
            {
                for (int j = 0; j < numeroDeVertices; j++) //todo: La lógica es muy complicada, a lo mejor se puede simplificar
                {
                    if ((Selected[j] != 1) && ((distancia(G, i, j, 'C') != 0) || (distancia(G, i, j, 'A') != 0)))
                    {


                        if (distancia(G, i, j, 'C') != 0 && (minimo > duracion(calcularAdyacencia(G, i, j, 'C'), 'C')))
                        {
                            minimo = duracion(calcularAdyacencia(G, i, j, 'C'), 'C');
                            tipoDeConexion[i] = 'C';
                            vx = i;
                            vy = j;
                        }

                        if ((distancia(G, i, j, 'A') != 0) && (minimo > duracion(calcularAdyacencia(G, i, j, 'A'), 'A')))
                        {
                            minimo = duracion(calcularAdyacencia(G, i, j, 'A'), 'A');
                            tipoDeConexion[i] = 'A';
                            vx = i;
                            vy = j;
                        }

                    }
                }
            }
        }
        Selected[vy] = 1;
        numArcos++;
        if (tipoDeConexion[vx] == 'C')
        {
            printf("%10s -- %10s : %10.2f\n", array_vertices(G)[vx].nombre, array_vertices(G)[vy].nombre, duracion((calcularAdyacencia(G, vx, vy, 'C')), 'C'));
            duracionTrayecto += duracionCarretera(calcularAdyacencia(G, vx, vy, 'C'));
        } else if (tipoDeConexion[vx] == 'A')
        {
            printf("%10s == %10s : %10.2f\n", array_vertices(G)[vx].nombre, array_vertices(G)[vy].nombre, duracion(calcularAdyacencia(G, vx, vy, 'A'), 'A'));
            duracionTrayecto += duracionAutopista(calcularAdyacencia(G, vx, vy, 'A'));
        }
    }

    printf("Tiempo del arbol de expansión de coste mínimo = %.2f horas\n", duracionTrayecto);
    free(Selected);
}
// VERSION 8. En principio, funciona. Falta probarlo con más grafos
// Esta es la versión que existe en el repositorio de github
