#include <stdlib.h>
#include <math.h>
#include <sys/time.h>
#include <time.h>
// Includes sleep function, only for Linux
// In Windows use Windows.h and function called Sleep(milliseconds)
#include <unistd.h>
#include <stdio.h>
#include <pthread.h>
#include <omp.h>

//cambio sin importancia
double random_double() {
    return (double)rand() / RAND_MAX;
}

// Function to generate random number from a normal distribution 
// (Box-Muller transform)
double random_normal(double mean, double stddev) {
    static int has_spare = 0;
    static double spare;

    if (has_spare) {
        has_spare = 0;
        return mean + stddev * spare;
    }

    has_spare = 1;
    double u1, u2;
    do {
        u1 = random_double();
        u2 = random_double();
    } while (u1 <= 1e-9); // Avoid log(0)

    spare = sqrt(-2.0 * log(u1)) * cos(2.0 * M_PI * u2);
    return mean + stddev * (sqrt(-2.0 * log(u1)) * sin(2.0 * M_PI * u2));
}

// Structure to hold data points
typedef struct {
    double x;
    double y;
} DataPoint;


// Function to initialize data
void initialize_data(int num_data, DataPoint *data_array, double m_true, double b_true) {
    if (data_array == NULL) {
        fprintf(stderr, "Memory allocation failed for data_array\n");
        exit(EXIT_FAILURE);
    }

    srand(time(NULL)); // Seed the random number generator
    //srand(rand_seed); // Seed the random number generator

    for (int i = 0; i < num_data; i++) {
        data_array[i].x = random_double(); // x values between 0 and 1
        double y_exact = m_true * data_array[i].x + b_true;
        // Add Gaussian noise (mean 0, standard deviation e.g., 0.1)
        data_array[i].y = y_exact + random_normal(0.0, 0.1);
    }
    printf("Data initialized with %d points based on m=%.2f, b=%.2f (with noise).\n", num_data, m_true, b_true);
}



// Function to perform gradient descent
void gradient_descent(int num_data, double learning_rate, int epochs, 
    double *m_estimated, double *b_estimated, DataPoint *data_array) {
    printf("\nStarting Gradient Descent...\n");
    // Initialize parameters
    *m_estimated = 0.0;
    *b_estimated = 0.0;

    for (int epoch = 0; epoch < epochs; epoch++) {
        double m_gradient = 0.0;
        double b_gradient = 0.0;

        for (int i = 0; i < num_data; i++) {
            double x_i = data_array[i].x;
            double y_i = data_array[i].y;
            double y_predicted = (*m_estimated) * x_i + (*b_estimated);

            // Partial derivatives of the Mean Squared Error cost function
            // d(MSE)/dm = -2/N * sum(x_i * (y_i - y_predicted))
            // d(MSE)/db = -2/N * sum(y_i - y_predicted)
            m_gradient += -2 * x_i * (y_i - y_predicted);
            b_gradient += -2 * (y_i - y_predicted);
        }

        // Average the gradients
        m_gradient /= num_data;
        b_gradient /= num_data;

        // Update parameters
        *m_estimated -= learning_rate * m_gradient;
        *b_estimated -= learning_rate * b_gradient;

        if ((epoch + 1) % (epochs/2) == 0 || epoch == 0) {
            double mse = 0.0;
            for (int i = 0; i < num_data; i++) {
                double y_predicted = (*m_estimated) * data_array[i].x 
                                          + (*b_estimated);
                mse += pow(data_array[i].y - y_predicted, 2);
            }
            mse /= num_data;
            printf("Epoch %d/%d: m_est = %.4f, b_est = %.4f, MSE = %.4f\n",
                   epoch + 1, epochs, *m_estimated, *b_estimated, mse);
        }
    }
}


// Argumentos de un thread
struct thread_arg{
   int id; // identidad de cada hilo
   DataPoint *subarray; // arreglo que le toca sumar al hilo
   int subarray_len; // longitud del arreglo subarray
   double m_estimated;
   double b_estimated;
   double m_gradient;   // = 0 por que son salida
   double b_gradient;
};


// This is the function that each thread will execute.
void *thread_sum(void *arg) {
    struct thread_arg *targ;
    targ = (struct thread_arg *)arg; // cast a apuntador a thread_arg
                                     //
    for (int i = 0; i < targ->subarray_len; i++){
        double y_predicted = (targ->m_estimated)*(targ->subarray[i].x) 
            + (targ->b_estimated);
        //targ->total += targ->subarray[10*(targ->id) + i];
        targ->b_gradient += targ->subarray[i].y - y_predicted;
        targ->m_gradient += 
            (targ->subarray[i].x)*(targ->subarray[i].y - y_predicted);
    }
        targ->m_gradient *= -2.0;
        targ->b_gradient *= -2.0;
    return (void *)(targ); 
}

