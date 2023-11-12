/**
 * @file grafo.c
 * @Author Marcelo Fort Muñoz y Profesores de la asinatura A.E.D. (ETSE-USC)
 * @date 2023
 * @brief Implementación del TAD grafo
 *
 * Este TAD representa un grafo no dirigido ponderado
 * con un máximo de MAXVERTICES vértices.
 *
 * @see grafo.h
 */

#include "grafo.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

/////////////////////////////////////////////////////////// TIPOS DE DATOS

// Estructura privada
struct tipografo
{
    int N; //número de vértices del grafo
    tipovertice VERTICES[MAXVERTICES]; //vector de vértices

    double ADYACENCIA_CARRETERA[MAXVERTICES][MAXVERTICES]; //matriz de adyacencia para conexiones por carretera
    double ADYACENCIA_AUTOPISTA[MAXVERTICES][MAXVERTICES]; //matriz de adyacencia para conexiones por autopista
};

//////////////////////////////////////////////////////////////// FUNCIONES

// HAY QUE MODIFICAR ESTA FUNCIÓN SI SE CAMBIA EL TIPO DE DATO tipovertice
/* 
 * Esta función devuelve 0 si los dos nodos son iguales
 * -1 si V1 está antes de V2 o 1 en otro caso.
 */
int _comparar_vertices(tipovertice V1, tipovertice V2)
{
    return strcmp(V1.nombre, V2.nombre);
}

//Creación del grafo con 0 nodos
void crear_grafo(grafo *G)
{
    *G = (struct tipografo *) malloc(sizeof(struct tipografo));
    (*G)->N = 0;
}

//Devuelve la posición del vértice Vert en el vector VERTICES del grafo G
//Si devuelve -1 es porque no encontró el vértice
int posicion(grafo G, tipovertice V)
{
    int contador = 0;
    //comparo V con todos los vertices almacenados en VERTICES 
    while (contador < G->N)
    {
        //if (G->VERTICES[contador]==V)  //encontré la posicion de V
        if (_comparar_vertices(G->VERTICES[contador], V) == 0)
        {
            return contador;
        }
        contador++;
    }
    return -1;
}

//Devuelve 1 si el grafo G existe y 0 en caso contrario
int existe(grafo G)
{
    return (G != NULL);
}

//Devuelve 1 si el vértice Vert existe en el grafo G
int existe_vertice(grafo G, tipovertice V)
{
    return (posicion(G, V) >= 0);
}

//todo: modificado
//Inserta un vértice en el grafo, devuelve -1 si no ha podido insertarlo por estar el grafo lleno
int insertar_vertice(grafo *G, tipovertice Vert)
{
    int i;
    if ((*G)->N == MAXVERTICES)
    {
        // Se ha llegado al maximo numero de vertices
        return -1;
    }

    (*G)->N++;
    (*G)->VERTICES[((*G)->N) - 1] = Vert;
    for (i = 0; i < (*G)->N; i++)
    {
        (*G)->ADYACENCIA_AUTOPISTA[i][((*G)->N) - 1] = 0;
        (*G)->ADYACENCIA_AUTOPISTA[((*G)->N) - 1][i] = 0;
        (*G)->ADYACENCIA_CARRETERA[i][((*G)->N) - 1] = 0;
        (*G)->ADYACENCIA_CARRETERA[((*G)->N) - 1][i] = 0;
    }
    return (*G)->N - 1;
}

//Borra un vértice del grafo
void borrar_vertice(grafo *G, tipovertice Vert)
{
    int F, C, P, N = (*G)->N;
    P = posicion(*G, Vert);
    if (P == -1)
    {
        return;
    }
    //if (P >= 0 && P < (*G)->N) {
    for (F = P; F < N - 1; F++)
    {
        (*G)->VERTICES[F] = (*G)->VERTICES[F + 1];
    }
    for (C = P; C < N - 1; C++)
    {
        for (F = 0; F < N; F++)
        {
            (*G)->ADYACENCIA_AUTOPISTA[F][C] = (*G)->ADYACENCIA_AUTOPISTA[F][C + 1];
            (*G)->ADYACENCIA_CARRETERA[F][C] = (*G)->ADYACENCIA_CARRETERA[F][C + 1];
        }
    }
    for (F = P; F < N - 1; F++)
    {
        for (C = 0; C < N; C++)
        {
//            (*G)->A[F][C] = (*G)->A[F + 1][C];
            (*G)->ADYACENCIA_AUTOPISTA[F][C] = (*G)->ADYACENCIA_AUTOPISTA[F + 1][C];
            (*G)->ADYACENCIA_CARRETERA[F][C] = (*G)->ADYACENCIA_CARRETERA[F + 1][C];
        }

    }
    (*G)->N--;
}

//todo: hay que modificar aquí?
//Crea el arco de relación entre VERTICES(pos1) y VERTICES(pos2)
void crear_arco(grafo *G, int pos1, int pos2, double valor, enum TipoVia tipoVia)
{
    switch(tipoVia)
    {
        case CARRETERA:
            (*G)->ADYACENCIA_CARRETERA[pos1][pos2] = valor;
            (*G)->ADYACENCIA_CARRETERA[pos2][pos1] = valor;
            break;
        case AUTOPISTA:
            (*G)->ADYACENCIA_AUTOPISTA[pos2][pos1] = valor;
            (*G)->ADYACENCIA_AUTOPISTA[pos1][pos2] = valor;
            break;
        default:
            printf("[ERROR] crear_arco --> TipoVia desconocida: No ha sido posible crear el arco\n");
    }
}

//todo: hay que modificar aquí?
//Borra el arco de relación entre VERTICES(pos1) y VERTICES(pos2)
void borrar_arco(grafo *G, int pos1, int pos2, enum TipoVia tipoVia)
{
    switch(tipoVia)
    {
        case CARRETERA:
            (*G)->ADYACENCIA_CARRETERA[pos1][pos2] = 0;
            (*G)->ADYACENCIA_CARRETERA[pos2][pos1] = 0;
            break;
        case AUTOPISTA:
            (*G)->ADYACENCIA_AUTOPISTA[pos1][pos2] = 0;
            (*G)->ADYACENCIA_AUTOPISTA[pos2][pos1] = 0;
            break;
        default:
            printf("[ERROR] borrar_arco --> TipoVia desconocida: No ha sido posible borrar el arco\n");
    }
}

//Devuelve la distancia entre las poblaciones VERTICES(pos1) y VERTICES(pos2) si son vértices adyacentes. En caso contrario devuelve 0.
double distancia(grafo G, int pos1, int pos2, enum TipoVia tipoVia)
{
    switch(tipoVia)
    {
        case CARRETERA:
            return G->ADYACENCIA_CARRETERA[pos1][pos2];
        case AUTOPISTA:
            return G->ADYACENCIA_AUTOPISTA[pos1][pos2];
        default:
            printf("[ERROR] distancia --> TipoVia desconocida: No ha sido posible calcular la adyacencia\n");
            return INFINITY;
    }
}


//Destruye el grafo
void borrar_grafo(grafo *G)
{
    free(*G);
    *G = NULL;
}

//Devuelve el número de vértices del grafo G
int num_vertices(grafo G)
{
    return G->N;
}

//Devuelve el vector de vértices VERTICES del grafo G
tipovertice *array_vertices(grafo G)
{
    return G->VERTICES;
}



