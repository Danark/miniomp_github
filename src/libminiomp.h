#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdbool.h>
#include <string.h>
#include <stdint.h>
#include <pthread.h>
#include "extrae_user_events.h"
#include "Config.h"
#include "Structures.h"

// To implement memory barrier (flush)
//void __atomic_thread_fence(int);
#define mb() __atomic_thread_fence(3)


extern miniomp_icv_t miniomp_icv;

// declaration of per-thread specific key
extern pthread_key_t miniomp_specifickey;

// Declaration of array for storing pthread identifier from pthread_create function


//Pointer to the threads array
extern pthread_t *threads;
//Barrier indicator 1
extern int barrier_count1;
//Barrier indicator 2
extern int barrier_count2;
extern int count;
extern int count_critical_loop;
extern int end;
extern int count_dependences;
extern int count_tasks_loop;
extern int count_loop;
extern int count_max_inner_loop;
extern int count_inner_loop;
extern int thread_count;

// Declaratiuon of global variable for single work descriptor
extern int single_count;

//mutex que permite concurrencia
extern pthread_mutex_t concurrent_lock;
extern pthread_cond_t condition;

extern miniomp_hash_t miniomp_hash;

extern miniomp_task_dependences_t miniomp_task_dependences;

#define MAXELEMENTS_TQ 128




