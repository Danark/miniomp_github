#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <pthread.h>
#include <stdbool.h>
#include <string.h>
#include <omp.h>	/* OpenMP */

long result=0;

void foo() {
#pragma omp parallel 
    {
    /*#pragma omp for 
    for (long i = 0; i < 10; i++) {
	#pragma omp atomic
        result++;
    }*/
   
  
    omp_set_schedule(omp_sched_dynamic,2);
  
    #pragma omp for schedule(runtime) 
    for (long i = 0; i < 11; i++){
      #pragma omp task 
	result++;
      #pragma omp task 
	result++;
    }
   
   
    /*#pragma omp for schedule(dynamic,1) nowait
    for (long i = 0; i < 10; i++)
	#pragma omp atomic
        result++;*/

   //#pragma omp barrier
   //#pragma omp single
   printf("result = %ld\n", result);
    }
}

int main(int argc, char *argv[]) {
    foo();
   printf("result = %ld\n", result);
}
