#include <stdio.h>
#include <stdlib.h>
#include "vectordinamico.h"

void leerDivisas(FILE* archivo);

int main()
{
    FILE* archivoDivisas;
    archivoDivisas =  fopen("../monedas.curr","rt");
    char seleccion[9];
    char sel = 'r';
    leerDivisas(archivoDivisas);
    while (sel != '1' && sel != '2')
    {
        //fflush(NULL);
        system("cls||clear");
        fprintf(stdout, "Modo de operación (Ilimitado 1 o Limitado 2): ");
        fscanf(stdin, "%c", &sel);
    }
    if(sel =='1')
    {
        fprintf(stdout,"ILIMITADO");
    
    }
    if(sel=='2')
    {
        fprintf(stdout,"LIMITADO");
    }
    fclose(archivoDivisas);
    return 0;
}

void leerDivisas(FILE* archivo/*,vectorD divisas[]*/)
{
    char* divisa =(char*) malloc(36*sizeof(char));
    fscanf(archivo,"%[^\n]",divisa);
    int nw = -7;
    int o = 0;
    while(nw!=1)
    {
        if(divisa[o] == '\0')
        {
            nw=1;
        }
        
        ++o;
    }
    
    realloc(divisa,o*sizeof(char));
}


int cambio(int x, int n, const int valor[n], int solucion[n])
{
    
    
    for (int i = 0; i < n; i++)
    {
        solucion[ i ] = 0;
    }
    int i = 0, suma = 0;
    
    while (suma < x && i < n)
    {
        if (suma + valor[ i ] <= x)
        {
            solucion[ i ]++;
            suma += valor[ i ];
        } else
            i++;
    }
    if (suma == x)
    {
        return 1;
    } else
    {
        for (int i = 0; i < n; i++) solucion[ i ] = 0;
        return 0;
    }
}