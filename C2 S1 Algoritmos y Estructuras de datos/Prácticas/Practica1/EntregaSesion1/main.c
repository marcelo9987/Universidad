/* Practica 1: Prueba de manejo de Arboles Binarios  */
#include <stdlib.h>
#include <stdio.h>

#include "abin.h"
#include "recorridos.h"
#include "funcionesArboles.h"

int main(int argc, char **argv)
{

    abin Arbol, aux;

    //Creo el Arbol
    crear(&Arbol);
    fprintf(stdout, "Arbol creado\n");

    // El primero sera la raiz
    insizq(&Arbol, 'J');

    //Insertamos un nodo a la derecha de la raíz
    insder(&Arbol, 'M');

    //Para insertar un nodo a la derecha de M, nos movemos a la derecha de la raíz
    aux = der(Arbol);

    //Y ahora insertamos el nodo a la derecha de M
    insder(&aux, 'W');

    //Insertamos un nodo a la izquierda de M
    insizq(&aux, 'K');

    //Insertamos un nodo a la izquierda de la raíz
    insizq(&Arbol, 'F');


    //Insertamos un nodo a la izquierda de F
    //Para eso tenemos que movernos a la izquierda de la raíz
    aux = izq(Arbol);

    //Y ahora insertamos el nodo a la izquierda de F
    insizq(&aux, 'D');

    //Insertamos un nodo a la derecha de F
    insder(&aux, 'G');


    //Para insertar un nodo a la derecha de G, nos movemos a la derecha de F, que es la izquierda de J
    aux = der(izq(Arbol));

    //Y ahora insertamos el nodo a la derecha de G
    insder(&aux, 'H');


    //Insertamos un nodo a la izquierda de D
    //Para eso tenemos que ir dos veces a la izquierda de la raíz
    aux = izq(izq(Arbol));
    insizq(&aux, 'B');

    //Insertamos un nodo a la derecha de D
    //Para eso podemos movernos a la derecha de aux
    insder(&aux, 'E');

    //Imprimimos la altura del árbol final
    printf("Altura de arbol: %d\n", AlturaArbol(Arbol));


    //Imprimo los elementos del arbol mediante el recorrido inorden no recursivo
    printf("Inorden no recursivo (usa pilas): \n");
    inordenNR(Arbol);

    // INICIO de la parte basica

//    aux = izq(Arbol);
//    supder(&aux);
//    fprintf(stdout, "\nSubarbol derecho de F destruido\n");

    // FIN de la parte basica

    //INICIO de la ampliacion
    char letraBuscar;
    fprintf(stdout, "\nIntroduzca la letra a buscar: ");
    fscanf(stdin, "%c", &letraBuscar);


    // Busco el nodo que contiene la letra introducida
    buscar(Arbol, letraBuscar, &aux);
    if (!esVacio(aux))
    {
        //Destruyo el subarbol derecho del nodo encontrado
        supder(&aux);
        fprintf(stdout, "\nSubarbol derecho de %c destruido\n", letraBuscar);
    } else
    {
        fprintf(stdout, "\nNo se ha encontrado el nodo de %c\n", letraBuscar);
    }

    // FIN de la ampliacion

    //imprimo el arbol en inorden recursivo
    printf("Inorden (IRD): \n");
    inorden(Arbol);

    //procedo a listar la altura del arbol
    printf("\nAltura de arbol: %d\n", AlturaArbol(Arbol));
    //Nº. de nodos del arbol
    printf("Nº. de nodos del arbol: %d\n", NumeroNodos(Arbol));

    // Liberamos memoria asociada al arbol:
    destruir(&Arbol);

    return (EXIT_SUCCESS);
}
