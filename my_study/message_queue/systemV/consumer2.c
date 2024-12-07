#include<stdio.h>
#include<sys/ipc.h>
#include<sys/msg.h>

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
    while(1)
    {
    msgrcv(msgid, &message, sizeof(message), 2, 0);

    printf("Data from message queue: data type: %ld, message: %s\n", message.msg_type, message.msg_text);

   
    }
     msgctl(msgid, IPC_RMID, NULL);
    return 0;
}
