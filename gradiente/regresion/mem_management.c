#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <sys/time.h>
// Includes sleep function, only for Linux
// In Windows use Windows.h and function called Sleep(milliseconds)
#include <unistd.h>
#include "reg_utils.h"


// Structure to hold data points
typedef struct {
    double x;
    double y;
} DataPoint;

// Global array to store data points
DataPoint *data_array;


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

int main () {
    // --- Configuration ---
    int num_data_points = 1000000;  // Number of data points to generate
    double true_slope = 2.5;     // True slope of the line
    double true_intercept = 1.0; // True y-intercept of the line


    // --- Initialize Data ---
    initialize(num_data_points, true_slope, true_intercept);

    printf("Done initialize, sleeping for 5 seconds. \n");
    sleep(5);
    // --- Cleanup ---
    printf("Cleaning up. \n");
    free(data_array);

    sleep(5);
    printf("Initialize again ----- \n");
    initialize(num_data_points, true_slope, true_intercept);

    sleep(5);
    free(data_array);

    return 0;
}

