#include<stdlib.h>
#include<stdio.h>
#include "config.h"

/*Se vuelve a definir el tipo de datos que contiene el vector*/
typedef int TELEMENTO;

/*Implementación del TAD vectorD*/
typedef struct
{
    TELEMENTO* datos;   /*valores del vector*/
    short tam;          /*tamaño del vector*/
} STVECTOR; /*definición del tipo de datos estructura*/
typedef STVECTOR* vectorD;/*puntero a estructura*/

/*Funciones con manipulación de datos*/

/*Función crear: asigna memoria y devuelve la asignación al vector*/
void crear(vectorD* vector, short longitud)
{
    short i;
    
    *vector = (vectorD) malloc(sizeof(STVECTOR));
    if (*vector == NULL)
    {
        fprintf(STDERR, "ERR, malloc: 001");
        exit(1);
    }
    
    (*vector)->datos = (TELEMENTO*) malloc(longitud * sizeof(TELEMENTO));
    if ((*vector)->datos == NULL)
    {
        fprintf(STDERR, "ERR, malloc: 002");
        exit(2);
    }
    
    (*vector)->tam = longitud;
    for (i = 0; i < longitud; i++)
    {
        /*Inicialización a 0 de las componentes del vector*/
        *((*vector)->datos + i) = 0;
    }
}

/*Función asignar: Asigna un valor a la posición del vector*/
void asignar(vectorD* vector, short pos, TELEMENTO valor)
{
    if (vector == NULL || (*vector)==NULL)
    {
        fprintf(STDERR, "WARNING :: asignar(): NO vector TO WRITE 014\n");
        
    } else if (pos < 0 || pos >= (*vector)->tam)
    {
        fprintf(STDERR, "WARNING 015 :: asignar(): pos OUT OF BOUNDS in pos %i. Valid positions: from 0 to %i\n", pos, (*vector)->tam);
        
    } else
    {
        (*vector)->datos[pos] = valor;
        //*((*v)->datos + posicion) = valor;
        
    }
}

void liberar(vectorD* vector)
{
    if (*vector != NULL)
    {
        if ((*vector)->datos != NULL)
        {
            free((*vector)->datos);
        }
        free(*vector);
        *vector = NULL;
    } else
    {
        fprintf(STDERR, "INFO :: liberar(): NO vector TO FREE 003\n");
    }
}

TELEMENTO recuperar(vectorD vector, short pos)
{
    if (vector == NULL)
    {
        fprintf(STDERR, "WARNING :: recuperar(): NO vector TO READ 004\n");
        return 0;
    } else if (pos < 0 || pos >= vector->tam)
    {
        fprintf(STDERR, "WARNING 005 :: recuperar(): pos OUT OF BOUNDS in pos %i. Valid positions: from 0 to %i\n", pos, vector->tam);
        
        return 0;
    } else
    {
        TELEMENTO valor;
        valor = vector->datos[pos];
        return valor;
    }
}

short longitudVector(vectorD vector)
{
    if (vector == NULL)
    {
        fprintf(STDERR, "\nWARNING :: longitudVector(): NO SUCH vector 006\n");
        return 0;
    } else
    {
        return vector->tam;
    }
    
}
