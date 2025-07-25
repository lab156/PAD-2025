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

void gradient_descent(int num_data, double learning_rate, int epochs, double *m_estimated, double *b_estimated, DataPoint *data_array) ;

// Argumentos de un thread
struct thread_arg{
   int id; // identidad de cada hilo
   DataPoint *subarray; // arreglo que le toca sumar al hilo
   int subarray_len; // longitud del arreglo subarray
   double m_estimated;
   double b_estimated;
   double m_gradient;
   double b_gradient;
};

void thread_gradient_descent(int num_data, double learning_rate, int epochs, double *m_estimated, double *b_estimated, DataPoint *data_array) ;

void omp_gradient_descent(int num_data, double learning_rate, int epochs, 
    double *m_estimated, double *b_estimated, DataPoint *data_array);
