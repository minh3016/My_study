#include<stdio.h>
#include<unistd.h>
#include<string.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<sys/types.h>
#include<signal.h>
#define FIFO_NAME "./helloFIFO"
#define BUFFER_SIZE 1024

// Hàm xử lý tín hiệu SIGINT
void sig_handle(int signo)
{
    printf("\nServer exiting....\n");
    unlink(FIFO_NAME); // Xóa FIFO trước khi thoát
    _exit(0); // Kết thúc chương trình
}

int main(int argc, const char *argv[])
{
    char fifo_buff[BUFFER_SIZE];
    int fd;

    // Đăng ký xử lý tín hiệu SIGINT
    signal(SIGINT, sig_handle);

    // Tạo FIFO
    if (mkfifo(FIFO_NAME, 0666) == -1)
    {
        perror("mkfifo failed");
        return 1;
    }

    while (1)
    {
        printf("Message to client : ");
        fgets(fifo_buff, BUFFER_SIZE, stdin);

        // Loại bỏ ký tự xuống dòng '\n' từ fgets nếu có
        fifo_buff[strcspn(fifo_buff, "\n")] = 0;

        // Mở FIFO để ghi
        fd = open(FIFO_NAME, O_WRONLY);
        if (fd == -1)
        {
            perror("Failed to open FIFO for writing");
            continue;
        }

        write(fd, fifo_buff, strlen(fifo_buff) + 1);
        close(fd);

        // Mở FIFO để đọc
        int fd1 = open(FIFO_NAME, O_RDONLY);
        if (fd1 == -1)
        {
            perror("Failed to open FIFO for reading");
            continue;
        }

        read(fd1, fifo_buff, BUFFER_SIZE);
        printf("Client response: %s\n", fifo_buff);
        if (strncmp("exit", fifo_buff, 4) == 0)
        {
           printf("Raising SIGINT....\n");
            raise(SIGINT);
        }
        
        close(fd1);
    }

    return 0;
}
