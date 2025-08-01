#include <stdio.h>
#include "lapacke.h"
#include <stdio.h>
//#include <time.h>
#include <string.h>
#include <sys/time.h>

int main(int argc, char *argv[]) {
    // Inputs: The path of a CSV file with (x,y) data for linear regression.
    //
    // Input matrix A (column-major)
    //double a[6] = {12.0, 16.0, 18.0, 14.0, 16.0, 16.0};
    //lapack_int m = 3, n = 2, nrhs = 1, lda = 3;

    // Input matrix B (column-major)
    //double b[3] = {14.0, 18.0, 16.0};
    //lapack_int ldb = 3;
    struct timeval start_time, stop_time, elapsed_time;  // timers

    int num_data_points = 0;
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
    // set the dimension for a b 
    double a[2*num_data_points];
    double b[num_data_points];
    lapack_int m = num_data_points, n = 2, nrhs = 1, lda = 3;
    lapack_int ldb = num_data_points;


    char line[1024];
    char *str, *endPtr;
    int file_ind = 0;
    while (fgets(line, sizeof(line), file) != NULL) {
        str = strdup(line);
        // split the line on the comma and 
        // convert to double (x)
        a[file_ind] = strtod(
                   strsep(&str, ","), 
                   &endPtr);
        // convert to double (y)
        b[file_ind] = strtod(
                    strsep(&str, ","),
                    &endPtr);
        //printf("El resultado es: \n");
        //printf("x = %f  and y = %f", data_array[file_ind].x , data_array[file_ind].y);
        //printf("\n");
        file_ind++;
    }

    // cerrar el archivo
    fclose(file);

    // fill the column of 1s
    for (int i=num_data_points; i< 2*num_data_points; i++)  a[i] = 1.0;

    // Call LAPACKE_dgels
    int info = LAPACKE_dgels(LAPACK_COL_MAJOR, 'N', m, n, nrhs, a, lda, b, ldb);

    if (info == 0) {
        // Print the solution
        printf("Solution:\n");
        for (int i = 0; i < n; i++) {
            printf("x[%d] = %f\n", i, b[i]);
        }
    } else {
        printf("LAPACKE_dgels failed with error code %d\n", info);
    }

    return 0;
}
