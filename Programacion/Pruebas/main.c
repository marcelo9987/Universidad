#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/*
void hacercosas(int vec1[],int elnum)
{
 //   int longitud = 0;
     int longitud = elnum;
    for (int t = 0; t<longitud;t++)
    {
        printf("\n %d",vec1[t]);
    }
}*/
int main()
{
    char memoria[60];
    FILE* prueba;
    prueba = fopen ("test.txt","r+");
          //fscanf(prueba, "%s", memoria);
    fgets(memoria, 27,prueba);
         //fscanf(prueba, "%s", memoria);
    printf("1 : %s", memoria );
          //fscanf(prueba, "%s", memoria);
          
    fgets(memoria, 27,prueba);
    printf("\n 2 : %s", memoria );

    fgets(memoria, 27,prueba);
          //fscanf(prueba, "%s", memoria);
    printf("\n 3 : %s", memoria );
    fclose(prueba);

   /* int cosas[]={1,3,5,7,9,2,4,6,8,0};
    int numel = sizeof(cosas)/sizeof(cosas[0]);
    hacercosas(cosas,numel);*/



    return 0;
}
