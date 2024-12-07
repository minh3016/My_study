#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<sys/ipc.h>
#include<sys/shm.h>
#include<unistd.h>
#define SHM_SIZE 1024
int main()
{

    key_t key;
    int shmid;
    char *shmaddr;
    //create key for share mem

    key = ftok("./shmfile",65);

    // create share mem

    shmid = shmget(key, SHM_SIZE, IPC_CREAT | 0666);
    if(shmid == -1)
    {
        perror("Can not create share memory\n");
        exit(0);
    }

    //address

    shmaddr = (char*) shmat(shmid, NULL, 0);
    if(shmaddr == (char*)-1)
    {
        perror("shmat failed \n");
        exit(0);
    }

    //write data
    printf("Writing data in share memory: ");
    fgets(shmaddr, SHM_SIZE, stdin);

    printf("Data written in share memory: %s\n", shmaddr);

    // waiting client read data
   while(1);
    if(shmdt(shmaddr) == -1)
    {
        perror("shmdt fail\n");
        exit(0);
    }

    return 0;
}
