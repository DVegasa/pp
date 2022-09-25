#include <omp.h>
#include <stdio.h>
#include <vector>
#include <iostream>

using namespace std;


int main ()
{
    int N = 1000;
    #pragma omp parallel for
    for (int x = -N; x <= N; x++) {
        for (int y = -N; y <= N; y++) {
            for (int z = -N; z <= N; z++) {
                if (x*x + y*y + z*z*z == 10000000) {
                    printf("[debug] Thread %d | ", omp_get_thread_num());
                    printf("x=%7.d   y=%7.d   z=%7.d\n", x, y, z);
                }
            }
        }
    }

    return 0;
}
