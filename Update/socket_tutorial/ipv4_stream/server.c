#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>
#include<arpa/inet.h>
#include<netinet/in.h>
#include<sys/socket.h>

#define LISTEN_BACKLOG 50
#define BUFFER_SIZE 1024
#define handle_error(msg) \
    do { perror(msg); exit(EXIT_FAILURE); } while (0)

void chat_func(int new_socket_fd)
{
    int read_num, write_num;
    char tx_buffer[BUFFER_SIZE];
    char rx_buffer[BUFFER_SIZE];

    while (1)
    {
        memset(tx_buffer, 0, BUFFER_SIZE);
        memset(rx_buffer, 0, BUFFER_SIZE);

        // read message
        read_num = read(new_socket_fd, rx_buffer, BUFFER_SIZE);
        if(read_num == -1)
        {
            handle_error("read()");
        }

        if(strncmp("exit", rx_buffer, 4) == 0)
        {
            break;
        }

        printf("Message from client: %s\n", rx_buffer);

        // write message
        printf("Respond message: ");
        fgets(tx_buffer, BUFFER_SIZE, stdin);

        write_num = write(new_socket_fd, tx_buffer, strlen(tx_buffer));
        if(write_num == -1)
        {
            handle_error("write()");
        }

        if(strncmp("exit", tx_buffer, 4) == 0)
        {
            break;
        }

        sleep(2);
    }
    close(new_socket_fd);
}

int main(int argc, const char *argv[])
{
    int port_number, len, opt = 1;
    int server_fd, new_socket_fd;

    struct sockaddr_in server_addr, client_addr;

    // read command line argument
    if(argc < 2)
    { 
        printf("No port provided. Usage: ./server <port number>\n");
        exit(EXIT_FAILURE);
    }
    else
    {
        port_number = atoi(argv[1]);
    }

    memset(&server_addr, 0, sizeof(struct sockaddr_in));
    memset(&client_addr, 0, sizeof(struct sockaddr_in));

    // create socket
    server_fd = socket(AF_INET, SOCK_STREAM, 0);
    if(server_fd == -1)
    {
        handle_error("socket()");
    }

    // set socket options
    if(setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt)) == -1)
    {
        handle_error("setsockopt()");
    }

    // create address
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(port_number);
    server_addr.sin_addr.s_addr = INADDR_ANY;

    // bind
    if(bind(server_fd, (struct sockaddr *)&server_addr, sizeof(server_addr)) == -1)
    {
        handle_error("bind()");
    }

    // listen
    if(listen(server_fd, LISTEN_BACKLOG) == -1)
    {
        handle_error("listen()");
    }

    // get client info
    len = sizeof(client_addr);

    // main loop to accept connections
    while (1)
    {
        printf("Server listening on port number: %d\n", port_number);
        new_socket_fd = accept(server_fd, (struct sockaddr *)&client_addr, (socklen_t *)&len);
        if(new_socket_fd == -1)
        {
            handle_error("accept()");
        }
        printf("Server got a connection\n");
        chat_func(new_socket_fd);
    }

    close(server_fd);
    return 0;
}

