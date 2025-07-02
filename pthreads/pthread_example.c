#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define NUM_THREADS 5

// This is the function that each thread will execute.
void *thread_function(void *arg) {
    long thread_id = (long)arg;
    printf("Thread %ld: Starting execution.\n", thread_id);
    // Simulate some work
    sleep(5);
    printf("Thread %ld: Finished execution.\n", thread_id);
    return (void *)(thread_id * 10); // Example of returning a value
}

int main() {
    pthread_t threads[NUM_THREADS];
    int rc;
    long t;
    void *ret_val;

    printf("Main: Creating %d threads.\n", NUM_THREADS);

    for (t = 0; t < NUM_THREADS; t++) {
        // pthread_create arguments:
        // 1. Pointer to pthread_t variable to store thread ID.
        // 2. Thread attributes (NULL for default).
        // 3. The function the thread will execute.
        // 4. The argument to pass to the thread function.
        rc = pthread_create(&threads[t], NULL, thread_function, (void *)t);
        if (rc) {
            printf("ERROR; return code from pthread_create() is %d\n", rc);
            exit(-1);
        }
    }

    printf("Main: All threads created. Waiting for them to finish.\n");

    // Wait for all threads to complete
    for (t = 0; t < NUM_THREADS; t++) {
        // pthread_join arguments:
        // 1. The thread ID to wait for.
        // 2. A pointer to store the return value from the thread function.
        rc = pthread_join(threads[t], &ret_val);
        if (rc) {
            printf("ERROR; return code from pthread_join() is %d\n", rc);
            exit(-1);
        }
        printf("Main: Joined with thread %ld, which returned %ld.\n", t, (long)ret_val);
    }

    printf("Main: All threads have completed. Exiting.\n");
    return 0;
}
