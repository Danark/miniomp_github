#include "libminiomp.h"

void omp_set_num_threads (int n) {
  miniomp_icv.nthreads_var = (n > 0 ? n : 1);
}

int omp_get_num_threads (void) {
  return(miniomp_icv.nthreads_var);
}

int omp_get_thread_num (void) {
  //printf("TBI: omp_get_thread_num still doesn't know who I am ... let's say 0\n");
  //int num = (int)(long)pthread_getspecific(miniomp_specifickey);
  //return num;
  return 0;
}