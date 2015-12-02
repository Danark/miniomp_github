#include "libminiomp.h"
#include "intrinsic.h"
#include "events.h"



int id_list[100];

void init_hash(){
 miniomp_hash.hash = (int *)malloc(MAX_CRITICALS*sizeof(int));
 miniomp_hash.index=0;
}

int found_hash(int id){
 int result=-1;
 for (int i=0; i<miniomp_hash.index; i++){
	if (miniomp_hash.hash[i]==id) result=i;
 }
 if (result!=-1) result++;
 return result;
}

int insert_hash(int id){
  miniomp_hash.hash[miniomp_hash.index]=id;
  miniomp_hash.index++;
  return miniomp_hash.index;
}

void start_event_thread () {
    Extrae_event (TASK, count+1);
    //Extrae_event (7002, count+1);
    count++;
}

void end_event_thread () {
    Extrae_event (TASK, 0);
}


void start_event_loop () {
    Extrae_event (TASK, count+1);
    count++;
    id_list[omp_get_thread_num()]=1;
}


void end_event_loop () {
  if (id_list[omp_get_thread_num()]==1){
    Extrae_event (TASK, 0);
  }
  id_list[omp_get_thread_num()]=0;
}


void start_horizontal_dependences(int dependence) {
    printf("DEPENDENCE %d\n", dependence);
    for (int i=0; i<omp_get_num_threads(); i++){
	printf("DEPENDENCE_COUNT %d\n", dependence-i);
	Extrae_event (TASK_DEPENDENCES, dependence-i);
    }
}


void start_vertical_dependences() {
   int aux;
   if(count_dependences==0){
      Extrae_event (TASK_DEPENDENCES, count-1);
   }else{
      if(count_tasks_loop==0){
      	for (int i=1; i<=count_dependences; i++){
		aux=i+thread_count-1;
		Extrae_event (TASK_DEPENDENCES, count-aux);
      	}
      }
      else{
	int ite=count_max_inner_loop+1;
        aux=thread_count-1;
	printf("ite = %d\n", ite);
	int resi=(count_tasks_loop+count_dependences)%ite;
	printf("resi = %d\n", resi);
	int aux_count=count-(aux+resi);
	if (resi>0){ 
		Extrae_event (TASK_DEPENDENCES, aux_count);	
		count_dependences--;
	}
      	for (int i=1; i<=count_dependences; i++){
		Extrae_event (TASK_DEPENDENCES, aux_count-(i*ite));
      	}
      }
   }
   if (thread_count==omp_get_num_threads()) thread_count=0;
   count_dependences=0;
}

void set_count_dependences(int dependence){
     count_dependences=count-(dependence+count_tasks_loop+thread_count);
     printf("count_dependences %d\n", count_dependences);
     printf("count %d\n",thread_count );
     thread_count++;
     //if (thread_count==omp_get_num_threads()) thread_count=0;
}


void start_event_critical(int id) {
     int found=found_hash(id);
     if (found==-1) found=insert_hash(id);
     Extrae_event (START_CRITICAL, found);
     
}

void end_event_critical(int id) {
     int found=found_hash(id);
     Extrae_event (END_CRITICAL, found);
}

void init_loop_dependences() {
        count_tasks_loop=0;
        count_max_inner_loop=0;
        count_inner_loop=0;    
}

void calc_max_dependences(){
    if (count_max_inner_loop<count_inner_loop) count_max_inner_loop=count_inner_loop;
    count_inner_loop=0;
}

void start_event_task(){
    Extrae_event (TASK, count+1);
    count++;
    count_tasks_loop++;
    count_inner_loop++;
}
    
void end_event_task(){
    Extrae_event (TASK, 0);
}

void function_out(int depend){
   bool trobat  = false;
   int index = -1;
   for (int i=0; i<miniomp_task_dependences.index; i++){
	if (miniomp_task_dependences.depend_in[i]==depend){
            Extrae_event (TASK_DEPENDENCES, miniomp_task_dependences.task_in[i]);
	    trobat = true;
	    index = i;
	}
	if (miniomp_task_dependences.depend_out[i]==depend){
	    index = i;
	}
   }
   if (index == -1){
	miniomp_task_dependences.index++;
	index = miniomp_task_dependences.index;
   }

   miniomp_task_dependences.task_out[index] = count;
   miniomp_task_dependences.depend_out[index] = depend;
  
   if(!trobat){
	miniomp_task_dependences.task_in[index] = -1;
	miniomp_task_dependences.depend_in[index] = -1;
   }
}


void function_in(int depend){
   bool trobat  = false;
   int index = -1;
   for (int i=0; i<miniomp_task_dependences.index; i++){
	if (miniomp_task_dependences.depend_out[i]==depend){
            Extrae_event (TASK_DEPENDENCES, miniomp_task_dependences.task_out[i]);
	    trobat = true;
	    index = i;
	}
	if (miniomp_task_dependences.depend_in[i]==depend){
	    index = i;
	}
   }
   if (index == -1){
	miniomp_task_dependences.index++;
	index = miniomp_task_dependences.index;
   }

   miniomp_task_dependences.task_in[index] = count;
   miniomp_task_dependences.depend_in[index] = depend;
  
   if(!trobat){
	miniomp_task_dependences.task_out[index] = -1;
	miniomp_task_dependences.depend_out[index] = -1;
   }
}
		

void set_task_dependences (void **depend){
   size_t ndepend = (uintptr_t)depend[0];
   size_t nout = (uintptr_t)depend[1];
   size_t i=0;
   for (; i<nout; i++){
	function_out(depend[i+2]);
   }
   for (; i<ndepend; i++){
	function_in(depend[i+2]);
   }
}
