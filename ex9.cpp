#include <iostream>
#include <thread>
#include <semaphore.h>

using namespace std;

const int NUM_THREADS = 2;

int sharedResource = 0;
int turn = 0;
sem_t semaphores[2];

void* threadFunction(void* arg) {
    int id = *(int*)arg;

    for (int i = 0; i < 5; ++i) {
        // Entry section
        sem_wait(&semaphores[id]);
        while (turn != id) {
            sem_post(&semaphores[id]);
            sem_wait(&semaphores[id]);
        }

        // Critical section
        cout << "Thread " << id << " is in critical section." << endl;
        sharedResource++;
        cout << "Shared resource value: " << sharedResource << endl;

        // Exit section
        turn = 1 - id;
        sem_post(&semaphores[1 - id]);
    }

    return nullptr;
}

int main() {
    pthread_t threads[NUM_THREADS];
    int threadIds[NUM_THREADS] = {0, 1};

    // Initialize semaphores
    sem_init(&semaphores[0], 0, 1);
    sem_init(&semaphores[1], 0, 0);

    // Create threads
    for (int i = 0; i < NUM_THREADS; ++i) {
        pthread_create(&threads[i], nullptr, threadFunction, &threadIds[i]);
    }

    // Join threads
    for (int i = 0; i < NUM_THREADS; ++i) {
        pthread_join(threads[i], nullptr);
    }

    // Destroy semaphores
    sem_destroy(&semaphores[0]);
    sem_destroy(&semaphores[1]);

    return 0;
}
