#include<stdlib.h>
#include<stdio.h>

/*Se vuelve a definir el tipo de datos que contiene el vector*/
typedef float TELEMENTO;

/*Implementación del TAD vectorD*/
typedef struct
{
    TELEMENTO *datos;/*valores del vector*/
    short tam;/*tamaño del vector*/
}STVECTOR;/*definición dek  tipo de datos estructura*/
typedef STVECTOR *vectorD;/*puntero a estructura*/

/*Funciones con manipulación de datos*/

/*Función crear: asigna memoria y devuelve la asignación al vector*/
void crear(vectorD *v,short longitud)
{
    *v = (vectorD) malloc(sizeof(STVECTOR));
    (*v)->datos = (TELEMENTO*) malloc(longitud* sizeof(TELEMENTO));
    (*v)->tam=longitud;
    for(short i =0;i<longitud;i++)
    {
        /*Inicialización a 0 de las componentes del vector*/
        *((*v)->datos+i)=0;
    }
}

/*Función asignar: Asigna un valor a la posición del vector*/
void asignar(vectorD *v, short posicion,TELEMENTO valor)
{
    *((*v)->datos+posicion)=valor;

}

