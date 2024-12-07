#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<signal.h>

#define BUFFER_SIZE 50
char *msg1 = "Hello pipe, i am msg 1\n";
char *msg2 = "Hello pipe, i am msg 2\n";
char *msg3 = "Hello pipe, i am msg 3";
char *msg4 = "Hello pipe, i am sig INT\n";

char pipe_buffer[BUFFER_SIZE];
int fds[2];
int i;

void sig_handle(int signo)
{
    printf("\nHello i am sig handle 2\n");
    write(fds[1], msg4, BUFFER_SIZE);
}

int main(int argc, const char  *argv[])
{
    
    if(signal(SIGINT, sig_handle) == SIG_ERR)
    {
    fprintf(stderr, "Can not call sig int\n");
    exit(EXIT_FAILURE);
    }
    
   if(pipe(fds) < 0)
   {
    printf("Pipe can not created...\n");
    exit(1);
   }
    // writing pipe
   write(fds[1], msg1, BUFFER_SIZE);
   write(fds[1], msg2, BUFFER_SIZE);
    write(fds[1], msg3, BUFFER_SIZE);
    sleep(2);

    printf("Reading data from pipe.....\n");

    read(fds[0], pipe_buffer, BUFFER_SIZE);
    printf("Message[%d] from pipe: %s\n", 4, pipe_buffer);
    // reading pipe
    for(i = 0; i < 3;i++)
    {
       read(fds[0], pipe_buffer, BUFFER_SIZE);
        printf("Reading from pipe: Msg[%d]: %s\n", i+1, pipe_buffer);
    }

}