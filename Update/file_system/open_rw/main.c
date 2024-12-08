// I/O in linux file system

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>

int main(void)
{
    int fd;
    int number_write;
    char buffer1[12] = "hello world\n";

    fd = open("test.txt", O_RDWR | O_CREAT);// flag o_creat check file hello.txt neu chua ton tai thi tao moi
    if (-1 == fd)
    {
        /* code */
        perror("open() file hello.txt is FAILD");
	exit(EXIT_FAILURE);
    } 

    number_write = write(fd, buffer1, strlen(buffer1));
     
    printf("write %d bytes in hello.txt\n", number_write);

    lseek(fd,0,SEEK_END);


    char buffer2[10] = "MinhNq";

    write(fd, buffer2, strlen(buffer2));
	char buffer3[10];
	ssize_t number_byte_read = read(fd,buffer3, sizeof(buffer3) - 1);
	if(number_byte_read < 0)
	{
		perror("Read fail");
		close(fd);
		exit(EXIT_FAILURE);
	}
	buffer3[number_byte_read] = '\0';
	printf("data read in hello.txt:\n %s \n", buffer3);
    close(fd);
     return 0;
    
}
