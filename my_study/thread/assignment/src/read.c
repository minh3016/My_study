#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <pthread.h>
#include "read.h"

extern int student_ready;
extern int done_input;

void* read_thread(void* arg) {
    while (1) {
        pthread_mutex_lock(&mutex);
        pthread_cond_wait(&cond_read, &mutex);

        if (done_input && !student_ready) {
            pthread_mutex_unlock(&mutex);
            break;
        }

       
        int fd = open("thongtinsinhvien.txt", O_RDONLY);
        if (fd != -1) {
            char buffer[MAX];
            ssize_t bytes;
            printf("Dữ liệu đã ghi vào file:\n");
            while ((bytes = read(fd, buffer, MAX - 1)) > 0) {
                buffer[bytes] = '\0';  
                printf("%s", buffer);
            }
            close(fd);
        }

        pthread_cond_signal(&cond_input);
        pthread_mutex_unlock(&mutex);
    }
    return NULL;
}

