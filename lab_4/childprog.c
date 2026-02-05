#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h> 

int main() {
    pid_t pid = fork();

    if (pid < 0) {
        perror("fork failed");
        return 1;
    }

    if (pid > 0) {
        printf("[Parent] PID: %d. Created Zombie: %d\n", getpid(), pid);
        printf("[Parent] I am sleeping for 20 seconds. Check 'ps -l' now.\n");
        
        sleep(20); 
        
        printf("[Parent] Terminating now. Zombie %d will be adopted by init.\n", pid);
        exit(0); 
    } else {
        // Child exits immediately to become zombie
        exit(0); 
    }
}