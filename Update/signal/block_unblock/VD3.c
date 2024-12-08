#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<signal.h>

void sig_handle(int signo)
{
	printf("hello I am wating signal handler.... \n");
	exit(EXIT_SUCCESS);
}


int main()
{
	struct sigaction sa;

	sigset_t new_set, pending;
	 sa.sa_handler = sig_handle;
	 sigemptyset(&sa.sa_mask);
	 sa.sa_flags = 0;

	 sigaction(SIGINT,&sa, NULL);

	 sigemptyset(&new_set);
	 sigaddset(&new_set, SIGINT);

	 sigprocmask(SIG_BLOCK, &new_set, NULL);

	 printf("Blocking sig int.....\n");


	 sleep(10);

	 sigpending(&pending);

	 if(sigismember(&pending, SIGINT))
	 {
		 printf("Sig int waiting....\n");
	 }
	 else
	 {
		 printf("No have sig int pending....\n");
	 }
	sigprocmask(SIG_UNBLOCK, &new_set, NULL);
	printf("Un blocking sig int....\n");
	 pause();

	 return 0;
}
