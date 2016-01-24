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
  
  
  
  	
       #pragma omp task
       for (int i=0; i<10000; i++) result++;


       #pragma omp barrier

       #pragma omp task
       for (int i=0; i<10000; i++) result++;	

       #pragma omp taskwait
	
	
  
   
   printf("result = %ld\n", result);
    }
#pragma omp parallel 
    {

	for (int u=0; u<1000000; u++){
        	
	}
}

}

int main(int argc, char *argv[]) {
    foo();
   printf("result = %ld\n", result);
}
