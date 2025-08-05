#include <stdio.h>
#include <lapacke.h>


int main() {
    int n = 3; // Matrix dimension
    int nrhs = 1; // Number of right-hand sides
    double A[] = {2.0, 4.0, 7.0, 2.0, 5.0, 8.0, 3.0, 6.0, 9.0}; // Matrix A (column-major)
    double B[] = {6.0, 15.0, 24.0}; // Right-hand side vector B
    lapack_int ipiv[n]; // Pivot indices
    lapack_int info;

    // Solve the linear system
    // LAPACK_COMPLEX_CPP significa que lea columna por columna
    info = LAPACKE_dgesv(LAPACK_COL_MAJOR, n, nrhs, A, n, ipiv, B, n);

    if (info == 0) {
        printf("Solution x:\n");
        for (int i = 0; i < n; i++) {
            printf("%f\n", B[i]);
        }
    } else {
        printf("LAPACKE_dgesv failed with info = %d\n", info);
    }

    return 0;
}
