#include <stdlib.h>
#include <math.h>
#include <sys/time.h>
#include <time.h>
// Includes sleep function, only for Linux
// In Windows use Windows.h and function called Sleep(milliseconds)
#include <unistd.h>
#include <stdio.h>

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

        if ((epoch + 1) % (epochs / 10) == 0 || epoch == 0) {
            double mse = 0.0;
            for (int i = 0; i < num_data; i++) {
                double y_predicted = (*m_estimated) * data_array[i].x + (*b_estimated);
                mse += pow(data_array[i].y - y_predicted, 2);
            }
            mse /= num_data;
           // printf("Epoch %d/%d: m_est = %.4f, b_est = %.4f, MSE = %.4f\n",
           //        epoch + 1, epochs, *m_estimated, *b_estimated, mse);
        }
    }
}
