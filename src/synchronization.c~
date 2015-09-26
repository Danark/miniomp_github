#include "libminiomp.h"
#include "intrinsic.h"
#include <pthread.h>



void GOMP_critical_start (void) {
  //printf("TBI: Entering an unnamed critical, don't know if anyone else is alrady in. I proceed\n");

}

void GOMP_critical_end () {
  //printf("Exiting an unnamed critical section. I can not inform anyone else\n");

}

#if MYBARRIER

#endif

void GOMP_barrier() {
   //printf("TBI: Entering in barrier, but do not know how to wait for the rest. I proceed\n");
   /*int id=(pthread_getspecific(miniomp_specifickey)+1);
   id=id%omp_get_num_threads();
   barrier_count1++;
   pthread_continue_np(threads[id]);
   while (barrier_count1!=omp_get_num_threads()) {}
   int error;
   for (int i=0; i<get_num_threads()-1; i++){
        if(i!=pthread_getspecific(miniomp_specifickey)) {
              error=pthread_suspend_np(threads[i]);
        }
}*/
  barrier_count1++;
  if(barrier_count1==omp_get_num_threads()){
	barrier_count1=0;
	pthread_cond_signal(&condition);
	pthread_mutex_unlock(&concurrent_lock);
  }
  else{
	pthread_cond_wait(&condition, &concurrent_lock);
	pthread_mutex_unlock(&concurrent_lock);
  }
  pthread_mutex_lock(&concurrent_lock);

}


