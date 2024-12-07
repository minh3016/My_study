#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<fcntl.h>
#include<sys/stat.h>
#include<unistd.h>
#include<sys/types.h>


#define FIFO_NAME "./helloFIFO"
#define BUFFER_SIZE 1024

int main(int argc, const char *argv[])
{
    char  fifo_buffer[BUFFER_SIZE];
    int fd;
    mkfifo(FIFO_NAME,0666);
    while (1)
    {
        //reading message
        fd = open(FIFO_NAME, O_RDONLY);
        read(fd, fifo_buffer, BUFFER_SIZE);
        printf("Message from server: %s\n", fifo_buffer);
        close(fd);
        //writing message

        printf("Writing message to server: \n");
        fflush(stdin);
        fgets(fifo_buffer,BUFFER_SIZE,stdin);

        fd = open(FIFO_NAME,O_WRONLY);
        write(fd,fifo_buffer,strlen(fifo_buffer) + 1);
        close(fd);
    }
    return 0;
}