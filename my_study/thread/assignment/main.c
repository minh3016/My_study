#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <pthread.h>
#include "input.h"
#include "write.h"
#include "read.h"


pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t cond_input = PTHREAD_COND_INITIALIZER;
pthread_cond_t cond_write = PTHREAD_COND_INITIALIZER;
pthread_cond_t cond_read = PTHREAD_COND_INITIALIZER;

void handle_sigint(int sig) {
    printf("\nProgram terminate.\n");
    exit(0);
}

int main() {
    
    signal(SIGINT, handle_sigint);

    
    pthread_t input_tid, write_tid, read_tid;

    
    pthread_create(&input_tid, NULL, input_thread, NULL);
    pthread_create(&write_tid, NULL, write_thread, NULL);
    pthread_create(&read_tid, NULL, read_thread, NULL);

    
    pthread_join(input_tid, NULL);
    pthread_join(write_tid, NULL);
    pthread_join(read_tid, NULL);

    
    pthread_mutex_destroy(&mutex);
    pthread_cond_destroy(&cond_input);
    pthread_cond_destroy(&cond_write);
    pthread_cond_destroy(&cond_read);

    return 0;
}
