#include<stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

int main(int argc, char* argv[])
{
	printf("Run command line ls -lah after 5 seconds\n");

	sleep(5);

	printf("Kill current process\n");
	//kill(getpid(), SIGKILL);

	//execl("/bin/ls", "ls", "-l","-a","-h",NULL);

	int cnt = 5;
	while(cnt > 0)
	{
		printf("I am coutinggggg\n");
		cnt --;
	}
	return 0;


}
