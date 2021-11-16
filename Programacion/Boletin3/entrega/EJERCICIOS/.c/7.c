/*
 * Programador: Marcelo Fort Muñoz
 * Descripción:
 *
 *
 *
 */
#define VERDADERO 1
#define FALSO 0

#include <stdio.h>
#include <locale.h>
#include <stdbool.h>

void limpieza(char linea[]);//cambia ",/ por espacios

int main() {
    bool primeraVuelta = VERDADERO;//determina si está en la primera línea
    FILE *csv;
    FILE *nue;
    char entrada[200] = {};//, salida[200] = {};


    setlocale(LC_ALL, "Spanish");
    csv = fopen("weatherdata-420-72.csv", "r");
    nue = fopen("weatherdata-420-72.txt", "w");
    if (csv == NULL) {
        printf("Error de Lectura");
    } else
    {
        do {

            if (primeraVuelta == VERDADERO)
            {
                fgets(entrada, 200, csv);
                getc(csv);
            }else
            {

              fgets(entrada, 200, csv);
              getc(csv);


                 limpieza(entrada);
                 fprintf(nue,entrada);

            }
            primeraVuelta = FALSO;

        }while(!feof(csv));
    }

   /* for (int i = 0; i < 200; i++) {
        printf("%c", entrada[i]);
    }*/

    fclose(csv);
    fclose(nue);
    return 0;
}

void limpieza(char linea[200])
{
    for(int i=0;i<200;i++)
    {
        if(linea[i] ==',')
        {
            linea[i]= ' ';
        }
        if(linea[i] =='/')
        {
            linea[i]= ' ';
        }
        if(linea[i] =='"')
        {
            linea[i]= ' ';
        }
    }
}