void thread_gradient_descent(int num_data, double learning_rate, int epochs, 
    double *m_estimated, double *b_estimated, DataPoint *array) {
    int NUM_THREADS = 14;
    printf("\nStarting Thread Gradient Descent with %d threads\n", 
            NUM_THREADS);
    // Initialize parameters
    *m_estimated = 0.0;
    *b_estimated = 0.0;

    for (int epoch = 0; epoch < epochs; epoch++) {
        double m_gradient = 0.0;
        double b_gradient = 0.0;

        pthread_t threads[NUM_THREADS];
        int rc; // sirve para revisar si el hilo se creo directamente
        void *ret_val;
        struct thread_arg arg[NUM_THREADS];


        for (int i = 0; i < NUM_THREADS; i++) {
            // Set the arguments for thread_function
            arg[i].id = i;
            arg[i].subarray = array + (num_data/NUM_THREADS)*i;
            arg[i].subarray_len = (num_data/NUM_THREADS);
            if (i == NUM_THREADS - 1) {
                arg[i].subarray_len += num_data%NUM_THREADS;
            }
            arg[i].m_estimated = *m_estimated;
            arg[i].b_estimated = *b_estimated;
            arg[i].m_gradient = 0.0;
            arg[i].b_gradient = 0.0;

            // pthread_create arguments:
            // 1. Pointer to pthread_t variable to store thread ID.
            // 2. Thread attributes (NULL for default).
            // 3. The function the thread will execute.
            // 4. The argument to pass to the thread function.
            //struct thread_arg *arg;
            rc = pthread_create(&threads[i], 
                    NULL,
                    thread_sum,
                    (void *)(arg + i));
            if (rc) {
                printf("ERROR; return code from pthread_create() is %d\n", rc);
                exit(-1);
            }
        }


        // JOIN THE THREADS
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
            //
            // Average the gradients
            m_gradient += (ret_->m_gradient)/num_data;
            b_gradient += (ret_->b_gradient)/num_data;

        }

        // Update parameters
        *m_estimated -= learning_rate * m_gradient;
        *b_estimated -= learning_rate * b_gradient;

    if ((epoch + 1) % (epochs/2) == 0 || epoch == 0) {
        double mse = 0.0;
        for (int i = 0; i < num_data; i++) {
            double y_predicted = (*m_estimated) * array[i].x 
                                      + (*b_estimated);
            mse += pow(array[i].y - y_predicted, 2);
        }
        mse /= num_data;
        printf("Epoch %d/%d: m_est = %.4f, b_est = %.4f, MSE = %.4f\n",
               epoch + 1, epochs, *m_estimated, *b_estimated, mse);
    }
    }
}


void omp_gradient_descent(int num_data, double learning_rate, int epochs, 
    double *m_estimated, double *b_estimated, DataPoint *data_array) {
    printf("\nStarting Gradient Descent...\n");
    // Initialize parameters
    *m_estimated = 0.0;
    *b_estimated = 0.0;

    for (int epoch = 0; epoch < epochs; epoch++) {
        double m_gradient = 0.0;
        double b_gradient = 0.0;

        #pragma omp parallel for reduction(+:m_gradient, b_gradient)
        for (int i = 0; i < num_data; i++) {
            double x_i = data_array[i].x;
            double y_i = data_array[i].y;
            double y_predicted = (*m_estimated) * x_i + (*b_estimated);

            // Partial derivatives of the Mean Squared Error cost function
            // d(MSE)/dm = -2/N * sum(x_i * (y_i - y_predicted))
            // d(MSE)/db = -2/N * sum(y_i - y_predicted)
            m_gradient += -2 * x_i * (y_i - y_predicted);
            b_gradient += -2 * (y_i - y_predicted);
        }

        // Average the gradients
        m_gradient /= num_data;
        b_gradient /= num_data;

        // Update parameters
        *m_estimated -= learning_rate * m_gradient;
        *b_estimated -= learning_rate * b_gradient;

        if ((epoch + 1) % (epochs/2) == 0 || epoch == 0) {
            double mse = 0.0;
            for (int i = 0; i < num_data; i++) {
                double y_predicted = (*m_estimated) * data_array[i].x 
                                          + (*b_estimated);
                mse += pow(data_array[i].y - y_predicted, 2);
            }
            mse /= num_data;
            printf("Epoch %d/%d: m_est = %.4f, b_est = %.4f, MSE = %.4f\n",
                   epoch + 1, epochs, *m_estimated, *b_estimated, mse);
        }
    }
}
