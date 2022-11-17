#include <stdio.h>
#include <pthread.h>

void * p(void* r)
{
    for(;;)
    {
        int n = 37284697084939809+88;
        pthread_yield(NULL);
    }
}
int main()
{
    pthread_t p1,p2,p3,p4;
    pthread_create(&p1, NULL, p, NULL);
    pthread_create(&p2, NULL, p, NULL);
    pthread_create(&p3, NULL, p, NULL);
   // pthread_create(&p4, NULL, p, NULL);
    for(;;);
    return 0;
}
