#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/wait.h>
int main(int argc, char* argv[])
{

	pid_t chil_process1, chil_process2;
	int status, return_value;

	chil_process1 = fork();
//	chil_process2 = fork();
	if(chil_process1 >= 0)
	{
	if(chil_process1 == 0)
	{

		printf("I am children  process 1, my pid: %d, my parent pid: %d\n", getpid(),getppid());

		printf("Child process 1 will terminate in 5 second\n");
		sleep(5);
		exit(EXIT_FAILURE);
	}

	else {

		return_value = waitpid(chil_process1,&status,0);
		if(return_value == -1)
		{
		printf("waitpid() fail\n");
	
		}
		printf("I am parent process, my children pid: %d\n", return_value);
		}
	}
	else{
		printf("Fork() fail\n");
	}
	while(1);
	return 0;
}

