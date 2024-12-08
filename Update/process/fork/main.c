#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int agrc, char* argv[])
{
	pid_t child_pid;
	int cnt = 2;

	child_pid = fork();
	if(child_pid >= 0)
	{
		if(child_pid == 0)
		{
			printf(" I am children process. My PID: %d, My parent PID: %d \n", getpid(), getppid());
			printf("Counter : %d \n", cnt ++);
		}
		else{
			printf("I am parent process, my pid: %d \n", getpid());
			printf("Counter: %d\n", cnt --);
		}
	}
		else{
		perror("Fork() is fail\n");
	}
		return 0;

}
