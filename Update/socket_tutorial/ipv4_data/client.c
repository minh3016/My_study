// udp_client.c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <signal.h>
#define PORT 8080
#define BUFFER_SIZE 1024

void sig_handle(int signo)
{
    printf("Client terminate\n");
    exit(1);
}
int main() {
    int sockfd;
    struct sockaddr_in server_addr;
    char buffer[BUFFER_SIZE];
    socklen_t addr_len;
    signal(SIGINT, sig_handle);
    // Create UDP socket
    if ((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0) {
        perror("Socket creation failed");
        exit(EXIT_FAILURE);
    }

    // Initialize server information
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(PORT);
    server_addr.sin_addr.s_addr = INADDR_ANY;

    while (1) {
        // Get client message from keyboard
        printf("Enter message to send to server: ");
        fgets(buffer, BUFFER_SIZE, stdin);

        // Send message to server
        sendto(sockfd, buffer, strlen(buffer), MSG_CONFIRM, (const struct sockaddr *)&server_addr, sizeof(server_addr));
        printf("Message sent to server.\n");

        // Receive response from server
        addr_len = sizeof(server_addr);
        int n = recvfrom(sockfd, buffer, BUFFER_SIZE, MSG_WAITALL, (struct sockaddr *)&server_addr, &addr_len);
        buffer[n] = '\0';
        printf("Server: %s\n", buffer);
        if(strncmp("exit", buffer, 4) == 0)
        {
            printf("Receive message exit from server, ");
            raise(SIGINT);
        }
    }

    close(sockfd);
    return 0;
}
