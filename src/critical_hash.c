#include "libminiomp.h"
#include "intrinsic.h"
#include "instrumentation.h"


void init_hash(int max_elements) {
    miniomp_hash.hash = (miniomp_node_t *)malloc(max_elements*sizeof(miniomp_node_t));
    miniomp_hash.index = 0;
}

void add_node(miniomp_node_t node){
    miniomp_hash.hash[miniomp_hash.index] = node;
    miniomp_hash.index++;
}

void add_node(){
 }
