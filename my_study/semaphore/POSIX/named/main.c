#include<stdio.h>
#include<fcntl.h>
#include<unistd.h>
#include<stdlib.h>
#include<semaphore.h>
#include<sys/stat.h>

int main()
{
    sem_t *sem;
    int current_value;
    const char *sem_named = "/example_sem";
    //open new sem
    sem = sem_open(sem_named,O_CREAT | O_EXCL,0666,5);
    if(sem == SEM_FAILED)
    {
        perror("Open sem fail\n");
        exit(1);
    }
    //waiting sem

    printf("Waiting semaphore....\n");
    sem_wait(sem);
    printf("Current value semaphore: %d\n", sem_getvalue(sem, &current_value));
    //critical section
    printf("I am in critical section\n");

    sleep(5);

    //post sem

    printf("Posting semaphore.... \n");

    sem_post(sem);
    printf("Curent value semaphore: %d\n", sem_getvalue(sem,&current_value));
    //closing sem

    printf("Closing semaphore...\n");
    sem_close(sem);
    printf("Closing success\n");

    // unlink sem

    sem_unlink(sem_named);
    
    return 0;
}
