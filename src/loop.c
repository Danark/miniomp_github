#include "libminiomp.h"
#include "intrinsic.h"

// Declaratiuon of global variable for loop work descriptor
miniomp_loop_t miniomp_loop;
int id_list[100];

/* The *_next routines are called when the thread completes processing of 
   the iteration block currently assigned to it.  If the work-share 
   construct is bound directly to a parallel construct, then the iteration
   bounds may have been set up before the parallel.  In which case, this
   may be the first iteration for the thread.

   Returns true if there is work remaining to be performed; *ISTART and
   *IEND are filled with a new iteration block.  Returns false if all work
   has been assigned.  */

bool
GOMP_loop_dynamic_next (long *istart, long *iend) {
  //printf("TBI: Asking for more iterations? I gave you all at the beginning, no more left ...\n");
  bool ret=(true);
  //printf("Entro en Next\n");
   if((miniomp_loop.left/miniomp_loop.incr)>0){
	if (id_list[omp_get_thread_num()]==1){
		#if _EXTRAE_
	 	Extrae_event (7001, 0);
		Extrae_event (7003, 0);
	  	#endif
	}
        //printf("Primer if\n");
	id_list[omp_get_thread_num()]=1;
  	*istart=miniomp_loop.current;
  	if ((miniomp_loop.left/miniomp_loop.incr)>=miniomp_loop.chunk_size){
		//printf("Segon if\n");	
		*iend=miniomp_loop.current+(miniomp_loop.chunk_size*miniomp_loop.incr);
		miniomp_loop.current+=(miniomp_loop.chunk_size*miniomp_loop.incr);
		miniomp_loop.left-=(miniomp_loop.chunk_size*miniomp_loop.incr);
		}
	else{
	 *iend=miniomp_loop.end;
	 miniomp_loop.left=0;
	 }
	//espera de la resta de threads x per poder seguir
	miniomp_loop.count++;
	//printf("contador %d\n",miniomp_loop.count);
	if(miniomp_loop.count==omp_get_num_threads()){
		//printf("count= %d\n",miniomp_loop.count);
		//printf("num_threads= %d\n",omp_get_num_threads());
		//printf("Los voy a despertar a todos!\n");
		miniomp_loop.count=0;
		pthread_cond_broadcast(&condition);
		pthread_mutex_unlock(&concurrent_lock);
		//printf("Salgo de despertarlos!\n");
 	 }
  	else{
		//printf("Me quedo esperando\n");
		pthread_cond_wait(&condition, &concurrent_lock);
		//printf("Salgo de la espera\n");
		pthread_mutex_unlock(&concurrent_lock);	
		//printf("Me despierto!\n");
	}
	//printf("Cojo el mutex\n");
	pthread_mutex_lock(&concurrent_lock);
	if (id_list[omp_get_thread_num()]==1){
		miniomp_loop.count_iteration++;
		#if _EXTRAE_
	 	Extrae_event (7001, miniomp_loop.count_iteration);
		Extrae_event (7003, 1);
	  	#endif
	}
  }
  else {
  	ret=(false);

        if (id_list[omp_get_thread_num()]==1){
		#if _EXTRAE_
	 	Extrae_event (7001, 0);
		Extrae_event (7003, 0);
	  	#endif
	}
  }

  
  
  
  return(ret);
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
GOMP_loop_dynamic_start (long start, long end, long incr, long chunk_size,
                         long *istart, long *iend)
{
  
  // *istart = start;
  // *iend= end;
  if (miniomp_loop.isStart==(false)){
	printf("Inicialitzo loop dynamic\n");
  	miniomp_loop.left= end;
	miniomp_loop.start=start;
	miniomp_loop.end=end;
	miniomp_loop.incr=incr;
	miniomp_loop.chunk_size=chunk_size;
        miniomp_loop.count_iteration=0;
        miniomp_loop.isStart=(true);
	miniomp_loop.current=start;
	miniomp_loop.count=0;
	miniomp_loop.count2=0;
  }
  bool ret=GOMP_loop_dynamic_next(istart, iend);  
  
  //GOMP_loop_dynamic_next(istart, iend);  
	
  //printf("TBI: What a mess! Starting a non-static for worksharing construct and dont know what to do, I'll take it all\n");

  return(ret);
}

/* The GOMP_loop_end* routines are called after the thread is told that
   all loop iterations are complete.  The first version synchronize
   all threads; the nowait version does not. */

void
GOMP_loop_end (void) {
   //printf("TBI: Finishing a for worksharing construct with non static schedule\n");
   //miniomp_loop.count=0;
   miniomp_loop.count2++;
   if (miniomp_loop.count2==1){
   	pthread_cond_broadcast(&condition);
   }
    if (miniomp_loop.count2==omp_get_num_threads()){
	miniomp_loop.count2=0;
   }
   GOMP_barrier();
   miniomp_loop.isStart=(false);
   
}

void
GOMP_loop_end_nowait (void) {
  //printf("TBI: Finishing a for worksharing construct with non static schedule, with nowait clause\n");
  miniomp_loop.count=0;
  miniomp_loop.isStart=(false);
 
 
}
