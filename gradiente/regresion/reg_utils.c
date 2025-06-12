#include <stdlib.h>
#include <math.h>
#include <sys/time.h>
// Includes sleep function, only for Linux
// In Windows use Windows.h and function called Sleep(milliseconds)
#include <unistd.h>


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
