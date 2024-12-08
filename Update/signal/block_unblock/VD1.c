#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<signal.h>

void sig_handle(int signo)
{
	printf("Hello i am sig handle\n");
	exit(EXIT_SUCCESS);
}

int main()
{
	struct sigaction sa;
	sigset_t newMask, oldMask;

	sa.sa_handler = sig_handle;

	sigemptyset(&sa.sa_mask);

	sa.sa_flags = 0;

	sigaction(SIGTERM, &sa, NULL);

	sigemptyset(&newMask);
	sigaddset(&newMask,SIGTERM);

	sigprocmask(SIG_BLOCK, &newMask, &oldMask);

	printf("Blocking sig term .....\n");

	sleep(30);

	sigprocmask(SIG_SETMASK, &oldMask, NULL);

	printf("Un blocking sig term .... \n");

	pause();
	return 0;
}
