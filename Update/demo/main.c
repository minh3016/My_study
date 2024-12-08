#include "inc/ipc_message_queue.h"
#include "inc/ipc_shared_memory.h"
#include "inc/ipc_pipe.h"

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

void *client_thread(void *arg) {
    ipc_message_queue_client();
    ipc_shared_memory_client();
    ipc_pipe_client();
    return NULL;
}

void *server_thread(void *arg) {
    ipc_message_queue_server();
    ipc_shared_memory_server();
    ipc_pipe_server();
    return NULL;
}

int main() {
    pthread_t client, server;

    pthread_create(&client, NULL, client_thread, NULL);
    pthread_create(&server, NULL, server_thread, NULL);

    pthread_join(client, NULL);
    pthread_join(server, NULL);

    return 0;
}
