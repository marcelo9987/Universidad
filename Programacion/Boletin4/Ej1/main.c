#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
int main() {
    int pera = rand()%100;
    int* ciberpera;
    float manzana=rand()%100;
    float* cibermanzana;
    char kiwi = '2';
    ciberpera=&pera;
    cibermanzana=&manzana;
    printf("\nEl puntero de pera es: %p y su valor es: %i",&pera,pera);
    printf("\nEl puntero de manzana es:%p y su valor es: %f",&manzana,manzana);
    printf("\nEl puntero de kiwi es: %p y su valor es: %c",&kiwi,kiwi);
    printf("\n\n");
    printf("\nEl puntero de pera es: %p y su valor es: %i",ciberpera,*ciberpera);
    printf("\nEl puntero de manzana es:%p y su valor es: %f",cibermanzana,*cibermanzana);
    printf("\n\n");
    ciberpera=&manzana;
    cibermanzana=&pera;
    printf("\nEl puntero de pera es: %p y su valor es: %i",ciberpera,*ciberpera);
    printf("\nEl puntero de manzana es:%p y su valor es: %f",cibermanzana,*cibermanzana);
    printf("\n");

    system("pause");
    return 0;
}
