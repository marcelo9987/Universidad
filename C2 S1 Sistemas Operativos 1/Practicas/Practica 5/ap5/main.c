#include <stdio.h>
#include <math.h>
#include <unistd.h>
#include <string.h>

#define bool _Bool
#define true 1
#define false 0


#define esperar()
//#define esperar() \
//{                 \
//    printf("\nContinuar: ");\
//    while(getchar()!='\n');\
//}

//#define procmap(numUso)
#define procmap(numUso) _procmap(numUso)

void _procmap(int numUso)
{
    char nombreArchivoDestino[20];
    sprintf(nombreArchivoDestino, "%s%i.mem", "maps", numUso);
    FILE* archivo = fopen(nombreArchivoDestino, "w+");
    
    char nombreArchivo[0xfff];
    sprintf(nombreArchivo, "%s%d%s", "/proc/", getpid(), "/maps");
    FILE* contenidosMapaMemoria;
    contenidosMapaMemoria = fopen(nombreArchivo, "r");
    int counter = 0;
    
    char buffer[300];
    while (1)
    {
        
        fgets(buffer, sizeof(buffer), contenidosMapaMemoria);
        if (feof(contenidosMapaMemoria))
        {
            break;
        }
        fprintf(archivo, "%s", buffer);
        
        ++counter;
    }
    printf("He leído %i líneas.\n", counter);
    fclose(archivo);
    fclose(contenidosMapaMemoria);
}

bool esPar(int num)
{
    return num%2==0;
}

int main(int argc,char* argv[])
{
    int numeroMemoria=0;
    printf("archivo: %s\n",argv[0]);
    if(strcmp(argv[0],"./main.dynamic")==0)
    {
        numeroMemoria = 60;
    }else if(strcmp(argv[0],"./main.static")==0)
    {
        numeroMemoria = 50;
    }
    procmap(numeroMemoria+0);
    
    float sumaTotal = 0;
    for(int i=0;i<1000000;i++)
    {
        if(esPar(i))
        {
            sumaTotal += cos(i);
        }
    }
    
    procmap(numeroMemoria+1);
    
    printf("%f\n",sumaTotal);
    return 0;
}


