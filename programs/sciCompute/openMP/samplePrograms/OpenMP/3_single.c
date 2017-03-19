#include <stdio.h>
#include <omp.h>

main ()  {
  
  int nthreads, tid;
  
  /* Fork a team of threads with each thread having a private tid variable */
#pragma omp parallel private(tid)
  {
    
    /* Obtain and print thread id */
    tid = omp_get_thread_num();
    
#pragma omp single 
    printf("Hello World from thread = %d\n", tid);
    
    
    printf("Hi, I am thread %d\n", tid);
    /* Only master thread does this */
#pragma omp master
    {
      nthreads = omp_get_num_threads();
      printf("Number of threads = %d\n", nthreads);
    }
    
  }  /* All threads join master thread and terminate */
  
}

