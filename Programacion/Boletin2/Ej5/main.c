#include <stdio.h>
//#include <stdlib.h>
#include <locale.h>
#include <string.h>
void medirpalabra(char abc[30]);
int longitud,consonantes,vocales;
int main() {
    char palabra[30];
    setlocale(LC_ALL,"Spanish");
    printf("Introduzca una palabra: ");
    scanf("%s",&palabra);
    medirpalabra(palabra);
    printf("\n Vocales: %i",vocales);
    printf("\n Consonantes: %i",consonantes);
    return 0;
}
void medirpalabra(char abc[30])
{
    vocales=0;
    consonantes=0;
    int fin = 0;
    int a=0;
        longitud=strlen(abc)-1;

    while (fin==0)
    {

        switch (abc[a])
        {
            case 'a':
            case 'e':
            case 'i':
            case 'o':
            case 'u':
                vocales+=1;
                break;
            default:
                consonantes+=1;
                break;
        }
        if(a==longitud)
        {
            fin = 1;
        }else
        {
            a = a + 1;
        }
    }
}