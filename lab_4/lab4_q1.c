/*Write a C program to create a child process. Display different messages in parent
process and child process. Display PID and PPID of both parent and child process.
Block parent process until child completes using wait system call.*/
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
int main(){
  pid_t pid;
  pid = fork();
  if(pid<0){
     fprintf(stderr, "fork failed");
     return 1;
  }
  else if (pid == 0){
     printf("Hello from the Child process\n");
     printf("Child PID: %d, Parent PID (PPID): %d\n", getpid(), getppid());
   }

   else{
    wait(NULL);
    printf("\nHello from the Parent process!\n");
    printf("Parent PID: %d, My Parent (Shell) PID: %d\n", getpid(), getppid());
    printf("Child process has finished execution.\n");
   }
   return 0;
}
