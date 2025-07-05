#include <math.h>
#include <stdio.h>
#include <stdlib.h>
//#include <stdlib.h>
#include <string.h>
#include "reg_utils.h"

int main(int argc, char *argv[]) {

    DataPoint *data_array;
    int num_data = 10000000;

    data_array = (DataPoint *)malloc(num_data * sizeof(DataPoint));

    initialize_data(num_data, data_array, 1.63, -1.3);

    // Open file for writing
    // los modos de un archivo son 'r' read y 'w' write
    FILE *file = fopen(argv[1], "w");
    // Check for errors
    if (file == NULL) {
        perror("Error opening file");
        return 1;
    }

    // Write the contents of data_array
    for (int i=0; i<num_data; i++) {
        fprintf(file, "%f, %f \n", data_array[i].x, data_array[i].y);
        
    }


    /*
    char line[1024];
    while (fgets(line, sizeof(line), file) != NULL) {
        printf("%s", line);
    }
    */

    // ALWAYS CLOSE THE FILE
    fclose(file);
    return 0;
}
