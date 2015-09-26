#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdbool.h>
#include <string.h>
#include <stdint.h>
#include <pthread.h>
#include "extrae_user_events.h"



// Extrae Constants
#define  _EXTRAE_   0
#define  END        0
#define  PARALLEL   2


#define MAX_THREADS 32

// To implement memory barrier (flush)
//void __atomic_thread_fence(int);
#define mb() __atomic_thread_fence(3)

// Type declaration for Internal Control Variables (ICV) structure
typedef struct {
  int nthreads_var;
  // Add other ICV if needed
} miniomp_icv_t;

extern miniomp_icv_t miniomp_icv;

// declaration of per-thread specific key
extern pthread_key_t miniomp_specifickey;


// Default lock for critical sections


// Default barrier within a parallel region
#define MYBARRIER 1
#if MYBARRIER
//  Here you should define all neceesary types and variables to implement your barrier



	
#else
// Default barrier using Pthread barriers 

#endif

// Type declaration for own implementation of barrier
//typedef struct {
    // complete the definition of barrier
//} miniomp_barrier_t;

//extern miniomp_barrier_t miniomp_barrier;

// Declaration of array for storing pthread identifier from pthread_create function


// Type declaration for parallel descriptor (arguments needed to create pthreads)
typedef struct {
    void (*fn) (void *);
    void *fn_data;
    int id;
    // complete the definition of parallel descriptor
} miniomp_parallel_t;

//Pointer to the threads array
extern pthread_t *threads;
//Barrier indicator 1
extern int barrier_count1;
//Barrier indicator 2
extern int barrier_count2;

extern int end;



// Type declaration for loop worksharing descriptor
typedef struct {
  long start;           // loop bounds and increment 
  long end;
  long incr;
  int schedule;         // schedule kind for loop
  long chunk_size;
  long left;
  long current;
  bool isStart;
  int count;
  int count2;
} miniomp_loop_t;


#define ws_STATIC 	0
#define ws_STATICCHUNK 	1
#define ws_DYNAMIC 	2
#define ws_GUIDED 	3
#define ws_RUNTIME 	4
#define ws_AUTO 	5



// Type declaration for single work sharing descriptor


// Declaratiuon of global variable for single work descriptor
extern int single_count;

/* This structure describes a "task" to be run by a thread.  */


//mutex que permite concurrencia
extern pthread_mutex_t concurrent_lock;
extern pthread_cond_t condition;



#define MAXELEMENTS_TQ 128

// funtions to implement basic management operations on taskqueue

