#include<stdio.h>
#include<omp.h>

int main() {
int private_id, shared_num = 5;
# pragma omp parallel private(private_id) num_threads(shared_num)
{
private_id = omp_get_thread_num();
printf(" shared_num = %d , private_id = %d  \n",
 shared_num, private_id);
#pragma omp master 
printf(" Esta linea solo la ejecuta Master, %d \n", omp_get_thread_num());
}
}
