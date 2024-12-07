#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include "buffer.h"

// Hàm của Consumer (Người tiêu thụ)
void* consumer(void* arg) {
    int item;
    while (1) {
        // Đợi cho đến khi có phần tử trong buffer
        sem_wait(&full);
        // Đợi để vào critical section
        sem_wait(&mutex);

        // Lấy phần tử ra khỏi buffer
        count--;
        item = buffer[count];
        printf("Consumer tiêu thụ: %d\n", item);

        // Giải phóng critical section
        sem_post(&mutex);
        // Tăng số vị trí trống cho Producer
        sem_post(&empty);

        sleep(2);  // Giả lập thời gian tiêu thụ
    }
}

int main() {
    pthread_t cons;

    // Khởi tạo buffer và semaphore
    sem_init(&empty, 0, BUFFER_SIZE);  // Ban đầu buffer rỗng
    sem_init(&full, 0, 0);             // Ban đầu buffer không có phần tử nào
    sem_init(&mutex, 0, 1);            // Semaphore bảo vệ critical section

    // Tạo luồng Consumer
    pthread_create(&cons, NULL, consumer, NULL);

    // Chờ luồng Consumer kết thúc (vô tận)
    pthread_join(cons, NULL);

    // Hủy semaphore (thực tế không đến đây)
    sem_destroy(&empty);
    sem_destroy(&full);
    sem_destroy(&mutex);

    return 0;
}
