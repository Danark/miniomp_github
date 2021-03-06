#include "libminiomp.h"
#include "intrinsic.h"
#include <pthread.h>



void GOMP_critical_start (void) {
  start_event_critical(6000);//we set a fixed id for the criticals with no name

}

void GOMP_critical_end () {
  end_event_critical(6000);//we set a fixed id for the criticals with no name

}


void GOMP_critical_name_start (void **ptr) {
  int id = ptr;
  start_event_critical(id);
}

void GOMP_critical_name_end (void **ptr) {
  int id = ptr;
  end_event_critical(id);

}





void GOMP_barrier() {
  barrier_count1++;
 
  if(barrier_count1==omp_get_num_threads()){
	barrier_count1=0;
	pthread_cond_broadcast(&condition);
	count_tasks_loop_aux = count_tasks_loop;
        restart_count_tasks_loop();
	#if _EXTRAE_
  	end_event_thread();
  	#endif
	pthread_mutex_unlock(&concurrent_lock);
  }
  else{
	#if _EXTRAE_
  	end_event_thread();
  	#endif
	pthread_cond_wait(&condition, &concurrent_lock);//conditional wait
	pthread_mutex_unlock(&concurrent_lock);
  }
  pthread_mutex_lock(&concurrent_lock);
  barrier_count3++;
  #if _EXTRAE_
  start_event_thread();
  start_horizontal_dependences(count-barrier_count3-count_tasks_loop, count_tasks_loop_aux);
  #endif
  if(barrier_count3==omp_get_num_threads()){
	barrier_count3=0;
	
  }

}



void GOMP_barrier_loop(int dependences, int type) {
  barrier_count1++;
  if(barrier_count1==omp_get_num_threads()){
	barrier_count1=0;
	restart_count_tasks_loop();
	pthread_cond_broadcast(&condition);
	pthread_mutex_unlock(&concurrent_lock);
	restart_count_tasks_loop();
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


void GOMP_barrier_No_Extrae() {
  barrier_count1++;
  if(barrier_count1==omp_get_num_threads()){
	barrier_count1=0;
	pthread_cond_broadcast(&condition);
	pthread_mutex_unlock(&concurrent_lock);
	restart_count_tasks_loop();
  }
  else{

	pthread_cond_wait(&condition, &concurrent_lock);
	pthread_mutex_unlock(&concurrent_lock);
  }
  pthread_mutex_lock(&concurrent_lock);

}



