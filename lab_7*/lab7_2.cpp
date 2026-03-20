#include <iostream>
#include <pthread.h>
#include <semaphore.h>
#include <vector>
#include <unistd.h>

using namespace std;
sem_t rw_mutex;    
sem_t mtx;         
int read_count = 0;
int shared_data = 0;

void* reader(void* arg) {
    int id = *((int*)arg);
    sem_wait(&mtx);
    read_count++;
    if (read_count == 1) {
        sem_wait(&rw_mutex); 
    }
    sem_post(&mtx);
    cout << "Reader " << id << " is reading data: " << shared_data << endl;
    usleep(500000); 

    sem_wait(&mtx);
    read_count--;
    if (read_count == 0) {
        sem_post(&rw_mutex);
    }
    sem_post(&mtx);

    return nullptr;
}

void* writer(void* arg) {
    int id = *((int*)arg);

    // Entry Section
    sem_wait(&rw_mutex);

    // Writing
    shared_data += 5; 
    cout << "Writer " << id << " updated data to: " << shared_data << endl;
    usleep(500000); // Simulate writing time

    // Exit Section
    sem_post(&rw_mutex);

    return nullptr;
}

int main() {
    int num_readers, num_writers;

    cout << "Enter number of Readers: ";
    cin >> num_readers;
    cout << "Enter number of Writers: ";
    cin >> num_writers;

    // Initialize Semaphores
    sem_init(&rw_mutex, 0, 1);
    sem_init(&mtx, 0, 1);

    vector<pthread_t> r_threads(num_readers);
    vector<pthread_t> w_threads(num_writers);
    vector<int> r_ids(num_readers);
    vector<int> w_ids(num_writers);

    // Create Reader Threads
    for (int i = 0; i < num_readers; i++) {
        r_ids[i] = i + 1;
        pthread_create(&r_threads[i], nullptr, reader, &r_ids[i]);
    }

    // Create Writer Threads
    for (int i = 0; i < num_writers; i++) {
        w_ids[i] = i + 1;
        pthread_create(&w_threads[i], nullptr, writer, &w_ids[i]);
    }

    // Join Threads
    for (int i = 0; i < num_readers; i++) pthread_join(r_threads[i], nullptr);
    for (int i = 0; i < num_writers; i++) pthread_join(w_threads[i], nullptr);

    // Cleanup
    sem_destroy(&rw_mutex);
    sem_destroy(&mtx);

    cout << "Simulation finished. Final data value: " << shared_data << endl;

    return 0;
}