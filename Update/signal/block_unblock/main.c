#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<signal.h>

void signal_handle(int signo)
{
	printf("I am signal handle, my sig number: %d\n", signo);
	exit(EXIT_SUCCESS);
}

int main()
{
	sigset_t new_set, old_set;

	if(signal(SIGINT,signal_handle) == SIG_ERR)
	{
		fprintf("Can not handle sig int\n");
		exit(EXIT_FAILURE);
	}

	sigemptyset(&new_set);
	sigemptyset(&old_set);

	sigaddset(&new_set,SIGINT);

	if(sigpromask(SIGINT,&new_set,&old_set) == -1)
	{
		fprintf("
