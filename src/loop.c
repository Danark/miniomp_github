#include "libminiomp.h"
#include "intrinsic.h"

// Declaratiuon of global variable for loop work descriptor
miniomp_loop_t miniomp_loop;
int contador;

/* The *_next routines are called when the thread completes processing of 
   the iteration block currently assigned to it.  If the work-share 
   construct is bound directly to a parallel construct, then the iteration
   bounds may have been set up before the parallel.  In which case, this
   may be the first iteration for the thread.

   Returns true if there is work remaining to be performed; *ISTART and
   *IEND are filled with a new iteration block.  Returns false if all work
   has been assigned.  */


bool
GOMP_loop_guided_next (long *istart, long *iend) {
  #if _EXTRAE_
  end_event_loop();
  #endif
  miniomp_loop.count++;
  if(miniomp_loop.count==omp_get_num_threads()){
  	miniomp_loop.count=0;
	pthread_cond_broadcast(&condition);
	pthread_mutex_unlock(&concurrent_lock);
  }
  else{
		
	pthread_cond_wait(&condition, &concurrent_lock);
	pthread_mutex_unlock(&concurrent_lock);	
		
	}
  pthread_mutex_lock(&concurrent_lock);
  bool ret=(true);
   if((miniomp_loop.left/miniomp_loop.incr)>0){
        #if _EXTRAE_
  	start_event_loop();
	if (no_wait_dependences[omp_get_thread_num()]!=0){
		start_loop_dependences();
  	}else{
		start_horizontal_dependences(miniomp_loop.dependences);
  	}
	no_wait_dependences[omp_get_thread_num()]=count;
  	#endif
  	*istart=miniomp_loop.current;
  	if ((miniomp_loop.left/miniomp_loop.incr)>=miniomp_loop.chunk_size){
		*iend=miniomp_loop.current+(miniomp_loop.chunk_size*miniomp_loop.incr);
		miniomp_loop.current+=(miniomp_loop.chunk_size*miniomp_loop.incr);
		miniomp_loop.left-=(miniomp_loop.chunk_size*miniomp_loop.incr);
		if ( miniomp_loop.left/(omp_get_num_threads()*2)==0 ) miniomp_loop.chunk_size = 1;
		else miniomp_loop.chunk_size= miniomp_loop.left/(omp_get_num_threads()*2);
		}
	else{
	 *iend=miniomp_loop.end;
	 miniomp_loop.left=0;
	 }

  }
  else {
  	ret=(false);

	
  }

  
  
  
  return(ret);
}



bool
GOMP_loop_dynamic_next (long *istart, long *iend) {
  #if _EXTRAE_
  end_event_loop();
  #endif
  miniomp_loop.count++;
  if(miniomp_loop.count==omp_get_num_threads()){
  	miniomp_loop.count=0;
	pthread_cond_broadcast(&condition);
	pthread_mutex_unlock(&concurrent_lock);
  }
  else{
		
	pthread_cond_wait(&condition, &concurrent_lock);
	pthread_mutex_unlock(&concurrent_lock);	
		
	}
  pthread_mutex_lock(&concurrent_lock);
  bool ret=(true);
   if((miniomp_loop.left/miniomp_loop.incr)>0){
        #if _EXTRAE_
  	start_event_loop();
	if (no_wait_dependences[omp_get_thread_num()]!=0){
		start_loop_dependences();
  	}else{
		start_horizontal_dependences(miniomp_loop.dependences);
  	}
	no_wait_dependences[omp_get_thread_num()]=count;
  	#endif
  	*istart=miniomp_loop.current;
  	if ((miniomp_loop.left/miniomp_loop.incr)>=miniomp_loop.chunk_size){
		*iend=miniomp_loop.current+(miniomp_loop.chunk_size*miniomp_loop.incr);
		miniomp_loop.current+=(miniomp_loop.chunk_size*miniomp_loop.incr);
		miniomp_loop.left-=(miniomp_loop.chunk_size*miniomp_loop.incr);
		}
	else{
	 *iend=miniomp_loop.end;
	 miniomp_loop.left=0;
	 }

  }
  else {
  	ret=(false);

	
  }

  
  
  
  return(ret);
}



