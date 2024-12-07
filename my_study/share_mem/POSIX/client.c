#include <stdio.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <sys/stat.h>        
#include <fcntl.h>           
#include <unistd.h>          
#include <string.h>

#define SHM_NAME "/my_shm"   // Name of shared memory object
#define SHM_SIZE 1024        // Size of shared memory (1KB)

int main() {
    int shm_fd;
    void *ptr;

    // Open the existing shared memory object
    shm_fd = shm_open(SHM_NAME, O_RDWR, 0666);
    if (shm_fd == -1) {
        perror("shm_open");
        exit(1);
    }

    // Map the shared memory object to the process's address space
    ptr = mmap(0, SHM_SIZE, PROT_READ, MAP_SHARED, shm_fd, 0);
    if (ptr == MAP_FAILED) {
        perror("mmap");
        exit(1);
    }

    // Read data from the shared memory
    printf("Client: Read message from shared memory: %s\n", (char*)ptr);

    // Unmap the shared memory
    if (munmap(ptr, SHM_SIZE) == -1) {
        perror("munmap");
        exit(1);
    }

    // Close the shared memory object
    if (close(shm_fd) == -1) {
        perror("close");
        exit(1);
    }

    return 0;
}
