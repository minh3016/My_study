// udp_server.c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include<signal.h>
#define PORT 8080
#define BUFFER_SIZE 1024
void sig_handle(int signo)
{
    printf("Sever terminate\n");
    exit(1);
}
int main() {
    int sockfd;
    signal(SIGINT, sig_handle);
    struct sockaddr_in server_addr, client_addr;
    char buffer[BUFFER_SIZE];
    socklen_t addr_len = sizeof(client_addr);

    // Create UDP socket
    if ((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0) {
        perror("Socket creation failed");
        exit(EXIT_FAILURE);
    }

    // Initialize server information
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(PORT);

    // Bind socket to the specified port and address
    if (bind(sockfd, (const struct sockaddr *)&server_addr, sizeof(server_addr)) < 0) {
        perror("Bind failed");
        close(sockfd);
        exit(EXIT_FAILURE);
    }

    printf("UDP Server is listening on port %d...\n", PORT);

    // Server loop to receive and respond to messages
    while (1) {
        int n = recvfrom(sockfd, buffer, BUFFER_SIZE, MSG_WAITALL, (struct sockaddr *)&client_addr, &addr_len);
        buffer[n] = '\0';
        printf("Message from client: %s\n", buffer);
        if(strncmp("exit", buffer, 4) == 0)
        {
            printf("Receive exit from client, ");
            raise(SIGINT);
        }
        // Get server response from keyboard
        printf("Enter response to client: ");
        fgets(buffer, BUFFER_SIZE, stdin);

        // Send response to client
        sendto(sockfd, buffer, strlen(buffer), MSG_CONFIRM, (const struct sockaddr *)&client_addr, addr_len);
        printf("Response sent to client.\n");
    }

    close(sockfd);
    return 0;
}
