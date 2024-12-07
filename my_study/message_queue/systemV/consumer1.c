#include<stdio.h>
#include<sys/ipc.h>
#include<sys/msg.h>
#include<signal.h>
#include<stdlib.h>
#include<string.h>
struct message_buffer
{
    /* data */
    long msg_type;
    char msg_text[100];
} message;
 void sig_handle(int signo)
 {
    printf("\nExit process....\n");
    exit(1);
 }
int main()
{
    key_t key;
    int msgid;
    signal(SIGINT, sig_handle);
    key  = ftok("progfile", 65); // create key

    msgid = msgget(key, IPC_CREAT | 0666); // create message queue
    while(1)
    {
    msgrcv(msgid, &message, sizeof(message), 1, 0); //read data from message queue

    // print data
    printf("Data from message queue: data type: %ld, message: %s\n", message.msg_type, message.msg_text);

    if(strncmp("exit", message.msg_text,4) == 0)
    {
        raise(SIGINT);
    }
    }

    // delete message queue

    msgctl(msgid, IPC_RMID, NULL);

    return 0;
}
