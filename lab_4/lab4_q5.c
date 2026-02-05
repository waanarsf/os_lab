#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

typedef struct {
    unsigned long long *fib;   
    int n;      
} FibData;

void* generate_fibonacci(void* arg) {
    FibData *data = (FibData*) arg;

    if (data->n > 0) data->fib[0] = 0;
    if (data->n > 1) data->fib[1] = 1;

    for (int i = 2; i < data->n; i++) {
        data->fib[i] = data->fib[i-1] + data->fib[i-2];
    }

    pthread_exit(NULL);
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Usage: %s <number_of_terms>\n", argv[0]);
        return 1;
    }

    int n = atoi(argv[1]);
    if (n <= 0) {
        printf("Number of terms must be a positive integer.\n");
        return 1;
    }

    unsigned long long *fib = malloc(n * sizeof(unsigned long long));
    if (fib == NULL) {
        perror("Failed to allocate memory");
        return 1;
    }

    FibData data;
    data.fib = fib;
    data.n = n;

    pthread_t tid;

    if (pthread_create(&tid, NULL, generate_fibonacci, &data) != 0) {
        fprintf(stderr, "Error: Could not create thread\n");
        free(fib);
        return 1;
    }

    printf("Parent: Waiting for child thread to generate sequence\n");
    pthread_join(tid, NULL);

    printf("Fibonacci series (%d terms):\n", n);
    for (int i = 0; i < n; i++) {
        printf("%llu ", fib[i]);
    }
    printf("\n");

    // 7. Cleanup
    free(fib);
    return 0;
}
/*
for output use:
gcc lab4_q5.c -o lab4_q5 -lpthread
./lab4_q5 5
*/