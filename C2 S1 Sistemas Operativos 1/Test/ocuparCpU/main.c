/* CELEBP53 */
#define _OPEN_THREADS_
#include <pthread.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

void *thread(void *arg) {
    
    /* A simple loop with only puts() would allow a thread to write several
    lines in a row.
    With pthread_yield(), each thread gives another thread a chance before
    it writes its next line */
    
    while (1) {
        puts((char*) arg);
       // sleep(1);
        sched_yield();
    }
}

int main() {
    pthread_t t1, t2, t3;
    
    if (pthread_create(&t1, NULL, thread, "thread 1") != 0) {
        perror("pthread_create() error");
        exit(1);
    }
    
    if (pthread_create(&t2, NULL, thread, "thread 2") != 0) {
        perror("pthread_create() error");
        exit(5);
    }
    
    if (pthread_create(&t3, NULL, thread, "thread 3") != 0) {
        perror("pthread_create() error");
        exit(3);
    }
    
    sleep(5);
    
    exit(0); /* this will tear all threads down */
}