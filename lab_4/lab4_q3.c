/*Create a zombie (defunct) child process (a child with exit() call, but no
corresponding wait() in the sleeping parent) and allow the init process to adopt it
(after parent terminates). Run the process as background process and run “ps”
command.*/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>

int main() {
    int duration;
    pid_t pid;
    printf("Enter number of seconds for the parent to sleep: ");
    if (scanf("%d", &duration) != 1) {
        printf("Invalid input.\n");
        return 1;
    }
    pid = fork();
    if (pid < 0) {
        perror("Fork failed");
        exit(1);
    }
    if (pid == 0) {
        printf("\n[Child] PID: %d. Exiting now to become a ZOMBIE...\n", getpid());
        exit(0);
    } else {
        printf("Parent PID: %d. Created child PID: %d.\n", getpid(), pid);
        printf("Parent I am sleeping for %d seconds. Run 'ps -l' now to see <defunct>.\n", duration);
        sleep(duration);
        printf("\nParent Exiting. Child (PID %d) will now be adopted by init/systemd.\n", pid);
    }

    return 0;
}

