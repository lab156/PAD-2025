#include <stdio.h>
#include "lapacke.h"
#include <stdio.h>
//#include <time.h>
#include <string.h>
#include <sys/time.h>

int main(int argc, char *argv[]) {
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
    double *a;
    a = (double *)malloc(2*num_data_points * sizeof(double));
    double *b;
    b = (double *)malloc(num_data_points * sizeof(double));
    lapack_int m = num_data_points, n = 2, nrhs = 1;
    lapack_int lda = num_data_points;
    lapack_int ldb = num_data_points;

    printf(" 'num_data_points' es: %d\n", num_data_points);

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
        file_ind++;
    }

    // cerrar el archivo
    fclose(file);
    //

    // fill the column of 1s
    for (int i=num_data_points; i< 2*num_data_points; i++)  a[i] = 1.0;

    
    // register BEGIN time 
    gettimeofday(&start_time,NULL); // Unix timer

    // Call LAPACKE_dgels
    int info = LAPACKE_dgels(LAPACK_COL_MAJOR, 'N', m, n, nrhs, a, lda, b, ldb);
    //
    // Register END time subtract routine
    gettimeofday(&stop_time,NULL);
    timersub(&stop_time, &start_time, &elapsed_time); 

    printf("\nTotal time was %f seconds.\n", 
            elapsed_time.tv_sec+elapsed_time.tv_usec/1000000.0);

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
