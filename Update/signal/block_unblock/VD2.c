#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<signal.h>


void sig_handle(int signo)
{
	printf("Hello i am in sig QUIT handle...\n");
	exit(EXIT_SUCCESS);
}

int main()

{
	struct sigaction sa;
	sigset_t new_set, old_set;

	sa.sa_handler = sig_handle;
	sigemptyset(&sa.sa_mask);

	sa.sa_flags = 0;

	sigaction(SIGQUIT, &sa, NULL);

	sigemptyset(&new_set);
	sigemptyset(&old_set);
	sigaddset(&new_set,SIGINT);
	sigaddset(&new_set,SIGQUIT);


	sigprocmask(SIG_BLOCK,&new_set,&old_set);

	printf("Blocking sig int and sig quit .... \n");

	sleep(15);

	sigprocmask(SIG_UNBLOCK, &new_set, NULL);

	printf("Unblocking sig quit .... \n");

	pause();
	return 0;
}
