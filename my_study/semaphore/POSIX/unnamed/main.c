#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <semaphore.h>
#include <pthread.h>

sem_t sem_exam;
int current_value;

void* thread_func(void* arg) {
    int thread_num = *(int *)arg;

    // Chờ semaphore
    sem_wait(&sem_exam);
    
    printf("Thread %d in critical section\n", thread_num);
    // Làm gì đó trong vùng critical
    sleep(5);
    printf("Thread %d exit critical section\n", thread_num);

    // Giải phóng semaphore
    printf("Posting sem...\n");
    sem_post(&sem_exam);

    sem_getvalue(&sem_exam, &current_value);
    printf("Current value of semaphore: %d\n", current_value);

    return NULL;
}

int main() {
    pthread_t thread_id1, thread_id2;
    int thread_num1 = 1, thread_num2 = 2;

    // Khởi tạo semaphore với giá trị ban đầu là 1
    sem_init(&sem_exam, 0, 1);

    pthread_create(&thread_id1, NULL, thread_func, &thread_num1);
    pthread_create(&thread_id2, NULL, thread_func, &thread_num2);

    pthread_join(thread_id1, NULL);
    pthread_join(thread_id2, NULL);
    
    // Hủy semaphore
    printf("Destroying semaphore\n");
    sem_destroy(&sem_exam);

    printf("Destroy success\n");
    return 0;
}
