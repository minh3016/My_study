#include <stdio.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <sys/stat.h>        
#include <fcntl.h>           
#include <unistd.h>          
#include <string.h>

#define SHM_NAME "./my_shm"   // Name of shared memory object
#define SHM_SIZE 1024        // Size of shared memory (1KB)

int main() {
    int shm_fd;
    void *ptr;

    // Create shared memory object
    shm_fd = shm_open(SHM_NAME, O_CREAT | O_RDWR, 0666);
    if (shm_fd == -1) {
        perror("shm_open");
        exit(1);
    }

    // Set the size of the shared memory object
    if (ftruncate(shm_fd, SHM_SIZE) == -1) {
        perror("ftruncate");
        exit(1);
    }

    // Map the shared memory object to the process's address space
    ptr = mmap(0, SHM_SIZE, PROT_READ | PROT_WRITE, MAP_SHARED, shm_fd, 0);
    if (ptr == MAP_FAILED) {
        perror("mmap");
        exit(1);
    }

    // Write data to the shared memory
    char *message = "Hello from shared memory!";
    sprintf(ptr, "%s", message);
    printf("Server: Wrote message to shared memory: %s\n", message);

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
