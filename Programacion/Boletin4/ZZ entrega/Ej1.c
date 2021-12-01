#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <locale.h>

int main() {
    int pera = rand() % 100;
    int *ciberpera;
    float manzana = rand() % 100;
    float *cibermanzana;
    char kiwi = '2';
    setlocale(LC_ALL, "Spanish");
    ciberpera = &pera;
    cibermanzana = &manzana;
    wprintf(L"\nLa dirección asociada a pera es:                0x%p y su valor es: %i", &pera, pera);
    wprintf(L"\nLa dirección asociada a manzana es:             0x%p y su valor es: %f", &manzana, manzana);
    wprintf(L"\nLa dirección asociada a kiwi es:                0x%p y su valor es: %c", &kiwi, kiwi);
    printf("\n\n");
    wprintf(L"\nLa variable ciberpera apunta a la dirección:    0x%p y su contenido es: %i", ciberpera, *ciberpera);
    wprintf(L"\nLa variable cibermanzana apunta a la dirección: 0x%p y su contenido es: %f", cibermanzana, *cibermanzana);
    printf("\n\n");
    ciberpera = &manzana;
    cibermanzana = &pera;
    wprintf(L"\nLa variable ciberpera apunta a la dirección:    0x%p y su contenido es: %i", ciberpera, *ciberpera);
    wprintf(L"\nLa variable cibermanzana apunta a la dirección: 0x%p y su contenido es: %f", cibermanzana, *cibermanzana);
    printf("\n");
    ciberpera++;
    cibermanzana++;
    wprintf(L"\nLa variable ciberpera apunta a la dirección:    0x%p y su contenido es: %i", ciberpera, *ciberpera);
    wprintf(L"\nLa variable cibermanzana apunta a la dirección: 0x%p y su contenido es: %f", cibermanzana, *cibermanzana);
    printf("\n");
    system("pause");
    return 0;
}
