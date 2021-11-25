/*!
 * @file main.c
 * @author Marcelo Fort Muñoz
 * @brief Lee de consola y reproduce el archivo leído(tenga o no extensión)
 * @bug Ninguno, mi programa es perfecto
 */
 // Este .c es doxygen-friendly
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
//#include <string.h>

/*!
 * @def VERDADERO
 * @brief Valor para booleanos en 1
 */

/*!
* @def FALSO
* @brief Valor para booleanos en 0
*/

/*!
* @struct archivo
 * @brief Estructura que contiene la información del archivo(Ver boletín)

*/
#define VERDADERO 1

#define FALSO 0
//char comando[]="start";

struct archivo
{
    /*!
     * @var char nombre
     * @brief nombre del archivo
     */
    char nombre[255];
    /*!
    * @var char extension
    * @brief extension del archivo
    */
    char  extension[12];
};

int main(int numargs, char* args[])
{

    //char comandor[255];
    bool flag=FALSO;
    int i = 0;
    int r=1;
    int v;
    v=0;

    printf("En proceso...");
    struct archivo elarchivo;
 if(numargs==1)flag=VERDADERO;

    while(!flag)
    {
        if(r==1)
        {
           if( (args[1][i])!='.' )
           {
                elarchivo.nombre[i] = args[1][i];

           }
            if( (args[1][i])=='.' || (args[1][i])=='\000')
            {
                elarchivo.nombre[i]='\0';
                //system("pause");
                r=2;
           }
        }

        if( r==2 /*& cc==1*/)
        {

            if( args[1][i]=='.')
            {
                //printf("%c",args[1][i]);
                //system("pause");
            }else if( args[1][i]!='.' && args[1][i]!=' ')
            {

                elarchivo.extension[v] = args[1][i];
                v+=1;
            }
            if(args[1][i]=='\0')
            {
                elarchivo.extension[v] = '\0';
                flag = VERDADERO;
            }
        }

        i+=1;

    }

    if(numargs==1)
    {
        printf("\nERROR, Faltan argumentos\n");
        system("pause");
    }
    else if(numargs==2)
    {
/*
        printf("\n%s\n",comando);
        system("pause");
        strcat(comando," ");
        strcat(comando,elarchivo.nombre);
        printf("%s",comando);
        system("pause");
        strcat(comando,".");
        printf("%s",comando);
        system("pause");
        strcat(comando,elarchivo.extension);
        printf("%s",comando);
        system("pause");
*/
        system("cls");
        if( elarchivo.extension[0]!='\000' )
        {
            printf("%s.%s",elarchivo.nombre,elarchivo.extension);
        }
        if( elarchivo.extension[0]=='\000' )
        {
            printf("%s",elarchivo.nombre);
        }
        printf("\n");
       // system(comando);
        system("pause");

    }
    return 0;
}

