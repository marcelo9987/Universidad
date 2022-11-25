# include <stdio.h>
#include <unistd.h>

void f1(int param)
{
    int num = param;
    printf("[%i] Parámetro en: %p Var en: %p\n",getpid(),&param,&num);

}
void f2(int param)
{
    int num = param;
    printf("[%i] Parámetro en: %p Var en: %p\n",getpid(),&param,&num);
}

int main()
{
    printf("f1 en: %p\n",f1);
    f1(8);
    printf("f2 en: %p\n",f2);
    f2(9);
    scanf("%i",NULL);
    
    return 0;
}