/*
 *
 * IMPLEMENTACION DE GRADIENT DESCENT FOR LINEAR LINEAR REGRESSION
 * Using: Gemini 2.5 Pro:
 *  
 */


#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <sys/time.h>
#include "reg_utils.h"

// Structure to hold data points
/*
typedef struct {
    double x;
    double y;
} DataPoint;
*/

// Global array to store data points
DataPoint *data_array;

// Aqui iban random_double y random_normal

// Function to initialize data
void initialize(int num_data, double m_true, double b_true) {
    data_array = (DataPoint *)malloc(num_data * sizeof(DataPoint));
    if (data_array == NULL) {
        fprintf(stderr, "Memory allocation failed for data_array\n");
        exit(EXIT_FAILURE);
    }

    //srand(time(NULL)); // Seed the random number generator
    srand(444); // Seed the random number generator

    for (int i = 0; i < num_data; i++) {
        data_array[i].x = random_double(); // x values between 0 and 1
        double y_exact = m_true * data_array[i].x + b_true;
        // Add Gaussian noise (mean 0, standard deviation e.g., 0.1)
        data_array[i].y = y_exact + random_normal(0.0, 0.1);
    }
    printf("Data initialized with %d points based on m=%.2f, b=%.2f (with noise).\n", num_data, m_true, b_true);
}

// Function to perform gradient descent
void gradient_descent(int num_data, double learning_rate, int epochs, double *m_estimated, double *b_estimated) {
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

int main() {
    // --- Configuration ---
    int num_data_points = 1000000;  // Number of data points to generate
    double true_slope = 2.5;     // True slope of the line
    double true_intercept = 1.0; // True y-intercept of the line

    double learning_rate = 0.1; // Learning rate for gradient descent
    int epochs = 1000;          // Number of iterations for gradient descent
    
    struct timeval start_time, stop_time, elapsed_time;  // timers

    // --- Initialize Data ---
    initialize(num_data_points, true_slope, true_intercept);


    // --- Perform Gradient Descent ---

    gettimeofday(&start_time,NULL); // Unix timer
                                    
    double estimated_slope, estimated_intercept;
    printf("\nStarting Gradient Descent...\n");
    gradient_descent(num_data_points, learning_rate, epochs, &estimated_slope, &estimated_intercept);


    gettimeofday(&stop_time,NULL);
    timersub(&stop_time, &start_time, &elapsed_time); // Unix time subtract routine

    // --- Output Results ---
    printf("\n--- Results ---\n");
    printf("True Slope (m):         %.4f\n", true_slope);
    printf("Estimated Slope (m_est): %.4f\n", estimated_slope);
    printf("True Intercept (b):       %.4f\n", true_intercept);
    printf("Estimated Intercept (b_est): %.4f\n", estimated_intercept);

    // --- Calculate Final MSE ---
    double final_mse = 0.0;
    for (int i = 0; i < num_data_points; i++) {
        double y_predicted = estimated_slope * data_array[i].x + estimated_intercept;
        final_mse += pow(data_array[i].y - y_predicted, 2);
    }
    final_mse /= num_data_points;
    printf("Final Mean Squared Error: %.4f\n", final_mse);

    printf("\nTotal time was %f seconds.\n", 
            elapsed_time.tv_sec+elapsed_time.tv_usec/1000000.0);

    // --- Cleanup ---
    free(data_array);

    return 0;
}
