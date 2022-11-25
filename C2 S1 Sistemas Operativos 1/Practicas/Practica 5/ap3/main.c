# include <stdio.h>
#include <unistd.h>
#include <stdlib.h>


int main()
{
    printf("mi pid es: %i\n", getpid());
    char v[25];
    char *mi_str = NULL;
    printf("mi_str está en %p\n", mi_str);
    printf("continuar: ");
    scanf("%s", v);
    mi_str = (char *) malloc(400000000 * sizeof(char));
    if (mi_str == NULL)
    {
        printf("Fallo en el malloc\n");
        exit(-1);
    }
    printf("mi_str está en %p\n", mi_str);
    printf("continuar: ");
    scanf("%s", v);
    free(mi_str);
    
    printf(" Después del free\n");
    printf("mi_str está en %p\n", mi_str);
    printf("continuar: ");
    scanf("%s", v);
    mi_str = (char *) malloc(600000000 * sizeof(char));
    printf("mi_str está en %p\n", mi_str);
    
    printf("continuar: ");
    scanf("%s", v);
    free(mi_str);
    printf("mi_str está en %p\n", mi_str);
    printf("continuar: ");
    scanf("%s", v);
    
    return 0;
}