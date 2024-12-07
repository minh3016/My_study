#include <stdio.h>
#include <fcntl.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>
#include "write.h"

extern Student student;
extern int student_ready;
extern int done_input;

void* write_thread(void* arg) {
    while (1) {
        pthread_mutex_lock(&mutex);
        while (!student_ready && !done_input) {
            pthread_cond_wait(&cond_write, &mutex); 
        }

        if (done_input && !student_ready) {
            pthread_mutex_unlock(&mutex);
            break;
        }

        
        int fd = open("thongtinsinhvien.txt", O_WRONLY | O_CREAT | O_APPEND, 0644);
        if (fd != -1) {
            char buffer[MAX];
            snprintf(buffer, MAX, "Họ và tên: %.255s\n", student.name);
            write(fd, buffer, strlen(buffer));

            snprintf(buffer, MAX, "Ngày sinh: %.255s\n", student.dob);
            write(fd, buffer, strlen(buffer));

            snprintf(buffer, MAX, "Quê quán: %.255s\n", student.hometown);
            write(fd, buffer, strlen(buffer));

            close(fd);
        }

        student_ready = 0; 
        pthread_cond_signal(&cond_read); 
        pthread_mutex_unlock(&mutex);
    }
    return NULL;
}

