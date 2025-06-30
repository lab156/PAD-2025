#include <pthread.h>
#include <stdio.h>

void* foo(void* arg) {
    printf("Created a new thread. \n");
    return NULL;
 }

int main() {
    // Create a pthread_t variable to store
    // thread ID
    pthread_t thread1;
    
    // Creating a new thread. 
    pthread_create(&thread1, NULL, foo, NULL);

    // Wait for the thread to finish
    pthread_join(thread1, NULL);

    return 0;
}
