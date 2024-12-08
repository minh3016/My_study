#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<signal.h>


void sig_INT_handle(int signo)
{
	printf("Having sig INT....\n");
	exit(EXIT_SUCCESS);
}

void sig_TERM_handle(int signo)
{
	printf("Having sig TERM....\n");
	exit(EXIT_SUCCESS);
}

int main()
{
	struct sigaction sa_INT, sa_TERM;


	sa_INT.sa_handler = sig_INT_handle;
	sigemptyset(&sa_INT.sa_mask);
	sa_INT.sa_flags = 0;
	sigaction(SIGINT, &sa_INT,NULL);


	sa_TERM.sa_handler = sig_TERM_handle;
	sigemptyset(&sa_TERM.sa_mask);
	sa_TERM.sa_flags = 0;
	sigaction(SIGTERM, &sa_TERM, NULL);


	printf("Runing main programing. Sending SIGINT or SIGTERM....\n");

	while(1)
	{
		sleep(1);
	}
	return 0;
}
