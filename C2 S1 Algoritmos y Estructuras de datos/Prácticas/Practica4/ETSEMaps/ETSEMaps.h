#ifndef FUNCIONES_H
#define FUNCIONES_H

#include <stdio.h>
#include "grafo.h"

#define PRECIOPORKMCARRETERA 0.01
#define PRECIOPORKMAUTOPISTA 0.07

#define VELOCIDADCARRETERA 70
#define VELOCIDADAUTOPISTA 120

enum TipoOptimizacionWarsall {
    DISTANCIA, TIEMPO, DINERO
};

int leerArchivo(FILE *archivoLectura, grafo *G);

double prim(grafo G);

void floydWarshall(grafo G, enum TipoOptimizacionWarsall tipoOptimizacionWarsall);

//FUNCIONES DEL PROGRAMA DE PRUEBA DE GRAFOS
//Opción a del menú, introducir un vertice en el grafo
void introducir_vertice(grafo *G);

//Opción b del menú, eliminar un vértice del grafo
void eliminar_vertice(grafo *G);

//Opción c del menú, crear una relación entre dos vértices
void nuevo_arco(grafo *G);

//Opción d del menú, eliminar una relación entre dos vértices
void eliminar_arco(grafo *G);

//Opción i del menú, imprimir el grafo
void imprimir_grafo(grafo G);


#endif	/* FUNCIONES_H */

