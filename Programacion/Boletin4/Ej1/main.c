#include <stdio.h>
#include <stdlib.h>
#include "../LibreriaBol4/library.h"//de momento no se usa, pero como proyecto planeo que esta librería se use lo máximo posible
int main() {
    int pera = -1;
    float manzana=5;
    char kiwi = '2';
    int* p = &pera;
    hello();
    printf("El puntero de pera es: %p y su valor es: %i",&p,pera);
    printf("\n El puntero de manzana es:%p y su valor es: %f",(void*)&manzana,*(&manzana));
    printf("\n El puntero de kiwi es: %p y su valor es: %c",(void*)&kiwi,kiwi);
    printf("\n");
    system("pause");
    return 0;
}
