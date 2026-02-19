#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <unistd.h>
#include <sys/wait.h>

#define MAX_WORDS 5
#define MAX_LEN 20

struct shared_buffer {
    char words[MAX_WORDS][MAX_LEN];
    int ready; 
};

int main() {
    int shmid;
    struct shared_buffer *shm_ptr;
    key_t key = ftok("shm_words", 88);

    shmid = shmget(key, sizeof(struct shared_buffer), 0666 | IPC_CREAT);
    shm_ptr = (struct shared_buffer *)shmat(shmid, NULL, 0);
    shm_ptr->ready = 0; 

    pid_t pid = fork();

    if (pid > 0) { 
        printf("Producer: Enter %d words:\n", MAX_WORDS);
        for (int i = 0; i < MAX_WORDS; i++) {
            printf("Word %d: ", i + 1);
            scanf("%s", shm_ptr->words[i]);
        }

        shm_ptr->ready = 1;
        printf("Producer: Words written to shared memory.\n");

        wait(NULL); 
        shmdt(shm_ptr);
        shmctl(shmid, IPC_RMID, NULL);
        printf("Producer: Shared memory detached and deleted.\n");
    } 
    else if (pid == 0) { 
        while (shm_ptr->ready == 0) {
            usleep(1000); 
        }

        printf("\nConsumer: Reading words from shared memory:\n");
        for (int i = 0; i < MAX_WORDS; i++) {
            printf("Received: %s\n", shm_ptr->words[i]);
        }
        shmdt(shm_ptr);
        exit(0);
    }

    return 0;
}