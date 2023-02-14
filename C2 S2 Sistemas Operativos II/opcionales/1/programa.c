#include <stdio.h>
#include <pthread.h>
//#define T 15
//#define M 5000

double suma =0;
int M,T;

void sum(int hilo)
{
        int j;

        for(j=hilo;j<=M;j+=T)
        {
                suma = suma + j;
        }
}

int main(int argc,char* argv[])
{
        if(argc<3){return(-1);}
        M=atoi(argv[1]);
        T=atoi(argv[2]);

        pthread_t hilos[T];
        for(int indice_creacionHilos =0;indice_creacionHilos<T;indice_creacionHilos++)
        {
          pthread_create(&hilos[indice_creacionHilos],NULL,sum,indice_creacionHilos);
        }

       for(int indice_creacionHilos =0;indice_creacionHilos<T;indice_creacionHilos++)
        {
          pthread_join(hilos[indice_creacionHilos],NULL); 
        }


        fprintf(stdout,"%i, %i, %lf, [%s]\n", M, T, suma,(suma-(M*(M+1))/2 ==0)?"OK":"Error");
        return(0);
}
