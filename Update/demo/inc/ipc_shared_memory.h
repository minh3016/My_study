#ifndef IPC_SHARED_MEMORY_H
#define IPC_SHARED_MEMORY_H

#define SHM_SIZE 1024
#define KEY 1234

void ipc_shared_memory_client();
void ipc_shared_memory_server();

#endif

