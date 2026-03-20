#include <iostream>
#include <pthread.h>
#include <semaphore.h>
#include <queue>
#include <unistd.h>
using namespace std;
queue<int> buffer;
pthread_mutex_t mtx;
sem_t empty_count; 
sem_t fill_count; 
void* producer(void* arg) {
    for (int i = 1; i <= 10; ++i) {
        sem_wait(&empty_count);
        pthread_mutex_lock(&mtx);
        buffer.push(i);
        cout << "Produced: " << i << " | Items in buffer: " << buffer.size() << endl;
        pthread_mutex_unlock(&mtx);
        sem_post(&fill_count);
        usleep(100000); 
    }
    return nullptr;
}
void* consumer(void* arg) {
    for (int i = 1; i <= 10; ++i) {
        sem_wait(&fill_count);
        pthread_mutex_lock(&mtx);
        int item = buffer.front();
        buffer.pop();
        cout << "Consumed: " << item << " | Items remaining: " << buffer.size() << endl;
        pthread_mutex_unlock(&mtx);
        sem_post(&empty_count);
        usleep(300000); 
    }
    return nullptr;
}

int main() {
    pthread_t prod_tid, cons_tid;
    pthread_mutex_init(&mtx, nullptr);
    sem_init(&empty_count, 0, 10); 
    sem_init(&fill_count, 0, 0);   
    pthread_create(&prod_tid, nullptr, producer, nullptr);
    pthread_create(&cons_tid, nullptr, consumer, nullptr);
    pthread_join(prod_tid, nullptr);
    pthread_join(cons_tid, nullptr);
    pthread_mutex_destroy(&mtx);
    sem_destroy(&empty_count);
    sem_destroy(&fill_count);
    return 0;
}