#include <stdio.h>
#include "omp.h"

const long NbLaps = 1000000;

/** The number of thread to create a each loop */
const int NbThreads = 4 ;
long test=0 ;
/**
* The more basic openmp function we can do
*/
int main(){
    long index=0;
    printf( "------- Test Openmp -------\n");
 
    const double startTime = omp_get_wtime();
    for(index = 0 ; index < NbLaps ; ++index ){
        #pragma omp parallel num_threads(NbThreads) reduction(+:test)
        {
		++test ;
        }
    }
 
    const double endTime = omp_get_wtime();
 
    printf("Duration = %lf Test value = %ld \n", (endTime - startTime), test);
    return 0;
}
