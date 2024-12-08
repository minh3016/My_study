#include <sys/stat.h>
#include <stdio.h>
#include <sys/file.h>
#include <unistd.h>
#include <fcntl.h>

int main(void)

{

    int fd;
    char buffer[16] = {0};
    sprintf(buffer,"Hello world\n");
    fd = open("./test.txt",O_RDWR | O_CREAT,0666);
    if(fd == -1)
    {
        printf("Khong the mo file test.txt\n");
        return 0;
    }
    else
    {
        printf("Mo thanh cong file test.txt\n");
    }
    int number_write = write(fd,buffer, sizeof(buffer)-1);
    if(number_write == -1)
    {
        printf("Khong the viet vao file test.txt\n");
    }
    else
    {
        printf("viet thanh cong vao file test.txt\n");
    }
    if(flock(fd, LOCK_EX | LOCK_NB) == -1)
    {
        
    }
}