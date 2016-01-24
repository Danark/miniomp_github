#include "libminiomp.h"

void omp_set_num_threads (int n) {
  miniomp_icv.nthreads_var = (n > 0 ? n : 1);
}

int omp_get_num_threads (void) {
  return(miniomp_icv.nthreads_var);
}

int omp_get_thread_num (void) {
  int num = (int)(long)pthread_getspecific(miniomp_specifickey);
  return num;
}

void omp_set_schedule (int n, int p) {
  miniomp_icv.run_ched_var = (n > 0 ? n : 1);
  miniomp_icv.run_ched_chunk_size = (p > 0 ? p : 0);
}


