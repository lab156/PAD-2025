/* -------------------------
 *
 * Linear Regresion with arguments read from the command line
 *
 * ----------------------- */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
//#include <time.h>
#include <string.h>
#include <sys/time.h>
#include "reg_utils.h"



int main(int argc, char *argv[]) {
    // Inputs: The path of a CSV file with (x,y) data for linear regression.
    // --- Configuration ---
    int num_data_points = 0;  // Number of data points to generate

    double learning_rate = 0.1; // Learning rate for gradient descent
    int epochs = 1000;          // Number of iterations for gradient descent
    
    struct timeval start_time, stop_time, elapsed_time;  // timers

    // At least one argument is necessary 
    if (argc < 1) return 1;

    // Open file in read mode 'r'
    FILE *file = fopen(argv[1], "r");
    // Check for errors
    if (file == NULL) {
        perror("Error opening file");
        return 1;
    }
    // Read characters one by one until the End Of the File (EOF)
    char ch;
    while ((ch = fgetc(file)) != EOF) {
        // Increment count if a newline character is found
        if (ch == '\n') {
            num_data_points++;
        }
    }

    // Go back to the beginning of the file
    // file.seek(0); en C++
    rewind(file);

    // Now that we know the number of lines
    DataPoint *data_array;
    data_array = (DataPoint *)malloc(num_data_points * sizeof(DataPoint));

    char line[1024];
    char *str, *endPtr;
    int file_ind = 0;
    while (fgets(line, sizeof(line), file) != NULL) {
        str = strdup(line);
        // split the line on the comma and 
        // convert to double (x)
        data_array[file_ind].x = strtod(
                   strsep(&str, ","), 
                   &endPtr);
        // convert to double (y)
        data_array[file_ind].y = strtod(
                    strsep(&str, ","),
                    &endPtr);
        //printf("El resultado es: \n");
        //printf("x = %f  and y = %f", data_array[file_ind].x , data_array[file_ind].y);
        //printf("\n");
        file_ind++;
    }

    // cerrar el archivo
    fclose(file);
    // --- Perform Gradient Descent ---

    gettimeofday(&start_time,NULL); // Unix timer
                                    
    double estimated_slope, estimated_intercept;
    gradient_descent(num_data_points, learning_rate, epochs, &estimated_slope, &estimated_intercept, data_array);
    //thread_gradient_descent(num_data_points, learning_rate, epochs, &estimated_slope, &estimated_intercept, data_array);


    gettimeofday(&stop_time,NULL);
    timersub(&stop_time, &start_time, &elapsed_time); // Unix time subtract routine

    // --- Output Results ---
    printf("\n--- Results for file: %s ---\n", argv[1]);
    printf("Estimated Slope (m_est): %.4f\n", estimated_slope);
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
