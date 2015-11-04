#include "libminiomp.h"

// Initializes the task queue
/*
void init_task_queue(int max_elements) {



}

// Checks if the task descriptor is valid
bool is_valid(void) {
    return false;
}

// Checks if the task queue is empty
bool is_empty() {
    return true;
}

// Checks if the task queue is full
bool is_full() {
  
 return true;

   
}

// Enqueues the task descriptor at the tail of the task queue
bool enqueue(void) {
   
    return true;
}

// Dequeue the task descriptor at the head of the task queue
void dequeue() { 
 
}



// Returns the task descriptor at the head of the task queue
/*miniomp_task_t *first() {
    return miniomp_taskqueue.head;
}*/

/* Called when encountering an explicit task directive.  If IF_CLAUSE is
   false, then we must not delay in executing the task. */
void
GOMP_task (void (*fn) (void *), void *data, void (*cpyfn) (void *, void *),
           long arg_size, long arg_align, bool if_clause, unsigned flags,
           void **depend)
{

	if (if_clause){
    	    if (__builtin_expect (cpyfn != NULL, 0))
        	{
			char * buf =  malloc(sizeof(char) * (arg_size + arg_align - 1));
			char *arg = (char *) (((uintptr_t) buf + arg_align - 1) 
						& ~(uintptr_t) (arg_align - 1));
			cpyfn (arg, data);
			printf("execute 1\n");
			start_event_task();
			fn(arg);
			end_event_task();
                }
            else 
		{
			char * arg =  malloc(sizeof(char) * (arg_size + arg_align - 1));
			memcpy(arg, data, arg_size);
			printf("execute 2\n");
			start_event_task();
			fn(arg);
			end_event_task();
		}
	}
	else{
		if (__builtin_expect (cpyfn != NULL, 0))
        	{
	 	 char * buf =  malloc(sizeof(char) * (arg_size + arg_align - 1));
         	 char *arg = (char *) (((uintptr_t) buf + arg_align - 1)
         	                       & ~(uintptr_t) (arg_align - 1));
         	 cpyfn (arg, data);
		 printf("execute 3\n");
		 start_event_task();
                 fn(arg);
		 end_event_task();
		 
       	 	}
    		else{
			printf("execute 4\n");
			start_event_task();
        		fn(data);
			end_event_task();
		}
    	}
}
       


void
GOMP_taskwait (void)
{
    printf("TBI: Entered in taskwait, there should be no pending tasks, so I proceed\n");
    
      
}
