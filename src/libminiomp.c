#include "libminiomp.h"
//#include "intrinsic.h"


pthread_mutex_t concurrent_lock;
pthread_cond_t condition;
int barrier_count1;
int barrier_count2;
int barrier_count3;
int single_count;
miniomp_loop_t miniomp_loop;
int count;
int count_critical_loop;
int count_loop;
int count_dependences;
int count_tasks_loop;
miniomp_hash_t miniomp_hash;
//miniomp_critical_depth_t miniomp_critical_depth;
int count_max_inner_loop;
int count_inner_loop;
miniomp_hash_t miniomp_hash;
int thread_count;
miniomp_task_dependences_t miniomp_task_dependences;
int count_ite;
int count_chunk;
int count_max_chunk;
int *no_wait_dependences;
int count_tasks_loop_aux;



// Library constructor and desctructor
void init_miniomp(void) __attribute__((constructor));
void fini_miniomp(void) __attribute__((destructor));

// Function to parse OMP_NUM_THREADS environment variable
void parse_env(void);

void
init_miniomp(void) {
  printf ("mini-omp is being initialized by Dani\n");

  #if _EXTRAE_
  Extrae_init();
  printf ("Starting Extrae\n");
  #endif
  // Parse OMP_NUM_THREADS environment variable to initialize nthreads_var internal control variable
  parse_env();
  pthread_setconcurrency(1);
  single_count=0;
  barrier_count1=0;
  barrier_count2=0;
  barrier_count3=0;
  count=0;
  count_critical_loop=0;
  count_loop=0;
  count_dependences=0;
  count_tasks_loop=0;
  count_tasks_loop_aux=0;
  pthread_mutex_init(&concurrent_lock, NULL);
  pthread_cond_init(&condition, NULL);
  init_hash();
  thread_count=0;
  miniomp_task_dependences.index=0;
  miniomp_task_dependences.depend = (miniomp_task_tree_t *)malloc(MAX_DEPENDENCES*sizeof(miniomp_task_tree_t));
  no_wait_dependences = (int *)malloc(MAX_THREADS*sizeof(int));
  /*miniomp_task_dependences.depend_in = (int *)malloc(MAX_DEPENDENCES*sizeof(int));
  miniomp_task_dependences.task_out = (int *)malloc(MAX_DEPENDENCES*sizeof(int));
  miniomp_task_dependences.task_in = (int *)malloc(MAX_DEPENDENCES*sizeof(int));*/

  // Initialize Pthread data structures and thread-specific data
  // Initialize OpenMP default lock and default barrier
  // Initialize OpenMP workdescriptors for loop and single and taskqueue
}

void
fini_miniomp(void) {
  // free structures allocated during library initialization
  pthread_mutex_destroy(&concurrent_lock);
  pthread_cond_destroy(&condition);
  printf ("mini-omp is finalized\n");
  #if _EXTRAE_
  Extrae_fini();
  #endif
  printf ("Ending Extrae\n");
}
