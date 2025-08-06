#include <stdio.h>
#include <gsl/gsl_sf_gamma.h>

int main() {
    double x = 5.0;
    double gamma_val = gsl_sf_gamma(x);
    printf("Gamma(%f) = %f\n", x, gamma_val);

    // ln de Gamma viene incluido en el archivo .h
    double lngamma_val = gsl_sf_lngamma(x);
    printf("log(Gamma(%f)) = %f\n", x, lngamma_val);

    return 0;
}
