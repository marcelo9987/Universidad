#include <stdio.h>
#include <unistd.h>



int i_arrayGlobal[6];
int i_varGlobal;

int main()
{
    char i;
    int i_varLocal;
    int i_arrayLocal[6];
    printf("pid: %d\n",getpid());
    printf("Main: %p",main);
    printf("varG: %p arrG: %p\n",&i_varGlobal,&i_arrayGlobal);
    printf("varL: %p arrL: %p",&i_varLocal,&i_arrayLocal);
    scanf("%s",&i);
    
    i_arrayLocal[2]=99;
    i_arrayGlobal[1]=8273678;
    i_varLocal=99;
    scanf("%s",&i);
    
    
    return 0;
}
