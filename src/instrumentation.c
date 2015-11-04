#include "libminiomp.h"
#include "intrinsic.h"


int id_list[100];

void start_event_thread () {
    Extrae_event (7001, count+1);
    Extrae_event (7002, count+1);
    count++;
}

void end_event_thread () {
    Extrae_event (7001, 0);
}


void start_event_loop () {
    Extrae_event (7001, count+1);
    count++;
    id_list[omp_get_thread_num()]=1;
    printf("count %d\n", count);	
}


void end_event_loop () {
  if (id_list[omp_get_thread_num()]==1){
    Extrae_event (7001, 0);
  }
  id_list[omp_get_thread_num()]=0;
}


void start_horizontal_dependences(int dependence) {
	Extrae_event (7007, dependence);
}


void start_vertical_dependences() {
   if(count_dependences==0){
      Extrae_event (7007, count-2);
   }else{
      if(count_tasks_loop==0){
      	for (int i=1; i<=count_dependences; i++){
		Extrae_event (7007, count-i);
      	}
      }
      else{
	int ite=(count_tasks_loop+count_dependences)/count_dependences;
	int resi=count_tasks_loop%count_dependences;
	int aux_count=count-resi;
	if (resi>0){ 
		Extrae_event (7007, aux_count);	
		ite++;
		count_dependences--;
	}
      	for (int i=1; i<=count_dependences; i++){
		Extrae_event (7007, aux_count-((i*ite)));
      	}
      }
   }
   count_dependences=0;
}

void set_count_dependences(int dependence){
     count_dependences=count-(dependence+count_tasks_loop);
}


void start_event_critical() {
     Extrae_event (7008, 708);
     count_critical++;
}

void end_event_critical() {
     Extrae_event (7009, 708);
}

void init_task_dependences() {
     count_tasks_loop=0;
}

void start_event_task(){
    Extrae_event (7001, count+1);
    count++;
    count_tasks_loop++;
}
    
void end_event_task(){
    Extrae_event (7001, 0);
}





