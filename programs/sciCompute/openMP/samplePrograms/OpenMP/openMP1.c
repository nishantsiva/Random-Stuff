#include <omp.h>
#include <stdio.h>
void main() 
{
  int a=0;
#pragma omp parallel if(a ==0)
  {
    // Code inside this region runs in parallel.
    a++;
    printf("Hello!, a is %d\n", a);
  }
  printf("Hello-Back to Sequential!\n");
  
}
