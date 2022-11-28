#include <stdio.h>
#include <math.h>

#define bool _Bool
#define true 1
#define false 0

bool esPar(int num);

int main()
{
    float sumaTotal = 0;
    
    for(int i=0;i<1000000;i++)
    {
        if(esPar(i))
        {
            sumaTotal += cos(i);
        }
    }
    printf("%f\n",sumaTotal);
    return 0;
}

bool esPar(int num)
{
    return num%2==0;
}
