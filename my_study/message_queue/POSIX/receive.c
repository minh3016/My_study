#include <stdio.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <mqueue.h>
#include <string.h>
#include <stdlib.h>

int main() {
    mqd_t mq;
    char buffer[1024];    // Đảm bảo bộ đệm nhận đủ lớn
    unsigned int prio;

    // Mở hàng đợi để đọc
    mq = mq_open("/test_queue", O_RDONLY);
    if (mq == -1) {
        perror("mq_open");
        exit(1);
    }
    while(1)
    {
    // Nhận tin nhắn
    if (mq_receive(mq, buffer, sizeof(buffer), &prio) == -1) {
        perror("mq_receive");
        exit(1);
    }

    printf("Received message: %s, priority: %u\n", buffer, prio);
    }
    // Đóng và hủy hàng đợi
    mq_close(mq);
    mq_unlink("/test_queue");

    return 0;
}