bool
GOMP_loop_static_next (long *istart, long *iend) {
  #if _EXTRAE_
  end_event_loop();
  #endif
  miniomp_loop.count++;
  if(miniomp_loop.count==omp_get_num_threads()){
  	miniomp_loop.count=0;
	pthread_cond_broadcast(&condition);
	pthread_mutex_unlock(&concurrent_lock);
  }
  else{
		
	pthread_cond_wait(&condition, &concurrent_lock);
	pthread_mutex_unlock(&concurrent_lock);	
		
	}
  pthread_mutex_lock(&concurrent_lock);
  bool ret=(true);
   if((miniomp_loop.left/miniomp_loop.incr)>0){
        #if _EXTRAE_
  	start_event_loop();
	if (no_wait_dependences[omp_get_thread_num()]!=0){
		start_loop_dependences();
  	}else{
		start_horizontal_dependences(miniomp_loop.dependences);
  	}
	no_wait_dependences[omp_get_thread_num()]=count;
  	#endif
  	*istart=miniomp_loop.current;
  	if ((miniomp_loop.left/miniomp_loop.incr)>=miniomp_loop.chunk_size){
		*iend=miniomp_loop.current+(miniomp_loop.chunk_size*miniomp_loop.incr);
		miniomp_loop.current+=(miniomp_loop.chunk_size*miniomp_loop.incr);
		miniomp_loop.left-=(miniomp_loop.chunk_size*miniomp_loop.incr);
		}
	else{
	 *iend=miniomp_loop.end;
	 miniomp_loop.left=0;
	 }

  }
  else {
  	ret=(false);

	
  }

  
  
  
  return(ret);
}


bool
GOMP_loop_runtime_next (long *istart, long *iend) {
	if (miniomp_icv.run_ched_var == ws_STATICCHUNK) return GOMP_loop_static_next (istart, iend);
	else if (miniomp_icv.run_ched_var == ws_DYNAMIC) return GOMP_loop_dynamic_next (istart, iend);
	else if (miniomp_icv.run_ched_var == ws_GUIDED) return GOMP_loop_guided_next (istart, iend);
	else return false;
}

/* The *_start routines are called when first encountering a loop construct
   that is not bound directly to a parallel construct.  The first thread 
   that arrives will create the work-share construct; subsequent threads
   will see the construct exists and allocate work from it.

   START, END, INCR are the bounds of the loop; CHUNK_SIZE is the
   scheduling parameter. 

   Returns true if there's any work for this thread to perform.  If so,
   *ISTART and *IEND are filled with the bounds of the iteration block
   allocated to this thread.  Returns false if all work was assigned to
   other threads prior to this thread's arrival.  */





bool
GOMP_loop_guided_start (long start, long end, long incr, long chunk_size,
                         long *istart, long *iend)
{
  #if _EXTRAE_
  end_event_thread();
  #endif
  count_loop_init++;
  no_wait_dependences[omp_get_thread_num()]=count-(count_tasks_loop/count_loop_init);
  if(count_loop_init==omp_get_num_threads())count_loop_init=0;
  GOMP_barrier_No_Extrae();
  if (miniomp_loop.isStart==(false)){
  	miniomp_loop.left= end-start;
	miniomp_loop.start=start;
	miniomp_loop.end=end;
	miniomp_loop.incr=incr;
	miniomp_loop.chunk_size=chunk_size;
        miniomp_loop.count_iteration=0;
        miniomp_loop.isStart=(true);
	miniomp_loop.current=start;
	miniomp_loop.count=0;
	miniomp_loop.dependences=count;
	miniomp_loop.count2=0;
	miniomp_loop.type = ws_GUIDED;
	
  }
  
  GOMP_barrier_No_Extrae();
  bool ret=GOMP_loop_guided_next(istart, iend);   
  return(ret);
}





