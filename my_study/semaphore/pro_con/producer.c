#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<pthread.h>
#include "buffer.h"

// Hàm của Producer (Nhà sản xuất)
void* producer(void* arg) {
    int item;
    while (1) {
        // Sản xuất dữ liệu ngẫu nhiên
        item = rand() % 100;
        // Đợi cho đến khi có vị trí trống trong buffer
        sem_wait(&empty);
        // Đợi để vào critical section
        sem_wait(&mutex);

        // Thêm phần tử vào buffer
        buffer[count] = item;
        printf("Producer sản xuất: %d\n", item);
        count++;

        // Giải phóng critical section
        sem_post(&mutex);
        // Tăng số phần tử có sẵn cho Consumer
        sem_post(&full);

        sleep(1);  // Giả lập thời gian sản xuất
    }
}

int main() {
    pthread_t prod;

    // Khởi tạo buffer và semaphore
    sem_init(&empty, 0, BUFFER_SIZE);  // Ban đầu buffer rỗng
    sem_init(&full, 0, 0);             // Ban đầu buffer không có phần tử nào
    sem_init(&mutex, 0, 1);            // Semaphore bảo vệ critical section

    // Tạo luồng Producer
    pthread_create(&prod, NULL, producer, NULL);

    // Chờ luồng Producer kết thúc (vô tận)
    pthread_join(prod, NULL);

    // Hủy semaphore (thực tế không đến đây)
    sem_destroy(&empty);
    sem_destroy(&full);
    sem_destroy(&mutex);

    return 0;
}

