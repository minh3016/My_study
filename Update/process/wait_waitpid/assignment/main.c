#include<stdio.h>
#include<stdlib.h>
#include<sys/wait.h>
#include<fcntl.h>
#include<string.h>
#define FILE_NAME "test.txt"

void write_to_file(const char *message) {
    int fd = open(FILE_NAME, O_WRONLY | O_APPEND | O_CREAT, 0644);
    if (fd == -1) {
        perror("open");
        exit(EXIT_FAILURE);
    }
    write(fd, message, strlen(message));
    write(fd, "\n", 1);
    close(fd);
}

int main(int argc, char* argv[]) {
    pid_t pid_B, pid_C;

    // Tạo tiến trình B
    pid_B = fork();
    if (pid_B == 0) {
        // Đây là tiến trình B
        pid_t pid_B_prime = fork();
        if (pid_B_prime == 0) {
            // Đây là tiến trình B'
	    printf("Writng in B' process \n");
	    sleep(5);
            write_to_file("Hello I'm B' process\n");
            exit(EXIT_SUCCESS);
        } else {
            // Đợi tiến trình B' kết thúc
            waitpid(pid_B_prime, NULL, 0);

	    printf("Writing in process B \n");
	    sleep(2);
            write_to_file("Hello I'm B process\n");
            exit(EXIT_SUCCESS);
        }
    }

    // Tạo tiến trình C
    pid_C = fork();
    if (pid_C == 0) {
        // Đây là tiến trình C
        pid_t pid_C_prime = fork();
        if (pid_C_prime == 0) {
            // Đây là tiến trình C'
	    printf("Writing in process C'\n");
	    sleep(5);
            write_to_file("Hello I'm C' process\n");
            exit(EXIT_SUCCESS);
        } else {
            // Đợi tiến trình C' kết thúc
            waitpid(pid_C_prime, NULL, 0);

	    printf("Writing in process C \n");
	    sleep(2);
            write_to_file("Hello I'm C process\n");
            exit(EXIT_SUCCESS);
        }
    }

    // Tiến trình A: Đợi tiến trình B kết thúc
    waitpid(pid_B, NULL, 0);

    printf("waiting B process terminate \n");
    sleep(2);
    write_to_file("Process B has finished, recorded by process A\n");

    // Đợi tiến trình C kết thúc (đảm bảo tiến trình A không kết thúc trước C)
    waitpid(pid_C, NULL, 0);
	printf("waiting C  process terminate \n");
    sleep(2);

    printf("All processes have finished. Check the file '%s'\n", FILE_NAME);

	return 0;
}
