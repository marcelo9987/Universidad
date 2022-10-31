#include <stdio.h>
#include <time.h>

int main()
{
    time_t hora;
    time(&hora);
    printf("Son las %s",ctime(&hora));
    
    return 0;
}
