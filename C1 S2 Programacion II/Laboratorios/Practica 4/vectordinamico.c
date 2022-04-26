#include<stdlib.h>
#include<stdio.h>

/*Se vuelve a definir el tipo de datos que contiene el vector*/
typedef int TELEMENTO;

/*Implementación del TAD vectorD*/
typedef struct
{
    TELEMENTO *datos;   /*valores del vector*/
    short tam;          /*tamaño del vector*/
} STVECTOR; /*definición del tipo de datos estructura*/
typedef STVECTOR *vectorD;/*puntero a estructura*/

/*Funciones con manipulación de datos*/

/*Función crear: asigna memoria y devuelve la asignación al vector*/
void crear(vectorD *v, short longitud)
{
    short i;

    *v = NULL;
    *v = (vectorD) malloc(sizeof(STVECTOR));
    if (*v == NULL)
    {
        printf("ERR, malloc: 001");
        exit(1);
    }

    (*v)->datos = NULL;
    (*v)->datos = (TELEMENTO *) malloc(longitud * sizeof(TELEMENTO));
    if ((*v)->datos == NULL)
    {
        printf("ERR, malloc: 002");
        exit(2);
    }

    (*v)->tam = longitud;
    for (i = 0; i < longitud; i++)
    {
        /*Inicialización a 0 de las componentes del vector*/
        *((*v)->datos + i) = 0;
    }
}

/*Función asignar: Asigna un valor a la posición del vector*/
void asignar(vectorD *v, short posicion, TELEMENTO valor)
{
    *((*v)->datos + posicion) = valor;

}


void liberar(vectorD *vector)
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
        printf("INFO :: liberar(): NO vector TO FREE 003\n");
    }
}

TELEMENTO recuperar(vectorD vector, short pos)
{
    if (vector == NULL)
    {
        printf("WARNING :: recuperar(): NO vector TO READ 004\n");
        return 0;
    } else if (pos < 0 || pos >= vector->tam)
    {
        printf("WARNING :: recuperar(): pos OUT OF BOUNDS 005\n");
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
        printf("\nWARNING :: longitudVector(): NO SUCH vector 006\n");
        return 0;
    } else
    {
        return vector->tam;
    }

}
