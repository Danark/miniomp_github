#include "libminiomp.h"


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
			start_event_task();
			if(depend!=0) set_task_dependences (depend);
			fn(arg);
			end_event_task();
                }
            else 
		{
			char * arg =  malloc(sizeof(char) * (arg_size + arg_align - 1));
			memcpy(arg, data, arg_size);
			start_event_task();
			if(depend!=0) set_task_dependences (depend);
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
		 start_event_task();
 		 if(depend!=0) set_task_dependences (depend);
                 fn(arg);
		 end_event_task();
		 
       	 	}
    		else{
			start_event_task();
			if(depend!=0) set_task_dependences (depend);
        		fn(data);
			end_event_task();
		}
    	}
}
       


void
GOMP_taskwait (void)
{

    GOMP_barrier();
    set_task_wait(); 
      
}
