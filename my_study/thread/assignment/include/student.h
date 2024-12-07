#ifndef STUDENT_H
#define STUDENT_H

#include <pthread.h>

#define MAX 512


typedef struct {
    char name[MAX];
    char dob[MAX];     
    char hometown[MAX]; 
} Student;

extern Student student;
extern int student_ready;
extern int done_input;

extern pthread_mutex_t mutex;
extern pthread_cond_t cond_input, cond_write, cond_read;

#endif

