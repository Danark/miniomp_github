#include "libminiomp.h"
#include "intrinsic.h"


int id_list[100];

void start_event_thread () {
    Extrae_event (7002, count+1);
    count++;
}

void end_event_thread () {
    Extrae_event (7002, 0);
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
        //count_dependences++;

}

void start_vertical_dependences() {
   if(count_dependences==0){
      Extrae_event (7007, count-2);
   }else{
      for (int i=1; i<=count_dependences; i++){
	Extrae_event (7007, count-i);
      }
   }
   count_dependences=0;
}

void set_count_dependences(int dependence){
     count_dependences=count-dependence;
}


void start_event_critical() {
     Extrae_event (7008, count_critical+1);
     count_critical++;
}

void end_event_critical() {
     Extrae_event (7009, count_critical);
}

    





