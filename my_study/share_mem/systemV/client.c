#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/shm.h>

#define SHM_SIZE 1024  // Kích thước bộ nhớ dùng chung

int main() {
    key_t key;
    int shmid;
    char *shmaddr;

    // Tạo một khóa duy nhất giống như trong server
    key = ftok("shmfile", 65);

    // Tìm kiếm bộ nhớ dùng chung đã được tạo bởi server
    shmid = shmget(key, SHM_SIZE, 0666);
    if (shmid == -1) {
        perror("shmget failed");
        exit(1);
    }

    // Gắn bộ nhớ dùng chung vào không gian địa chỉ của tiến trình
    shmaddr = (char*) shmat(shmid, NULL, 0);
    if (shmaddr == (char *) -1) {
        perror("shmat failed");
        exit(1);
    }
   
    // Đọc dữ liệu từ bộ nhớ dùng chung
    printf("Dữ liệu được đọc từ bộ nhớ: %s\n", shmaddr);

   
    // Tháo bộ nhớ dùng chung
    if (shmdt(shmaddr) == -1) {
        perror("shmdt failed");
        exit(1);
    }

    // Xóa bộ nhớ dùng chung (chỉ server hoặc client mới cần làm điều này)
    if (shmctl(shmid, IPC_RMID, NULL) == -1) {
        perror("shmctl failed");
        exit(1);
    }
    return 0;
}
