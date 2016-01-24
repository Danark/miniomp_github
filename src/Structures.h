
// Type declaration for Internal Control Variables (ICV) structure
typedef struct {
  int nthreads_var;
  int run_ched_chunk_size;
  int run_ched_var;
} miniomp_icv_t;

// Type declaration for parallel descriptor (arguments needed to create pthreads)
typedef struct {
    void (*fn) (void *);
    void *fn_data;
    int id;
} miniomp_parallel_t;

// Type declaration for loop worksharing descriptor
typedef struct {
  long start;           
  long end;
  long incr;
  int schedule;         
  long chunk_size;
  int count_iteration;
  long left;
  long current;
  bool isStart;
  int count;
  int count2;
  int dependences;
  int type;
} miniomp_loop_t;


// Type declaration for critical translation
typedef struct {
    int *hash;
    int index;
} miniomp_hash_t;


//Type declaration for task dependence node
typedef struct {
   int level;
   int task;
} miniomp_task_node_t;

//Type decalration for task dependence tree
typedef struct {
   miniomp_task_node_t *depend;
   int index;
   int tree_index;
   int dependencia;
} miniomp_task_tree_t;

//Type declaration for task dependences vector
typedef struct {
   miniomp_task_tree_t *depend;
   int index;
} miniomp_task_dependences_t;








