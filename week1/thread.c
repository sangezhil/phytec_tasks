#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

// Function to be run by the first thread
void* task1(void* arg) {
    for (int i = 0; i < 5; i++) {
        printf("Thread 1: Count %d\n", i);
        sleep(1); // Sleep for 1 second
    }
    return NULL;
}

// Function to be run by the second thread
void* task2(void* arg) {
    for (int i = 0; i < 5; i++) {
        printf("Thread 2: Count %d\n", i);
        sleep(1); // Sleep for 1 second
    }
    return NULL;
}

int main() {
    pthread_t t1, t2; // Declare thread identifiers

    // Create two threads
    pthread_create(&t1, NULL, task1, NULL);
    pthread_create(&t2, NULL, task2, NULL);
	
    
    // Wait for both threads to finish
   pthread_join(t1, NULL);
   pthread_join(t2, NULL);

    printf("Main thread: All threads finished.\n");
    return 0;
}

