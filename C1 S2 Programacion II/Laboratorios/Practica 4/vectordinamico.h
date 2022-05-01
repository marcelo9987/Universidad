#ifndef VECTORDINAMICO_H
#define VECTORDINAMICO_H

/*Tipo de datos de los elementos del vector*/
typedef int TELEMENTO;

/*Tipo opaco, los detalles de implementación están ocultos al usuario*/
typedef void *vectorD;

/* Función Crear: asigna memoria y devuelve la asignación al vector.
 * Recibe v por referencia para devolver al programa principal la dirección
 * de memoria reservada por este procedimiento*/
void crear(vectorD *vector, short longitud);

/* Función asignar: Llena una posición del vector con un valor.
 * Recibe una copia de la dirección de memoria reservada para el vector v
 */
void asignar(vectorD *vector, short pos, TELEMENTO valor);

void liberar(vectorD* vector);

TELEMENTO recuperar(vectorD vector,short pos);

short longitudVector(vectorD vector);

#endif //VECTORDINAMICO_H
