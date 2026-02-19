#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include "msg_structure.h"
int isPalindrome(int n) {
    int reversed = 0, remainder, original;
    original = n;
    while (n != 0) {
        remainder = n % 10;
        reversed = reversed * 10 + remainder;
        n /= 10;
    }
    return (original == reversed);
}

int main() {
    key_t key;
    int msgid;
    struct msg_buffer message;
    key = ftok("progfile", 65);
    msgid = msgget(key, 0666 | IPC_CREAT);
    msgrcv(msgid, &message, sizeof(message.number), 1, 0);
    printf("Process B: Received Number: %d\n", message.number);
    if (isPalindrome(message.number))
        printf("Result: The number is a Palindrome.\n");
    else
        printf("Result: The number is NOT a Palindrome.\n");
    msgctl(msgid, IPC_RMID, NULL);

    return 0;
}