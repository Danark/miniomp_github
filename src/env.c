#include <unistd.h>
#include "libminiomp.h"

// Global variable storing the ICV (internal control variables) supported in our implementation
miniomp_icv_t miniomp_icv;

void parse_env(void) {
    char * env = getenv ("OMP_NUM_THREADS");
    if (env == NULL) {
      printf("Environment variable OMP_NUM_THREADS not defined, setting nthreads_var ICV to number of cores\n");
      int procs = (int)sysconf( _SC_NPROCESSORS_ONLN ); // returns the number of cores in system
      if (procs < 0) 
          miniomp_icv.nthreads_var = 1; 
      else miniomp_icv.nthreads_var = procs;
    } else {
      miniomp_icv.nthreads_var = atoi(env);
    }
    printf("Setting nthreads_var ICV to %d\n", miniomp_icv.nthreads_var);
    env = getenv ("OMP_SCHEDULE");
    if (env == NULL) {
	printf("ccaa");
    
    }else{
	int trobat = 0;
	int run_ched_var;
	while(trobat==0){
		if(strncasecmp(env,"auto", 4) ==0){
			trobat=1;
			env+=5;
			run_ched_var = ws_AUTO;
		}
		else if(strncasecmp(env,"guided", 6) ==0){
			trobat=1;
			env+=7;
			run_ched_var = ws_GUIDED;
		}
		else if(strncasecmp(env,"dynamic", 7) ==0){
			trobat=1;
			env+=8;
			run_ched_var = ws_DYNAMIC;
		}
		else if(strncasecmp(env,"static", 6) ==0){
			trobat=1;
			env+=7;
			run_ched_var = ws_STATICCHUNK;
		}
		else if (*env == ","){
			trobat = 1;
			env++;
		}
		else env++;
		
	}
	miniomp_icv.run_ched_chunk_size = atoi(env);
	miniomp_icv.run_ched_var = run_ched_var;	
	
    }
}
