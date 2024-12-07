#include<stdio.h>
#include<sys/ipc.h>
#include<sys/msg.h>

#define BUFFER_SIZE 100

struct message_buffer
{
    /* data */
    long msg_type;
    char msg_text[100];
} message;

int main()
{

    key_t key;
    int msgid;
    key = ftok("progfile", 65);
    msgid = msgget(key, IPC_CREAT | 0666);
    while (1)
    
        /* code */
    {
    
    printf("enter message type: ");
    scanf("%ld", &message.msg_type);

    stdin = freopen(NULL,"r",stdin);

    printf("enter message for message queue: ");
    fgets(message.msg_text, BUFFER_SIZE, stdin);

    msgsnd(msgid, &message, sizeof(message), 0);
    }

    
    return 0;
}

