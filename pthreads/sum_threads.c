#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>


// Argumentos de un thread
struct thread_arg{
   int id; // identidad de cada hilo
   double *subarray; // arreglo que le toca sumar al hilo
   int subarray_len; // longitud del arreglo subarray
   double total; // el total de la suma para el return de la funcion
};


// This is the function that each thread will execute.
void *thread_function(void *arg) {
    struct thread_arg *targ;
    targ = (struct thread_arg *)arg; // cast a apuntador a thread_arg
                                     //
    printf("Thread %d: Starting execution.\n", targ->id);
    targ->total = 0;
    for (int i = 0; i < targ->subarray_len; i++){
        //targ->total += targ->subarray[10*(targ->id) + i];
        targ->total += targ->subarray[i];
    }
    printf("Thread %d: Finished execution.\n", targ->id);
    return (void *)(targ); 
}

int main() {
    int NUM_THREADS = 5;
    pthread_t threads[NUM_THREADS];
    int rc; // sirve para revisar si el hilo se creo directamente
    void *ret_val;
    struct thread_arg arg[NUM_THREADS];

    double array[50];
    for (int i = 0; i<50; i++) {
        array[i] = i+1;
    }

    printf("Main: Creating %d threads.\n", NUM_THREADS);

    for (int i = 0; i < NUM_THREADS; i++) {
        // pthread_create arguments:
        // 1. Pointer to pthread_t variable to store thread ID.
        // 2. Thread attributes (NULL for default).
        // 3. The function the thread will execute.
        // 4. The argument to pass to the thread function.
        //struct thread_arg *arg;
        arg[i].id = i;
        arg[i].subarray = array + 10*i;
        arg[i].subarray_len = 10;
        arg[i].total = 0;

        printf("Comenzando thread %d \n", i);
        // ahora creamos los hilos
        rc = pthread_create(&threads[i], 
                NULL,
                thread_function,
                (void *)(arg + i));
        if (rc) {
            printf("ERROR; return code from pthread_create() is %d\n", rc);
            exit(-1);
        }
    }

    printf("Main: All threads created. Waiting for them to finish.\n");

    // Wait for all threads to complete
    double grand_total = 0;
    for (int i = 0; i < NUM_THREADS; i++) {
        // pthread_join arguments:
        // 1. The thread ID to wait for.
        // 2. A pointer to store the return value from the thread function.
        rc = pthread_join(threads[i], &ret_val);
        if (rc) {
            printf("ERROR; return code from pthread_join() is %d\n", rc);
            exit(-1);
        }
        struct thread_arg *ret_;
        ret_ = (struct thread_arg *) ret_val;
        //double *ret_;
        //ret_ = (double *) ret_val;

        grand_total += ret_->total;


        printf("Main: Joined with thread %d, which returned %f.\n", 
                ret_->id, ret_->total);
    }

    printf("Main: All threads have completed. The total is %f Exiting.\n",
            grand_total);
    return 0;
}
