/*Write a C program to create a child process. Display different messages in parent
process and child process. Display PID and PPID of both parent and child process.
Block parent process until child completes using wait system call.*/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {
    pid_t pid;

    
    pid = fork();

    if (pid < 0) {
      
        perror("fork failed");
        exit(1);
    } 
    else if (pid == 0) {
   
        printf("Child Process:\n");
        printf("   PID  = %d\n", getpid());
        printf("   PPID = %d\n", getppid());
        printf("   Message: Hello from the child process!\n");
    } 
    else {
   
      
        wait(NULL); 

        printf("Parent Process:\n");
        printf("   PID  = %d\n", getpid());
        printf("   PPID = %d\n", getppid());
        printf("   Message: Child has finished. Hello from the parent process!\n");
    }

    return 0;
}