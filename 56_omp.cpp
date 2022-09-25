#include <omp.h>
#include <stdio.h>
#include <vector>
#include <iostream>

using namespace std;


int main ()
{
    double res = 0.0;
    int N = 1234567;

    #pragma omp parallel
    {
        #pragma omp for reduction(+:res)
        for (int x = 1; x <= N; x++) {
//            printf("[debug] Thread %d\n", omp_get_thread_num());
            res += 1.0 / (1.0*x*x);
        }
    }

    cout << "RESULT: После " << N << " итераций число (pi^2)/6 равно " << res << endl;

    return 0;
}
