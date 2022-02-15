#ifndef P1_V0_VECTORDINAMICO_H
#define P1_V0_VECTORDINAMICO_H

/*Tipo de datos de los elementos del vector*/
typedef float TELEMENTO;

/*Tipo opaco, los detalles de implementación están ocultos al usuario*/
typedef void* vectorD;

/* Función Crear: asigna memoria y devuelve la asignación al vector.
 * Recibe v por referencia para devolver al programa principal la dirección
 * de memoria reservada por este procedimiento*/
void crear(vectorD *v,short longitud);

/* Función asignar: Llena una posición del vector con un valor.
 * Recibe una copia de la dirección de memoria reservada para el vector v
 */
void asignar(vectorD *v,short posicion,TELEMENTO valor);
#endif //P1_V0_VECTORDINAMICO_H
