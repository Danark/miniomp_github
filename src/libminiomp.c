#include "libminiomp.h"
#include "intrinsic.h"


pthread_mutex_t concurrent_lock;
pthread_cond_t condition;
int barrier_count1;
int barrier_count2;
int single_count;
miniomp_loop_t miniomp_loop;



//miniomp_taskqueue_t miniomp_taskqueuee
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
  pthread_mutex_init(&concurrent_lock, NULL);
  pthread_cond_init(&condition, NULL);

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
