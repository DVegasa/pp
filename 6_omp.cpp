#include <omp.h>
#include <stdio.h>
#include <vector>
#include <iostream>

using namespace std;

double f (double x) {
    return 2 / (1 + x * x);
}

int main ()
{

    double a = 2;
    double b = 5;
    int n = 200; /** OMP требует чтобы параметр в цикле был целым числом */

    const double width = (b-a)/n;

    double trapezoidal_integral = 0;

    #pragma omp parallel for
    for (int step = 0; step < n; step++) {
        printf("[debug] Thread %d is working on element %d\n", omp_get_thread_num(), step);

        const double x1 = a + step*width;
        const double x2 = a + (step+1)*width;

        trapezoidal_integral += 0.5*(x2-x1)*(f(x1) + f(x2));
    }

    cout << "res: " << trapezoidal_integral << endl;

    return 0;
}
