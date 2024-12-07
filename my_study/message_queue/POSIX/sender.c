#include <stdio.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <mqueue.h>
#include <string.h>
#include <stdlib.h>

int main() {
    mqd_t mq;
    struct mq_attr attr;
    char message[1024];
    unsigned int prio = 1;

    // Cấu hình thuộc tính hàng đợi
    attr.mq_flags = 0;             // Không có cờ đặc biệt
    attr.mq_maxmsg = 10;           // Tối đa 10 tin nhắn trong hàng đợi
    attr.mq_msgsize = 1024;        // Kích thước tối đa của mỗi tin nhắn là 1024 bytes
    attr.mq_curmsgs = 0;           // Số tin nhắn hiện tại trong hàng đợi

    // Mở hoặc tạo hàng đợi tin nhắn với thuộc tính
    mq = mq_open("/test_queue", O_CREAT | O_WRONLY, 0644, &attr);
    if (mq == -1) {
        perror("mq_open");
        exit(1);
    }
    while(1)
    {
    printf("enter message: ");
    fgets(message, sizeof(message), stdin);
    message[strcspn(message, "\n")] = '\0'; // Xóa ký tự xuống dòng

    // Gửi tin nhắn với độ ưu tiên là 1
    if (mq_send(mq, message, strlen(message) + 1, prio) == -1) {
        perror("mq_send");
        exit(1);
    }

    printf("Sent message: %s\n", message);
    attr.mq_curmsgs ++;
    printf("Number of message in queue: %ld\n", attr.mq_curmsgs);
    }
    // Đóng hàng đợi
    mq_close(mq);

    return 0;
}
