#include<stdio.h>
#include<omp.h>

int main() {
int private_id, shared_num = 7;
# pragma omp parallel private(private_id) 
{
private_id = omp_get_thread_num();
printf(" shared_num = %d , private_id = %d  \n",
 shared_num, private_id);
}
}
