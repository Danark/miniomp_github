#include "libminiomp.h"
#include "intrinsic.h"

// Declaratiuon of global variable for single work descriptor


/* This routine is called when first encountering a SINGLE construct. 
   Returns true if this is the thread that should execute the clause.  */

bool
GOMP_single_start (void)
{

  bool ret = (false);
  single_count++;
  if(single_count<2){
	ret=true;
  }
  if(single_count==omp_get_num_threads()){
	single_count=0;
  }  
return ret;
}


