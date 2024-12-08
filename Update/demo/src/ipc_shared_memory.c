#include "../inc/ipc_shared_memory.h"
#include <sys/types.h>
#include <sys/shm.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void ipc_shared_memory_client() {
    int shm_id = shmget(KEY, SHM_SIZE, IPC_CREAT | 0666);
    if (shm_id == -1) {
        perror("shmget");
        exit(1);
    }

    void *shm_addr = shmat(shm_id, NULL, 0);
    if (shm_addr == (void *)-1) {
        perror("shmat");
        exit(1);
    }

    strncpy((char *)shm_addr, "Image data detached from camera.", SHM_SIZE);
}

void ipc_shared_memory_server() {
    int shm_id = shmget(KEY, SHM_SIZE, IPC_CREAT | 0666);
    if (shm_id == -1) {
        perror("shmget");
        exit(1);
    }

    void *shm_addr = shmat(shm_id, NULL, 0);
    if (shm_addr == (void *)-1) {
        perror("shmat");
        exit(1);
    }

    printf("Server received (Shared Memory): %s\n", (char *)shm_addr);
}
