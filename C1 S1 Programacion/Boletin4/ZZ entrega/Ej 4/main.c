/*!
 * @file main.c
 * @brief Este programa pide por consola un nombre de archivo, procede a su lectura y volcado en pantalla del usuario
 * @author Marcelo Fort Muñoz
 */

#define EJECUCIONEXITOSA 0

#include   <stdio.h>
#include   <locale.h>
#include   <stdbool.h>
#include   <stdlib.h>
#include   <string.h>
//#include <math.h>

struct Archivo
{
    char *nombre;
    char *extension;
};

void abrirArchivo(struct Archivo *archivo);

int main(int argc, char *argv[])
{
    wprintf(L"-------- ---------- ------------ -----------\n");
    struct Archivo miArchivo;
    setlocale(LC_ALL, "Spanish");
    if (argc == 1)
    {
        wprintf(L"ERROR: Faltan argumentos.\n");
        wprintf(L"¿Ha introducido correctamente el nombre del archivo?\n");
    } else
    {
        int posUltimoPunto = -1;
        int pos;
        for (pos = 0; argv[1][pos] != '\0'; pos++)
        {
            if (argv[1][pos] == '.')
            {
                posUltimoPunto = pos;
            }
        }
        
        printf("param: [%s] ", argv[1]);
        wprintf(L"Ultimo punto: %i / Final de cadena: %i\n", posUltimoPunto, pos);
        
        miArchivo.nombre = &argv[1][0];
        if (pos == posUltimoPunto + 1)
        {
            miArchivo.extension = &argv[1][pos];
        } else if (posUltimoPunto != -1)
        {
            argv[1][posUltimoPunto] = '\0';
            miArchivo.extension = &argv[1][posUltimoPunto + 1];
        } else
        {
            miArchivo.extension = &argv[1][pos];
        }
        
        
        printf("Nombre: [%s] Extension: [%s]\n", miArchivo.nombre, miArchivo.extension);
        
        abrirArchivo(&miArchivo);
        
    }
    
    system("pause");
    return EJECUCIONEXITOSA;
}

void abrirArchivo(struct Archivo *archivo)
{
    int caracter;
    char *ruta = malloc(strlen(archivo->nombre) + strlen(archivo->extension) + 2);
    if (archivo->extension[0] == '\0')
    {
        strcpy(ruta, archivo->nombre);
    } else
    {
        sprintf(ruta, "%s.%s", archivo->nombre, archivo->extension);
    }
    
    printf("Ruta: [%s]\n", ruta);
    FILE *f = fopen(ruta, "r");
    if (f == NULL)
    {
        //printf("**** ");
        printf("**** Error intentando acceder al archivo \"%s\". Motivo: %s\n", ruta, strerror(errno));
        //putchar('\n');
    } else
    {
        printf("**** Contenido del archivo \"%s\":\n", ruta);
        do
        {
            caracter = fgetc(f);
            if (caracter != EOF)
            {
                putchar(caracter);
            }
        } while (caracter != EOF);
        printf("\n**** FIN ****\n");
        fclose(f);
    }
    
    free(ruta);
}