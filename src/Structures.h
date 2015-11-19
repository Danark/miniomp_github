
// Type declaration for Internal Control Variables (ICV) structure
typedef struct {
  int nthreads_var;
  // Add other ICV if needed
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
} miniomp_loop_t;


// Type declaration for critical translation
typedef struct {
    int *hash;
    int index;
} miniomp_hash_t;