#include <omp.h>
#include <stdio.h>
#include <vector>
#include <iostream>

using namespace std;

int main ()
{
    vector<double> a = {1, 5, 31, -1, 77, -3};
    vector<double> b = {7, 6, 22, -4, 42, -6};

    double res = 0;

    /** Использовать shared не нужно, т.к. переменные вне блока по умолчанию такие */
    #pragma omp parallel for
    for (int i = 0; i < a.size(); i++)
    {
        printf("[debug] Thread %d is working on element %d\n", omp_get_thread_num(), i);
        res += a[i] * b[i];
    }

    cout << "res: " << res << endl;

    return 0;
}
