#include "../inc/ipc_pipe.h"
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

void ipc_pipe_client() {
    if (mkfifo(PIPE_NAME, 0666) == -1) {
        perror("mkfifo");
    }

    int fd = open(PIPE_NAME, O_WRONLY);
    if (fd != -1) {
        write(fd, "Image data detached from camera.", 256);
        close(fd);
    } else {
        perror("open");
    }
}

void ipc_pipe_server() {
    int fd = open(PIPE_NAME, O_RDONLY);
    if (fd != -1) {
        char buffer[256];
        read(fd, buffer, 256);
        printf("Server received (Pipe): %s\n", buffer);
        close(fd);
    }
}
