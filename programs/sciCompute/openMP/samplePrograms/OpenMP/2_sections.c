#include <stdio.h>
#include <omp.h>
#define N     1000

main ()
{

int i, tid;
float a[N], b[N], c[N], d[N];

/* Some initializations */
for (i=0; i < N; i++) {
  a[i] = i * 1.5;
  b[i] = i + 22.35;
  }

#pragma omp parallel shared(a,b,c,d) private(i,tid)
  {
     tid = omp_get_thread_num();

  #pragma omp sections nowait
    {

    #pragma omp section
     {
     printf("Section 1, thread %d\n", tid);
    for (i=0; i < N; i++)
      c[i] = a[i] + b[i];
     }

    #pragma omp section
     {
     printf("Section 2, thread %d\n", tid);
    for (i=0; i < N; i++)
      d[i] = a[i] * b[i];
     }

    #pragma omp section
     {
     printf("Section 3, thread %d\n", tid);
    for (i=0; i < N; i++)
      d[i] = a[i] * b[i];
     }

    #pragma omp section
     {
     printf("Section 4, thread %d\n", tid);
    for (i=0; i < N; i++)
      d[i] = a[i] * b[i];
     }

    #pragma omp section
     {
     printf("Section 5, thread %d\n", tid);
    for (i=0; i < N; i++)
      d[i] = a[i] * b[i];
     }

    #pragma omp section
     {
     printf("Section 6, thread %d\n", tid);
    for (i=0; i < N; i++)
      d[i] = a[i] * b[i];
     }

    }  /* end of sections */

  }  /* end of parallel section */

}

