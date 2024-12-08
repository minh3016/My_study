#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
void sig_term_handle(int signo)
{
	printf("I am sig term handle\n");
	exit(EXIT_SUCCESS);
}
int main() {
    pid_t pid;
    int status;
    int cnt = 0;
//	signal(SIGTERM, sig_term_handle);
	while(cnt < 5)
	{
	printf("runing\n");
	cnt++;
	sleep(1);
	}
	sleep(5);
    pid = getpid();
    
    status = kill(pid, SIGTERM);
    
    if (status == 0) {
        printf("Sending signal success, pid:  %d\n", pid);
    } else {
        perror("sending signal fail\n");
    }

    return 0;
}

