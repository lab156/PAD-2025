#include <stdio.h>
#include <stdlib.h>
//#include <time.h>
#include <sys/time.h>
#include <mpi.h>
//#include "reg_utils.h"
#include <string.h>
//#include <omp.h>
//
// Structure to hold data points
typedef struct {
    double x;
    double y;
} DataPoint;

int main(int argc, char** argv) {
MPI_Init(&argc, &argv);

int world_size;
MPI_Comm_size(MPI_COMM_WORLD, &world_size);

int world_rank;
MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);

int num_data_points = 0;  // Number of data points to generate

const int nitems=2;
int          blocklengths[2] = {1,1};
MPI_Datatype types[2] = {MPI_DOUBLE, MPI_DOUBLE};
MPI_Datatype mpi_data_type;
MPI_Aint     offsets[2];

offsets[0] = offsetof(DataPoint, x);
offsets[1] = offsetof(DataPoint, y);

MPI_Type_create_struct(nitems, blocklengths, offsets, types, &mpi_data_type);
MPI_Type_commit(&mpi_data_type);


DataPoint *data_array;
int subarray_lens[world_size];
int subarray_disp[world_size];


// READ THE FILE
// Only rank = 0 reads the file
if (world_rank == 0) {
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
    int ch;
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
    printf("The num_data_points is: %d\n", num_data_points);
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
        file_ind++;
    }
    // cerrar el archivo
    fclose(file);

    for (int i = 0; i < world_size; i++) {
        subarray_lens[i] = (num_data_points/world_size);
        subarray_disp[i] = (num_data_points/world_size)*i;
        if (i == world_size - 1) {
             subarray_lens[i] += num_data_points%world_size;
        }
    }
}

// Broadcast the number of data points
MPI_Bcast(&num_data_points, 1, MPI_INT, 0, MPI_COMM_WORLD);

// Assign subalign length on each process
int subarray_len = (num_data_points/world_size);
if (world_rank == world_size - 1) {
     subarray_len += num_data_points%world_size;
}

// Allocate local arrays 
DataPoint *array;
array = (DataPoint *)malloc(subarray_len * sizeof(DataPoint));

MPI_Scatterv(data_array,
        subarray_lens,
        subarray_disp,
        mpi_data_type,
        array,
        subarray_len,
        mpi_data_type,
        0,
        MPI_COMM_WORLD
        );


/* -------------------------------------
 *   DONE READING DATA FROM FILE
 * -----------------------------------*/

MPI_Barrier(MPI_COMM_WORLD);
printf("Rank=%d  has Subarray length = %d\n", 
        world_rank, subarray_len);
printf("Rank=%d got 1st element x=%f, y=%f\n", 
        world_rank, array[0].x, array[0].y);

double x_i, y_i, y_predicted;
double m_gradient = 0.0;
double b_gradient = 0.0;

double learning_rate = 0.1; // Learning rate for gradient descent
int epochs = 2000;          // Number of iterations for gradient descent

// Set an array to gather the local m and b estimates
double local_mb_array[2];
double mb_array[2*world_size];
double estimates_array[2] = {0.0, 0.0};

for (int epoch = 0; epoch < epochs; epoch++) { 
    //printf("Starting epoch=%d on rank=%d\n", epoch, world_rank);
    MPI_Barrier(MPI_COMM_WORLD);
        //if ((epoch + 1) % (epochs/9) == 0 || epoch == 0) {
        /* if (1) { */
        /* printf("on rank=%d Starting epoch=%d with m=%f and b=%f \n", */
        /*         world_rank, epoch, estimates_array[0], estimates_array[1]); */
        /* } */
    m_gradient = 0.0;
    b_gradient = 0.0;
    for(int i=0; i<subarray_len; i++) {
        x_i = array[i].x;
        y_i = array[i].y;
        y_predicted = (estimates_array[0])*x_i + estimates_array[1];
        m_gradient +=  x_i * (y_i - y_predicted); // missing factor -2
        b_gradient +=  (y_i - y_predicted);
    }

    // Update local array
    local_mb_array[0] = m_gradient;
    local_mb_array[1] = b_gradient;

    MPI_Gather(local_mb_array,
            2,
            MPI_DOUBLE,
            mb_array,
            2,
            MPI_DOUBLE,
            0,
            MPI_COMM_WORLD);

    // only rank 0 gets to see the gradient
    if (world_rank == 0) {
        //m_gradient = 0;
        //b_gradient = 0;
        for (int i=2; i<2*world_size; i++) {
            if (i%2 == 0) {
                m_gradient += mb_array[i];
            } else {
                b_gradient += mb_array[i];
            }
        }
        estimates_array[0] += 2*learning_rate*m_gradient/num_data_points;
        estimates_array[1] += 2*learning_rate*b_gradient/num_data_points;

        // Broadcast the new estimates for m and b
        if ((epoch + 1) % (epochs/9) == 0 || epoch == 0) {
        printf("After Broadcast epoch=%d with m=%f and b=%f \n",
               epoch, estimates_array[0], estimates_array[1]);
        }
    }
        MPI_Bcast(estimates_array, 2, MPI_DOUBLE, 0, MPI_COMM_WORLD);

} // END EPOCHS FOR


printf("Rank = %d finished!!\n", world_rank);
MPI_Finalize();
return 0;
}
