#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <pthread.h>
#include <stdbool.h>
#include <string.h>
#include <omp.h>	/* OpenMP */

int first=0;

int foo() {
    int  x = 1023;
    first += x+1;
#pragma omp parallel firstprivate(x)  if(x>0)
    {
    int aux;
    #pragma omp task depend(in:first)
    aux = first+2;
    
    #pragma omp task depend(inout:first)
    first = first+2;
    #pragma omp task depend(inout:first)
    first = first+3;  
    
    printf("Thread %d finished the execution of foo\n", omp_get_thread_num());
    #pragma omp barrier
    
    }
    return(x);
}

int main(int argc, char *argv[]) {
    printf("first = %d, x = %d\n", first, foo());
}
