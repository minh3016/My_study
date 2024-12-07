
#ifndef BUFFER_H
#define BUFFER_H

#include <semaphore.h>

// Kích thước buffer
#define BUFFER_SIZE 5

// Buffer dùng chung
extern int buffer[BUFFER_SIZE];
extern int count;

// Semaphore
extern sem_t empty;
extern sem_t full;
extern sem_t mutex;

#endif
