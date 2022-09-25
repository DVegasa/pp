#include <omp.h>
#include <stdio.h>
#include <vector>
#include <iostream>

using namespace std;

double f (int i, int j) {
    return 1.0 / (i*i + j*j*j);
}

int main ()
{
    int N = 6666662;
    int M = 30;

    double res = 0;

    // Создаём внешний контекст, чтобы цикл видел переменную res
    #pragma omp parallel
    {
        // reduction нужно для убирания эффекта гонки при записи в res
        #pragma omp for reduction(+:res)
        for (int i = 1; i <= N; i++) {
            for (int j = 1; j <= M; j++) {
//                printf("[debug] Thread %d is working on element %d, %d\n", omp_get_thread_num(), i, j);
                res += f(i, j);
            }
        }
    }

    cout << "res: " << res << endl;

    return 0;
}
