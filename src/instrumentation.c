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
    count++;
    old_dependences[omp_get_thread_num()]=count;
	
}

void start_event_thread_region() {
    Extrae_event (TASK, count+1);
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


void start_horizontal_dependences(int dependence, int task) {
    for (int i=0; i<omp_get_num_threads(); i++){
	Extrae_event (TASK_DEPENDENCES, dependence-(((1+i)*task/omp_get_num_threads())+i));
    }
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

void start_event_task(){
    Extrae_event (TASK, count+1);
    count++;
    count_tasks_loop++;
}
    
void end_event_task(){
    Extrae_event (TASK, 0);
}

void function_in(int depend){
   int trobat = 0;
   for (int i=0; i<miniomp_task_dependences.index; i++){
	if (miniomp_task_dependences.depend[i].dependencia==depend){//if the memory region is in the vector
		trobat = 1;
		int tree_index = miniomp_task_dependences.depend[i].tree_index;
		if(tree_index%2==0){ 
			tree_index = miniomp_task_dependences.depend[i].tree_index-1;
		}
		else{
			tree_index = miniomp_task_dependences.depend[i].tree_index;
			miniomp_task_dependences.depend[i].tree_index++;	
		}
		int dependencie = -1;
		for (int u=0; u<miniomp_task_dependences.depend[i].index; u++){
			if(miniomp_task_dependences.depend[i].depend[u].level==tree_index){
				dependencie = miniomp_task_dependences.depend[i].depend[u].task;
			}
		}
		if (dependencie != -1) Extrae_event (TASK_DEPENDENCES, dependencie);
		int index = miniomp_task_dependences.depend[i].index;
		miniomp_task_dependences.depend[i].index++;
		miniomp_task_dependences.depend[i].depend[index].level=tree_index+1;
		miniomp_task_dependences.depend[i].depend[index].task=count;
		
	}
	
   }
   if (!trobat){//if the memory region isn't in the vector
	int index_trobat = miniomp_task_dependences.index;
	miniomp_task_dependences.index++;
	miniomp_task_dependences.depend[index_trobat].depend = (miniomp_task_node_t *)malloc(MAX_DEPENDENCES_NODES*sizeof(miniomp_task_node_t));
	miniomp_task_dependences.depend[index_trobat].depend[0].task = count;
	miniomp_task_dependences.depend[index_trobat].depend[0].level = 0;
	miniomp_task_dependences.depend[index_trobat].index = 1;
	miniomp_task_dependences.depend[index_trobat].tree_index=0;
	miniomp_task_dependences.depend[index_trobat].dependencia = depend;
   }
}



void function_out(int depend){
   int trobat = 0;
   for (int i=0; i<miniomp_task_dependences.index; i++){ //if the memory region is in the vector
	if (miniomp_task_dependences.depend[i].dependencia==depend){
		trobat = 1;
		int tree_index = miniomp_task_dependences.depend[i].tree_index;
		int tree_aux = tree_index-1;
		if(tree_index%2==0){
			miniomp_task_dependences.depend[i].tree_index++;
			tree_aux++;
		}
		for (int u=0; u<miniomp_task_dependences.depend[i].index; u++){
			if(miniomp_task_dependences.depend[i].depend[u].level==tree_index){
				Extrae_event (TASK_DEPENDENCES, miniomp_task_dependences.depend[i].depend[u].task);
			}
		}
		int index = miniomp_task_dependences.depend[i].index;
		miniomp_task_dependences.depend[i].index++;
		miniomp_task_dependences.depend[i].depend[index].level=tree_aux+1;
		miniomp_task_dependences.depend[i].depend[index].task=count;
	}
	
   }
   if (!trobat){ //if the memory region is not in the vector
	int index_trobat = miniomp_task_dependences.index;
	miniomp_task_dependences.index++;
	miniomp_task_dependences.depend[index_trobat].depend = (miniomp_task_node_t *)malloc(MAX_DEPENDENCES_NODES*sizeof(miniomp_task_node_t));
	miniomp_task_dependences.depend[index_trobat].depend[0].task = count;
	miniomp_task_dependences.depend[index_trobat].depend[0].level = 1;
	miniomp_task_dependences.depend[index_trobat].index = 1;
	miniomp_task_dependences.depend[index_trobat].tree_index=1;
	miniomp_task_dependences.depend[index_trobat].dependencia = depend;
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

void start_loop_dependences(){
   Extrae_event (TASK_DEPENDENCES, no_wait_dependences[omp_get_thread_num()]);
}

void start_nowait_dependences(){
   Extrae_event (TASK_DEPENDENCES, no_wait_dependences[omp_get_thread_num()]);
}

void start_vertical_dependences() {
   for (int i = 0; i<omp_get_num_threads(); i++){
	Extrae_event (TASK_DEPENDENCES, no_wait_dependences[i]);
   }
}

void start_vertical_dependences_region() {
   for (int i = 0; i<omp_get_num_threads(); i++){
	Extrae_event (TASK_DEPENDENCES, old_dependences[i]);
   }
}



void start_horizontal_dependences_regions() {
   Extrae_event (TASK_DEPENDENCES, sequential_region);
}

void restart_count_tasks_loop(){
   count_tasks_loop=0;
}	


void set_task_wait() {
 Extrae_event(TASK_WAIT, count);
}
	

