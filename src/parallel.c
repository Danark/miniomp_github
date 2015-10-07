#include "libminiomp.h"
#include "intrinsic.h"
#include "instrumentation.h"

// Declaration of array for storing pthread identifier from pthread_create function
//pthread_t *threads;
int end=0;
// Global variable for parallel descriptor
miniomp_parallel_t *miniomp_parallel;

// declaration of per-thread specific key
pthread_key_t miniomp_specifickey;





void *worker( miniomp_parallel_t* parameters) {
        //printf("worker1\n");
        pthread_setspecific(miniomp_specifickey, (void *)parameters->id);
        void (*fn) (void *) = (void *)parameters->fn;
        void (*fn_data) (void *)=  (void *)parameters->fn_data;
        //printf("worker\n");
        //printf("worker-thread %d\n", (void *)parameters->id); 
	//printf("thread %d\n",miniomp_specifickey);
        pthread_mutex_lock(&concurrent_lock);
        #if _EXTRAE_
  	start_event_thread ();
  	#endif
	//printf("worker2\n");
        fn(fn_data);
	//printf("worker3\n");
	//printf("thread %d\n",miniomp_specifickey);
	end++;
	pthread_cond_signal(&condition);
	 #if _EXTRAE_
  	end_event_thread();
  	#endif
	pthread_mutex_unlock(&concurrent_lock);
	pthread_exit(NULL);

	
}


pthread_t threads_aux[100];
miniomp_parallel_t parameters[100];
void
GOMP_parallel_start (void (*fn) (void *), void *data, unsigned num_threads) {
  if(!num_threads) num_threads = omp_get_num_threads();
  printf("Starting a parallel region using %d threads\n", num_threads);
  pthread_key_create(&miniomp_specifickey, NULL);
 
  for (int i=0; i<num_threads-1; i++){
      parameters[i].fn=fn;
      printf("%d\n", i);
      parameters[i].fn_data=data;
      parameters[i].id=i+1;
      printf("id %d\n",i);
      pthread_create(&threads_aux[i], NULL, worker, &parameters[i]);
   }
  void *status;
  pthread_mutex_lock(&concurrent_lock);
  #if _EXTRAE_
  start_event_thread ();
  #endif
      
  
  
 
}

void
GOMP_parallel_end (void) {
  #if _EXTRAE_
  end_event_thread();
  #endif
  while(end!=(omp_get_num_threads())-1){
	//printf("while\n");
	pthread_cond_wait(&condition, &concurrent_lock);
  }
  pthread_mutex_unlock(&concurrent_lock);
 // printf("-----------------------------------------\n");
  printf("Reaching the end of the parallel region\n");
  for( int i=0; i<omp_get_num_threads()-1; i++){
	pthread_join(threads_aux[i], NULL);
  }
}






/*void
GOMP_parallel (void (*fn) (void *), void *data, unsigned num_threads, unsigned int flags) {
  
  if(!num_threads) num_threads = omp_get_num_threads();
  miniomp_parallel_t parameters[num_threads];
  pthread_t threads_aux[num_threads];
  printf("Starting a parallel region using %d threads\n", num_threads);
  for (int i=0; i<num_threads; i++){
      parameters[i].fn=fn;
      printf("%d\n", i);
      parameters[i].fn_data=data;
      //printf("data\n");
      parameters[i].id=i;
      printf("id %d\n",i);
      //fn (data);
      pthread_create(&threads_aux[i], NULL, worker, &parameters[i]);
   }
   pthread_mutex_lock(&concurrent_lock);
  while(end!=(omp_get_num_threads())){
	printf("while\n");
	pthread_cond_wait(&condition, &concurrent_lock);
  }
  pthread_mutex_unlock(&concurrent_lock);
  printf("-----------------------------------------\n");
  #if _EXTRAE_
  Extrae_event (1000, END);
  #endif
  printf("Reaching the end of the parallel region\n");
}*/


