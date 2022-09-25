#include <stdio.h>
#include "mpi.h"
#include <iostream>

using namespace std;

/**
    3 В главном процессе прочесть вещественное число X и вывести его противоположное значение,
    в каждом из остальных процессов (подчиненных процессов, ранг которых больше 0) вывести его
    ранг.
*/

int main(int argc, char **argv)
{
    int rank, size;
    MPI_Init(&argc, &argv);

    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    if (rank == 0) {
        printf("Я тут главный и докладываю: процессоров %d штук\n", size);
        double n;
        cin >> n;
        printf("Число противоположное твоему это %f\n", -n);

    } else {
        printf("Привет. Я процессор#%d\n", rank);
    }


    MPI_Finalize();
    return 0;
}
