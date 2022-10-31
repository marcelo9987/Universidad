#include <stdio.h>
#include <signal.h>
#include <unistd.h>

void hand(int a)
{
    switch(a)
    {
        case SIGALRM:
            printf("hola\n");
            break;
    }
}
int main()
{
    signal(SIGALRM,hand);
    while(1)
    {
        alarm(1);
    }
    return 0;
}
