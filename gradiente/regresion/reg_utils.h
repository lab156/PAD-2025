#ifndef REG_UTILS_H

#define REG_UTILS_H

double random_double();

double random_normal(double mean, double stddev) ;

typedef struct {
    double x;
    double y;
} DataPoint;

void initialize_data(int num_data, DataPoint *data_array, double m_true, double b_true);
#endif // REG_UTILS_H
