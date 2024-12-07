#include <stdio.h>
#include <string.h>
#include <pthread.h>
#include <signal.h>
#include "input.h"

Student student;
int student_ready = 0;
int done_input = 0;

void* input_thread(void* arg) {
    while (1) {
        pthread_mutex_lock(&mutex);
        while (student_ready) {
            pthread_cond_wait(&cond_input, &mutex); 
        }

        printf("Enter name or exit: ");
        fgets(student.name, MAX, stdin);
        student.name[strcspn(student.name, "\n")] = 0; 

        
        if (strcmp(student.name, "exit") == 0) {
            done_input = 1;
            pthread_cond_signal(&cond_write); 
            pthread_mutex_unlock(&mutex);
            raise(SIGINT);
            break;
        }

        printf("Enter date of birth: ");
        fgets(student.dob, MAX, stdin);
        student.dob[strcspn(student.dob, "\n")] = 0;

        printf("Enter hometown: ");
        fgets(student.hometown, MAX, stdin);
        student.hometown[strcspn(student.hometown, "\n")] = 0;

        student_ready = 1;
        pthread_cond_signal(&cond_write); 
        pthread_mutex_unlock(&mutex);
    }
    return NULL;
}

