#include <omp.h>
#include <stdio.h>

int main ()
{
    #pragma omp parallel
    {   
        // ID of the thread in the current team
        int thread_id = omp_get_thread_num();
        // Number of threads in the current team
        int nthreads = omp_get_num_threads();

        printf("I'm thread %d out of %d threads.\n", thread_id, nthreads);
    }
    return 0;
}