bool
GOMP_loop_dynamic_start (long start, long end, long incr, long chunk_size,
                         long *istart, long *iend)
{
  #if _EXTRAE_
  end_event_thread();
  #endif
  count_loop_init++;
  no_wait_dependences[omp_get_thread_num()]=count-(count_tasks_loop/count_loop_init);
  if(count_loop_init==omp_get_num_threads())count_loop_init=0;
  GOMP_barrier_No_Extrae();
  if (miniomp_loop.isStart==(false)){
  	miniomp_loop.left= end-start;
	miniomp_loop.start=start;
	miniomp_loop.end=end;
	miniomp_loop.incr=incr;
	miniomp_loop.chunk_size=chunk_size;
        miniomp_loop.count_iteration=0;
        miniomp_loop.isStart=(true);
	miniomp_loop.current=start;
	miniomp_loop.count=0;
	miniomp_loop.dependences=count;
	miniomp_loop.count2=0;
	miniomp_loop.type = ws_DYNAMIC;
  }
  
  GOMP_barrier_No_Extrae();
  bool ret=GOMP_loop_dynamic_next(istart, iend);  
  return(ret);
}

bool
GOMP_loop_static_start (long start, long end, long incr, long chunk_size,
                         long *istart, long *iend)
{
  #if _EXTRAE_
  end_event_thread();
  #endif
  count_loop_init++;
  no_wait_dependences[omp_get_thread_num()]=count-(count_tasks_loop/count_loop_init);
  if(count_loop_init==omp_get_num_threads())count_loop_init=0;
  GOMP_barrier_No_Extrae();
  if (miniomp_loop.isStart==(false)){
  	miniomp_loop.left= end-start;
	miniomp_loop.start=start;
	miniomp_loop.end=end;
	miniomp_loop.incr=incr;
	if (chunk_size == 0){
		chunk_size = (end-start)/omp_get_num_threads();
		if (((end-start)%omp_get_num_threads())!=0) chunk_size++;
		//printf("cunk size: %d\n", chunk_size);
	}
	miniomp_loop.chunk_size=chunk_size;
        miniomp_loop.count_iteration=0;
        miniomp_loop.isStart=(true);
	miniomp_loop.current=start;
	miniomp_loop.count=0;
	miniomp_loop.dependences=count;
	miniomp_loop.count2=0;
	miniomp_loop.type = ws_STATICCHUNK;
  }
  GOMP_barrier_No_Extrae();
  bool ret=GOMP_loop_static_next(istart, iend);  


  return(ret);
}

/* The GOMP_loop_end* routines are called after the thread is told that
   all loop iterations are complete.  The first version synchronize
   all threads; the nowait version does not. */

bool
GOMP_loop_runtime_start (long start, long end, long incr, long *istart, long *iend)
{
	//printf("runtime\n");
	if (miniomp_icv.run_ched_var == ws_STATICCHUNK)return GOMP_loop_static_start (start, end, incr, (long)miniomp_icv.run_ched_chunk_size, istart, iend);
	else if (miniomp_icv.run_ched_var == ws_DYNAMIC) return GOMP_loop_dynamic_start (start, end, incr,(long)miniomp_icv.run_ched_chunk_size, istart, iend);
	else if (miniomp_icv.run_ched_var == ws_GUIDED)return GOMP_loop_guided_start (start, end, incr, (long)miniomp_icv.run_ched_chunk_size, istart, iend);
	else return false;

}

void
GOMP_loop_end (void) {
   miniomp_loop.count2++;
   if (miniomp_loop.count2==1){
   	pthread_cond_broadcast(&condition);
   }
    if (miniomp_loop.count2==omp_get_num_threads()){
	miniomp_loop.count2=0;
   }
   GOMP_barrier_loop(miniomp_loop.dependences, miniomp_loop.type);
   contador++;
   if (contador==1){
   	miniomp_loop.isStart=(false);
   }
   if (contador==omp_get_num_threads()){
	contador=0;
   }
   
   
}

void
GOMP_loop_end_nowait (void) {
  miniomp_loop.count2++;
  if (miniomp_loop.count2==omp_get_num_threads()){
	miniomp_loop.count2=0;
	miniomp_loop.isStart=(false);
  }
  start_event_thread();
  if (no_wait_dependences[omp_get_thread_num()]!=0){
	start_nowait_dependences();
  }else{
	start_horizontal_dependences(miniomp_loop.dependences);
  }
 
 
}
