#ifndef FUNCIONESARBOLES_H
#define FUNCIONESARBOLES_H

//Función que calcula la altura del árbol A
// @param A Arbol binario
int AlturaArbol(abin A);

//Función que calcula el número de nodos de un árbol A
// @param A Arbol binario
int NumeroNodos(abin A);

//Función que suma los elementos de un árbol A
// @param A Arbol binario
int SumaElementos(abin A);

/**
 * Función que busca un un nodo en el árbol
 * @param A Arbol binario en el que buscar
 * @param inf Información a buscar en el árbol
 * @param aux Arbol auxiliar para almacenar el nodo encontrado
 */
void buscar(abin A, tipoelem inf, abin* aux);

#endif /* FUNCIONESARBOLES_H */
