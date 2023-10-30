#include <stdio.h>
#include <stdlib.h>
#include "grafo.h"



//FUNCIONES DEL PROGRAMA DE PRUEBA DE GRAFOS

//Opción a del menú, introducir un vertice en el grafo

void introducir_vertice(grafo *G)
{
    tipovertice v1;
    printf("Introduce vertice: ");
    scanf("%s", v1.nombre);
    if (existe_vertice(*G, v1))
    {
        printf("Ese vertice ya esta en el grafo\n");
    } else
    {
        insertar_vertice(G, v1);
    }
}
//Opción b del menú, eliminar un vértice del grafo

void eliminar_vertice(grafo *G)
{
    tipovertice v1;
    printf("Introduce vertice: ");
    scanf("%d", &v1);
    if (existe_vertice(*G, v1))
    {
        borrar_vertice(G, v1);
    } else
    {
        printf("Ese vertice no existe en el grafo\n");
    }
}

//Opción c del menú, crear una relación entre dos vértices

void nuevo_arco(grafo *G)
{
    tipovertice v1, v2;
    //Insertamos una nueva relación pidiendo los datos al usuario controlando que existan los vértices
    printf("Nueva relacion vertice1-->vertice2\n");
    //Vértice origen del arco
    printf("Introduce vertice origen: ");
    scanf("%d", &v1);
    if (!existe_vertice(*G, v1))
    {
        printf("El vertice %d no existe en el grafo\n", v1);
        return;
    }
    //Vértice destino del arco
    printf("Introduce vertice destino: ");
    scanf("%d", &v2);
    if (!existe_vertice(*G, v2))
    {
        printf("El vertice %d no existe en el grafo\n", v2);
        return;
    }

    //todo: es aquí?
    char tipoDeConexion;
    printf("Introduce el tipo de conexion: ");
    scanf(" %c", &tipoDeConexion);
    if (tipoDeConexion != 'A' && tipoDeConexion != 'a' && tipoDeConexion != 'B' && tipoDeConexion != 'b')
    {
        printf("El tipo de conexion no es valido\n");
        return;
    }

    //todo: es aquí?
    int valorArco;
    printf("Introduce el valor del arco: ");
    scanf("%d", &valorArco);
    if (valorArco <= 0)
    {
        printf("El valor del arco no es valido\n");
        return;
    }

    //Creación del arco
    if (!son_adyacentes(*G, posicion(*G, v1), posicion(*G, v2), tipoDeConexion))
    {
        crear_arco(G, posicion(*G, v1), posicion(*G, v2), valorArco, tipoDeConexion);
    }
}

//todo: idem
//Opción d del menú, eliminar una relación entre dos vértices
void eliminar_arco(grafo *G)
{
    tipovertice v1, v2;
    //Eliminamos una relación pidiendo los datos al usuario controlando que existan los vértices
    printf("Eliminar relacion vertice1-->vertice2\n");
    //Vértice origen del arco
    printf("Introduce vertice origen: ");
    scanf("%d", &v1);
    if (!existe_vertice(*G, v1))
    {
        printf("El vertice %d no existe en el grafo\n", v1);
        return;
    }
    //Vértice destino del arco
    printf("Introduce vertice destino: ");
    scanf("%d", &v2);
    if (!existe_vertice(*G, v2))
    {
        printf("El vertice %d no existe en el grafo\n", v2);
        return;
    }

    char tipoDeConexion;
    printf("Introduce el tipo de conexion: ");
    scanf(" %c", &tipoDeConexion);

    // Eliminación del arco

    switch (tipoDeConexion)
    {
        case 'A':
        case 'a':
            if (son_adyacentes(*G, posicion(*G, v1), posicion(*G, v2), 'A'))
            {
                borrar_arco(G, posicion(*G, v1), posicion(*G, v2), 'A');
            }
            break;
        case 'C':
        case 'c':
            if (son_adyacentes(*G, posicion(*G, v1), posicion(*G, v2), 'C'))
            {
                borrar_arco(G, posicion(*G, v1), posicion(*G, v2), 'C');
            }
            break;
        default:
            printf("El tipo de conexion no es valido\n");
            return;
    }

}

//Opción i del menú, imprimir el grafo
//Función que imprime el grafo utilizando num_vertices para saber cuántos vértices tiene
//y array_vertices para recuperar el vector de vértices y recorrerlo

void imprimir_grafo(grafo G)
{
    tipovertice *VECTOR; //Para almacenar el vector de vértices del grafo
    int N; //número de vértices del grafo

    //Para recorrerla, simplemente vamos a recorrer la matriz de adyacencia
    N = num_vertices(G);
    VECTOR = array_vertices(G);

    int i, j;
    printf("El grafo actual es:\n");
    for (i = 0; i < N; i++)
    {
        //Imprimo el vértice
        printf("Vertice(%d): %d\n", i, VECTOR[i]);
        //Chequeo sus arcos
        for (j = 0; j < N; j++)
        {
            if (son_adyacentes(G, i, j, 'C'))
            {
                printf("\tHay una carretera de %d a %d con valor %d\n", VECTOR[i], VECTOR[j], calcularAdyacencia(G, i, j, 'C'));
            }
            if (son_adyacentes(G, i, j, 'A'))
            {
                printf("\tHay una autopista de %d a %d con valor %d\n", VECTOR[i], VECTOR[j], calcularAdyacencia(G, i, j, 'A'));
            }
        }
    }
}

