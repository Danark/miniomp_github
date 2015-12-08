#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <pthread.h>
#include <stdbool.h>
#include <string.h>
#include <omp.h>	/* OpenMP */

long result=0;
long caca=0;

void foo() {
#pragma omp parallel 
    { 
  
  
    #pragma omp for schedule(dynamic,3) 
    for (long i = 0; i < 10; i++){
	#pragma omp task shared(result) depend(in:result) depend(out:caca)
	{
        result++;}
	#pragma omp task depend(in: caca)
        caca++;
	#pragma omp task depend(in: caca)
        caca++;
	#pragma omp task depend(in: caca)
        caca++;
	#pragma omp task depend(out: caca)
        caca++;
}

   #pragma omp taskwait
   printf("result = %ld\n", result);
    }
}

int main(int argc, char *argv[]) {
    foo();
   printf("result = %ld\n", result);
}
