#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include "lab6_q1_msg_structure.h"
int main() {
    key_t key;
    int msgid;
    struct msg_buffer message;
    key = ftok("progfile", 65);
    msgid = msgget(key, 0666 | IPC_CREAT);
    message.msg_type = 1;
    printf("Process A: Enter a number to send: ");
    scanf("%d", &message.number);
    msgsnd(msgid, &message, sizeof(message.number), 0);
    printf("Data sent to Process B: %d\n", message.number);
    return 0;
}