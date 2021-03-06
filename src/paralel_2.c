// This file handles the PARALLEL construct

// Declaration of array for storing pthread identifier from pthread_create function
pthread_t *threads;

// Global variable for parallel descriptor
miniomp_parallel_t *miniomp_parallel;

// declaration of per-thread specific key
pthread_key_t miniomp_specifickey;

int point=0;


// This is the prototype for the Pthreads starting function
/*void *worker( miniomp_parallel_t* parameters) {
  // insert all necessary code here for:
  //   1) save thread-specific data
  //   2) invoke the per-threads instance of function encapsulating the parallel region
  //   3) exit the function
  
  pthread_setspecific(miniomp_specifickey, (void *)parameters->id);
  //miniomp_specifickey=parameters->id;
  void (*fn) (void *) = (void *)parameters->fn;
  void (*fn_data) (void *)=  (void *)parameters->fn_data;
  fn(fn_data);
  //printf("hola\n");
  GOMP_barrier();
  //printf("adew\n");
  pthread_exit((void *) miniomp_specifickey);
  
  
  
  
}*/

void *worker( miniomp_parallel_t* parameters) {
        printf("worker1\n");
        pthread_setspecific(miniomp_specifickey, (void *)parameters->id);
        void (*fn) (void *) = (void *)parameters->fn;
        void (*fn_data) (void *)=  (void *)parameters->fn_data;
        printf("worker\n");
       
        //pthread_mutex_lock(&concurrent_lock);
	printf("worker2\n");
        fn(fn_data);
	printf("worker3\n");
	pthread_exit((void *) miniomp_specifickey);
	//point=1;
	//pthread_mutex_unlock(&concurrent_lock);
}



/*void
GOMP_parallel (void (*fn) (void *), void *data, unsigned num_threads, unsigned int flags) {
  
  if(!num_threads) num_threads = omp_get_num_threads();
  omp_set_num_threads(num_threads);

  
  miniomp_parallel_t parameters[num_threads];
  pthread_t threads_aux[num_threads];
  threads = &threads_aux[0];
  pthread_key_create(&miniomp_specifickey, NULL);
  
  printf("Starting a parallel region using %d threads\n", num_threads);
  int i;
  for (i=0; i<num_threads-1; i++){
      #if _EXTRAE_
      Extrae_event (1000, PARALLEL);
      #endif
      parameters[i].fn=fn;
      parameters[i].fn_data=data;
      parameters[i].id=i;
      pthread_create(&threads[i], NULL, worker, &parameters[i]);
      }
      worker(&parameters[i]);

  void *status;
  
      for (i=0; i<num_threads-1; i++){
  	pthread_join(threads[i], &status);
	//printf("Completed join with thread %ld\n", (long)status);
      
      }
      #if _EXTRAE_
      Extrae_event (1000, END);
      #endif
  printf("Reaching the end of the parallel region\n");
      
  
}*/

// When using the following splitted interface, the master invokes foo after returning from GOMP_parallel_start
void
GOMP_parallel_start (void (*fn) (void *), void *data, unsigned num_threads) {
  if(!num_threads) num_threads = omp_get_num_threads();
  omp_set_num_threads(num_threads);

  
  miniomp_parallel_t parameters[num_threads];
  pthread_t threads_aux[num_threads];
  pthread_key_create(&miniomp_specifickey, NULL);
  
  printf("Starting a parallel region using dani %d threads\n", num_threads);
  for (int i=0; i<num_threads; i++){
      parameters[i].fn=fn;
      printf("fn\n");
      parameters[i].fn_data=data;
      printf("data\n");
      parameters[i].id=i;
      printf("id\n");;
      //pthread_create(&threads_aux[i], NULL, worker, &parameters[i]);
      fn(data);
      printf("thread\n");
      }
      //while(point!=1){}
      /*void *status;
      
      for ( int i=0; i<num_threads; i++){
	printf("end\n");
  	pthread_join(&threads_aux[i], &status);
	printf("Completed join with thread %ld\n", (long)status);
      
      }
      #if _EXTRAE_
      Extrae_event (1000, END);
      #endif*/
}

void
GOMP_parallel_end (void) {
      /*void *status;
      printf("end\n");
      for ( int i=0; i<omp_get_num_threads(); i++){
	printf("end1\n");
  	pthread_join((threads+i), &status);
	printf("Completed join with thread %ld\n", (long)status);
      
      }
      #if _EXTRAE_
      Extrae_event (1000, END);
      #endif*/
  printf("Reaching the end of the parallel region\n");
}

