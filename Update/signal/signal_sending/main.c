#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <signal.h>

void sig_handler1(int num)
{
    printf("\nIm signal handler1: %d\n", num);
}

void sig_handler3(int num)
{
    printf("Im signal handler3: %d\n", num);
    exit(EXIT_SUCCESS);  // Thoát chương trình khi nhận tín hiệu SIGTERM
}

int main()
{
    if (signal(SIGINT, sig_handler1) == SIG_ERR) {
        fprintf(stderr, "Cannot handle SIGINT\n");
        exit(EXIT_FAILURE);
    }

    if (signal(SIGTERM, sig_handler3) == SIG_ERR) {
        fprintf(stderr, "Cannot handle SIGTERM\n");
        exit(EXIT_FAILURE);
    }

    printf("process ID: %d\n", getpid());

    while (1)
    {
        printf("Running...\n");
        sleep(2);
    }

    return 0;
}

