#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/shm.h>
#include <sys/ipc.h>
#include <sys/wait.h>

struct shared_data {
    char alphabet;
    int status; 
};

int main() {
    int shmid;
    struct shared_data *shm_ptr;
    key_t key = ftok("shmfile", 77); 

    shmid = shmget(key, sizeof(struct shared_data), 0666 | IPC_CREAT);
    shm_ptr = (struct shared_data *)shmat(shmid, NULL, 0);   
    
    shm_ptr->status = 0; 
    
    pid_t pid = fork();

    if (pid > 0) {
        char input;
        printf("Parent: Enter an English alphabet: ");
        scanf(" %c", &input);
        
        shm_ptr->alphabet = input;
        shm_ptr->status = 1;
        
        printf("Parent: Sent '%c'. Waiting for Child...\n", input);
        
        while (shm_ptr->status != 0) {
            usleep(100); 
        }

        printf("Parent: Received reply from Child: '%c'\n", shm_ptr->alphabet);   
        
        wait(NULL); 
        shmdt(shm_ptr);
        shmctl(shmid, IPC_RMID, NULL); 
    } 
    else if (pid == 0) {
      
        while (shm_ptr->status != 1) {
            usleep(100);
        }
        
        printf("Child: Received '%c'. Processing next alphabet...\n", shm_ptr->alphabet);
        
        shm_ptr->alphabet = shm_ptr->alphabet + 1;
        shm_ptr->status = 0;
        
        shmdt(shm_ptr);
        exit(0);
    }

    return 0;
}