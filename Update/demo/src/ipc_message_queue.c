#include "../inc/ipc_message_queue.h"
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct msg_buffer {
    long msg_type;
    char msg_text[MSG_SIZE];
};

void ipc_message_queue_client() {
    int msg_queue_id = msgget(KEY, IPC_CREAT | 0666);
    if (msg_queue_id == -1) {
        perror("msgget");
        exit(1);
    }

    struct msg_buffer msg;
    msg.msg_type = 1;
    strncpy(msg.msg_text, "Image data detached from camera.", MSG_SIZE);

    if (msgsnd(msg_queue_id, &msg, sizeof(msg.msg_text), 0) == -1) {
        perror("msgsnd");
    }
}

void ipc_message_queue_server() {
    int msg_queue_id = msgget(KEY, IPC_CREAT | 0666);
    if (msg_queue_id == -1) {
        perror("msgget");
        exit(1);
    }

    struct msg_buffer msg;
    if (msgrcv(msg_queue_id, &msg, sizeof(msg.msg_text), 1, 0) != -1) {
        printf("Server received (Message Queue): %s\n", msg.msg_text);
    }
}
