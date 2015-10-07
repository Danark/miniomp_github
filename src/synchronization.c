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
  barrier_count1++;
  if(barrier_count1==omp_get_num_threads()){
	barrier_count1=0;
	pthread_cond_broadcast(&condition);
	#if _EXTRAE_
  	Extrae_event (7001, 0);
  	#endif
	pthread_mutex_unlock(&concurrent_lock);
  }
  else{
	#if _EXTRAE_
  	Extrae_event (7001, 0);
  	#endif
	pthread_cond_wait(&condition, &concurrent_lock);
	pthread_mutex_unlock(&concurrent_lock);
  }
  pthread_mutex_lock(&concurrent_lock);
  #if _EXTRAE_
  Extrae_event (7001, omp_get_thread_num()+1);
  #endif

}


