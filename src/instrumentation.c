#include "libminiomp.h"
#include "intrinsic.h"

int count=0;

void start_event_thread () {
    Extrae_event (7001, omp_get_thread_num()+1);
}

void end_event_thread () {
    Extrae_event (7001, 0);
}


void start_event_loop () {
    Extrae_event (7001, count);
    count++;
}


void end_event_loop () {
    Extrae_event (7001, 0);
}
