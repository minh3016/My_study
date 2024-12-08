#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<signal.h>

static void signal_handler(int signal_number)
{
	printf("\nSignal handler 1\n");
	exit(EXIT_SUCCESS);
}

int main(int argc, const char *argv[])
{
	signal(SIGINT, signal_handler);

	while (1)
	{
		printf("Hello world\n");
		sleep(2);
	}
	return 0;
}
