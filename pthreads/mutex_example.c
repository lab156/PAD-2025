/* -----------------------
 *
 * Elementary Mutex Usage with Race Conditions
 *   
 *   https://code-vault.net/lesson/
 *
 * ------------------------*/


#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>

// Note que log_cnt es un variable
int log_cnt = 0;
pthread_mutex_t mutex;

void* routine(void *arg) {
    for (int i = 0; i < 100000000; i++) {
        pthread_mutex_lock(&mutex);
        log_cnt++;
        pthread_mutex_unlock(&mutex);
        // read log_cnt
        // increment
        // write log_cnt
    }
    return NULL;
}

int main(int argc, char* argv[]) {
    pthread_t p1, p2, p3, p4;
    pthread_mutex_init(&mutex, NULL);
    if (pthread_create(&p1, NULL, &routine, NULL) != 0) {
        return 1;
    }
    if (pthread_create(&p2, NULL, &routine, NULL) != 0) {
        return 2;
    }
    if (pthread_create(&p3, NULL, &routine, NULL) != 0) {
        return 3;
    }
    if (pthread_create(&p4, NULL, &routine, NULL) != 0) {
        return 4;
    }
    if (pthread_join(p1, NULL) != 0) {
        return 5;
    }
    if (pthread_join(p2, NULL) != 0) {
        return 6;
    }
    if (pthread_join(p3, NULL) != 0) {
        return 7;
    }
    if (pthread_join(p4, NULL) != 0) {
        return 8;
    }
    pthread_mutex_destroy(&mutex);
    printf("Number of log_cnt: %d\n", log_cnt);
    return 0;
}
