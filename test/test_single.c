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
  
  
    #pragma omp for schedule(dynamic,1) 
    for (long i = 0; i < 100; i++){
	
        result++;
    }

   #pragma omp single
   {
   printf("result = %ld\n", result);
   }
    }
}

int main(int argc, char *argv[]) {
    foo();
   printf("result = %ld\n", result);
}
