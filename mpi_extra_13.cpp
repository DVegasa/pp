#include <stdio.h>
#include "mpi.h"
#include <iostream>
#include <time.h>
#include <stdlib.h>

using namespace std;

/**
    В каждом подчиненном процессе дано вещественное число. Переслать эти числа в
    главный процесс, используя функции MPI_Bsend (посылка сообщения с буферизацией) и
    MPI_Recv, и вывести их в главном процессе. Полученные числа выводить в порядке убывания
    рангов переславших их процессов. Для задания буфера использовать функцию MPI_Buffer_attach.
*/

int main(int argc, char **argv)
{

    int rank, size;
    MPI_Init(&argc, &argv);

    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);


    if (rank == 0) {
        double received = 0;
        double *data = new double[size];
        for (int i = 1; i < size; i++) {
            MPI_Recv(&data[i], 1, MPI_DOUBLE, i, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
            received++;

            if (received == size-1) {
                for (int j = size-1; j >= 1; j--) {
                    printf("%3.2f, ", data[j]);
                }
                printf("\n");
            }
        }

    } else {
        char *buf;
        int s2;
        MPI_Pack_size(1, MPI_DOUBLE, MPI_COMM_WORLD, &s2 );
        int bufsize = s2 + MPI_BSEND_OVERHEAD;
        buf = (char *)malloc( bufsize );
        MPI_Buffer_attach( buf, bufsize );

        double b = rank * 100 + (rank * 0.111);
        MPI_Bsend(&b, 1, MPI_DOUBLE, 0, 0, MPI_COMM_WORLD);
    }


    MPI_Finalize();
    return 0;
}
