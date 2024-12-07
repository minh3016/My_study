#include<stdio.h>
#include<semaphore.h>
#include<time.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/mman.h>
#include<signal.h>
#define SIZE 10
void sig_handle(int signo)
{
    printf("EXTING PROGRAM....\n");
    exit(1);
}
int main()

{
    // sig handle

    signal(SIGINT, sig_handle);
    // create share memory
    int *buffer = (char *)mmap(NULL, sizeof(int)*SIZE, PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, -1, 0);

    // create semaphore

    sem_t *mutex = (sem_t*)mmap(NULL, sizeof(sem_t*), PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, -1, 0);
    sem_t *empty = (sem_t*)mmap(NULL, sizeof(sem_t*), PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, -1, 0);
    sem_t *full =  (sem_t*)mmap(NULL, sizeof(sem_t*), PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, -1, 0);

    sem_init(mutex, 1, 1);
    sem_init(empty, 1, SIZE);
    sem_init(full, 1, 0);
    pid_t producer;
    pid_t consumer;
    // Process producer
    if((producer = fork()) == 0)
    {
        while(1)
        {
            sem_wait(empty);
            sem_wait(mutex);    // lock mutex
            printf("Producer create something\n");

            sem_post(full);
            sem_post(mutex); // unlock mutex

            sleep(3);
        }
    }
    //process consumer
    if((consumer = fork()) == 0)
    {
        while (1)
        {
            sem_wait(full);
            sem_wait(mutex);

            printf("consumer taking...\n");

            sem_post(mutex);
            sem_post(empty);
            
            srand(time(NULL));
            sleep(3 + rand() % 5);
        }
        
    }
    //process parent
    else
    {
        while (1)
        {
            /* code */
            sleep(15);
            int takentSlot;

            sem_getvalue(full, &takentSlot);

            printf("Item in full : %d/%d\n", takentSlot, SIZE);

            if(takentSlot == 10)
            {
                raise(SIGINT);
                
            }
        }
        
    }

    return 0;
}
