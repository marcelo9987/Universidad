#include   <stdio.h>
#include   <stdbool.h>
#include   <stdlib.h>


//parece ser que no se meten los caracteres de uno en uno al asignar =""

int main()
{
    
    char* reprueba;
    char** prueba;
    char* prueba2;
    prueba = (char**) malloc(2*sizeof(char*));
    prueba[0]=(char*) malloc(40*sizeof(char));
    prueba[1]=(char*) malloc(40*sizeof(char));
    scanf("%s",prueba[1]);
  
    int r =0;
    while(true)
    {
        if(prueba[1][r]=='.')
        {
            printf("%c",prueba[1][r]);
            prueba[1][r] = '\0';
            break;
        }
        r++;
    }
    reprueba = &prueba[1][0];
    
    printf("%s",reprueba);
    
  
    return 0;
}
