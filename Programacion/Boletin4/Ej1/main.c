#include <stdio.h>
#include <stdlib.h>
int main() {
    int pera = -1;
    int* ciberpera=&pera;
    float manzana=5;
    float* cibermanzana=&manzana;
    char kiwi = '2';
    
    printf("\nEl puntero de pera es: %p y su valor es: %i",&pera,pera);
    printf("\nEl puntero de manzana es:%p y su valor es: %f",&manzana,*(&manzana));
    printf("\nEl puntero de kiwi es: %p y su valor es: %c",&kiwi,kiwi);
    printf("\n\n");
    printf("\nEl puntero de pera es: %p y su valor es: %i",ciberpera,*ciberpera);
    printf("\nEl puntero de manzana es:%p y su valor es: %f",cibermanzana,*cibermanzana);
    printf("\n\n");
    cibermanzana=&pera;
    ciberpera=&manzana;
    printf("\nEl puntero de pera es: %p y su valor es: %i",ciberpera,*ciberpera);
    printf("\nEl puntero de manzana es:%p y su valor es: %f",cibermanzana,*cibermanzana);
    printf("\n");
    //Por que se obteñen valores distintos aos anteriores?
    //porque os punteros asignados non sin do mesmo tipo que a variable á que apuntan
    system("pause");
    return 0;
}
//é posibel distinguir o tipo de dato a partires do valor do enderezo impreso?
//no
//Se lle sumamos 1 a eses enderezos de memoria, que resultados obtemos e por que?
//0, porque no hay nada declarado en esa dirección de memoria

