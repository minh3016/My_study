#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<arpa/inet.h>
#include<string.h>
#include<error.h>
#include<sys/socket.h>
#include<netinet/in.h>

#define BUFFER_SIZE 1024
#define handle_error(msg) \
    do { perror(msg); exit(EXIT_FAILURE); } while (0)


void chat_func(int server_fd)
{
    int read_num, write_num;
    char rx_buffer[BUFFER_SIZE];
    char tx_buffer[BUFFER_SIZE];

    while (1)
    {
        /* code */
        memset(tx_buffer, 0, BUFFER_SIZE);
        memset(rx_buffer, 0, BUFFER_SIZE);

        printf("Enter the message: ");
        fgets(tx_buffer, BUFFER_SIZE, stdin);

        // writing message to server

        write_num = write(server_fd, tx_buffer, sizeof(tx_buffer));
        if(write_num == -1)
        {
            handle_error("write()");
        }
         if(strncmp("exit", tx_buffer, 4) == 0)
         {
            printf("Client exiting....\n");
            break;
         }
        // get message from server 

        read_num = read(server_fd, rx_buffer,sizeof(rx_buffer));
        if(read_num == -1)
        {
            handle_error("read");
        }

        if(strncmp("exit", rx_buffer, 4) == 0)
        {
            printf("Server exitng....\n");
            break;
        }
        printf("Message from server: %s", rx_buffer);

    }
    close(server_fd);
}
int main(int argc, const char *argv[])
{
    int port_number;
    int server_fd;
    struct sockaddr_in server_addr;
    memset(&server_addr, 0 , sizeof(server_addr));

    // read command line
    if(argc < 3)
    {
        printf("Command: ./client <server_addr> <port number>\n");
        exit(1);
    }
    else
    {
        port_number = atoi(argv[2]);
    }

    // creat adddress

    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(port_number);

    if(inet_pton(AF_INET, argv[1], &server_addr.sin_addr) == -1)
    {
        handle_error("inet_pton()");
    }

    // create socket
    server_fd = socket(AF_INET, SOCK_STREAM, 0);
    if(server_fd == -1)
    {
        handle_error("socket()");
    }
    // connect to server
    if(connect(server_fd, (struct sockaddr*)&server_addr, sizeof(server_addr)) == -1)
    {
        handle_error("connect()");
    }
    chat_func(server_fd);
    return 0;
}
