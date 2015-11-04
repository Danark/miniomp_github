#include "libminiomp.h"
#include "intrinsic.h"
#include <pthread.h>



void GOMP_critical_start (void) {
  //printf("TBI: Entering an unnamed critical, don't know if anyone else is alrady in. I proceed\n");
  start_event_critical();

}

void GOMP_critical_end () {
  //printf("Exiting an unnamed critical section. I can not inform anyone else\n");
  end_event_critical();

}


#if MYBARRIER

#endif

void GOMP_barrier() {
  barrier_count1++;
  if(barrier_count1==omp_get_num_threads()){
	barrier_count1=0;
	pthread_cond_broadcast(&condition);
	#if _EXTRAE_
  	end_event_thread();
  	#endif
	pthread_mutex_unlock(&concurrent_lock);
  }
  else{
	#if _EXTRAE_
  	end_event_thread();
  	#endif
	pthread_cond_wait(&condition, &concurrent_lock);
	pthread_mutex_unlock(&concurrent_lock);
  }
  pthread_mutex_lock(&concurrent_lock);
  #if _EXTRAE_
  start_event_thread();
  start_vertical_dependences();
  #endif

}



void GOMP_barrier_loop() {
  barrier_count1++;
  if(barrier_count1==omp_get_num_threads()){
	barrier_count1=0;
	pthread_cond_broadcast(&condition);
	pthread_mutex_unlock(&concurrent_lock);
  }
  else{
	pthread_cond_wait(&condition, &concurrent_lock);
	pthread_mutex_unlock(&concurrent_lock);
  }
  pthread_mutex_lock(&concurrent_lock);
  #if _EXTRAE_
  start_event_thread();
  start_vertical_dependences();
  #endif

}


