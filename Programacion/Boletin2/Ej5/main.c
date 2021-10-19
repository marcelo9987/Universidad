#include <stdio.h>
//#include <stdlib.h>
#include <locale.h>
#include <string.h>
void medirpalabra(char abc[30]);
int longitud,consonantes,vocales;
int ar,e,i,o,u;
int main() {
    char palabra[30];
    setlocale(LC_ALL,"Spanish");
    printf("Introduzca una palabra: ");
    scanf("%s",&palabra);
    medirpalabra(palabra);
    printf("\n Vocales: %i",vocales);
    printf("\n Consonantes: %i",consonantes);
    printf("\n A's: %i",ar);
    printf("\n e's: %i",e);
    printf("\n I's: %i",i);
    printf("\n O's: %i",o);
    printf("\n U's: %i",u);
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
            	ar+=1;
            	vocales +=1;
            	break;
            case 'e':
            	e+=1;
            	vocales +=1;
            	break;
            case 'i':
            	i+=1;
            	vocales +=1;
            	break;
            case 'o':
            	o+=1;
            	vocales +=1;
            	break;
            case 'u':
                vocales+=1;
                u=u+1;
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
