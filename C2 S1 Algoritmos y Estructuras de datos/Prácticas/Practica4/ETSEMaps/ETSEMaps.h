/**
 * @file   ETSEMaps.h
 * @Author Marcelo Fort Muñoz y Profesores de la asinatura A.E.D. (ETSE-USC)
 * @date 2023
 * @brief Librería de funciones para el TAD Grafo (cabecera)
 * @version 3.0 (Tras la actualización de requisitos)
 */

#ifndef ETSEMAPS_H
#define ETSEMAPS_H

#include <stdio.h>
#include <stdbool.h>

#include "grafo.h"

#define PRECIOPORKMCARRETERA 0.01
#define PRECIOPORKMAUTOPISTA 0.07

#define VELOCIDADCARRETERA 70
#define VELOCIDADAUTOPISTA 120

#define NOMBRE_ARCHIVO_MAPA_NOROESTE "mapaNoroeste.grafo"


enum TipoOptimizacionWarsall {
    DISTANCIA, TIEMPO, DINERO
};

/**
 * Lee un archivo y lo almacena en un grafo
 * @param nombreArchivo  nombre del archivo a leer.
 * @param G Puntero al grafo donde se almacenará el archivo.
 * @return true si se ha leído correctamente, false en caso contrario.
 */
bool leerArchivo(const char *nombreArchivo, grafo *G);

/**
 * Guarda un grafo en un archivo
 * @param nombreArchivo nombre del archivo donde se guardará el grafo.
 * @param G grafo a guardar.
 * @return true si se ha guardado correctamente, false en caso contrario.
 */
bool guardarArchivo(const char *nombreArchivo, grafo G);

/**
 * Calcula el arból de expansión mínima de un grafo
 * @param G grafo a calcular el árbol de expansión mínima.
 * @return el coste del árbol de expansión mínima.
 */
double prim(grafo G);

/**
 * Optimiza el grafo con el algoritmo de Floyd-Warshall en base al parámetro tipoOptimizacionWarsall
 * @param G grafo a optimizar.
 * @param tipoOptimizacionWarsall tipo de optimización a realizar. Puede ser DISTANCIA, TIEMPO o DINERO.
 */
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


#endif    /* ETSEMAPS_H */

