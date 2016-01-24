#include "libminiomp.h"


pthread_mutex_t concurrent_lock;
pthread_cond_t condition;
int barrier_count1;
int barrier_count3;
int single_count;
miniomp_loop_t miniomp_loop;
int count;
int count_tasks_loop;
miniomp_hash_t miniomp_hash;
miniomp_hash_t miniomp_hash;
miniomp_task_dependences_t miniomp_task_dependences;
int *no_wait_dependences;
int *old_dependences;
int count_tasks_loop_aux;
int count_loop_init;
int start;
int sequential_region;



// Library constructor and desctructor
void init_miniomp(void) __attribute__((constructor));
void fini_miniomp(void) __attribute__((destructor));

// Function to parse OMP_NUM_THREADS environment variable
void parse_env(void);

void
init_miniomp(void) {
  //printf ("mini-omp is being initialized by Dani\n");

  #if _EXTRAE_
  Extrae_init();
  //printf ("Starting Extrae\n");
  #endif
  // Parse OMP_NUM_THREADS environment variable to initialize nthreads_var internal control variable
  parse_env();

  //set numbre of kernel threads
  pthread_setconcurrency(1);

  single_count=0;
  barrier_count1=0;
  barrier_count3=0;
  count=0;
  count_tasks_loop=0;
  count_tasks_loop_aux=0;
  start = 0;
  //start mutex and conditions
  pthread_mutex_init(&concurrent_lock, NULL);
  pthread_cond_init(&condition, NULL);
  //init hash
  init_hash();
  miniomp_task_dependences.index=0;
  count_loop_init = 0;
  sequential_region = 0;
  miniomp_task_dependences.depend = (miniomp_task_tree_t *)malloc(MAX_DEPENDENCES*sizeof(miniomp_task_tree_t));
  no_wait_dependences = (int *)malloc(MAX_THREADS*sizeof(int));
  old_dependences = (int *)malloc(MAX_THREADS*sizeof(int));
}

void
fini_miniomp(void) {
  Extrae_event (7001, 0);
  // free structures allocated during library initialization
  pthread_mutex_destroy(&concurrent_lock);
  pthread_cond_destroy(&condition);
  //printf ("mini-omp is finalized\n");
  #if _EXTRAE_
  Extrae_fini();
  #endif
  //printf ("Ending Extrae\n");
}
