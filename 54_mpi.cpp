
#include "mpi.h"
#include <stdio.h>
#include <vector>
#include <iostream>

using namespace std;


int main (int argc, char **argv)
{
    int rank, size;
    MPI_Init(&argc, &argv);

    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);


    int N = 1000001;
    long int TARGET = 10000L * 10000L * 10000L;

    long from = (-1) * N + rank;
    for (long int x = from; x <= N; x += size) {
        for (long int y = -N; y <= N; y++) {
            for (long int z = -N; z <= N; z++) {
                if (x*x + y*y*y + z*z*z == TARGET) {
                    printf("rank %d:    ", rank);
                    printf("x=%7.ld   y=%7.ld   z=%7.ld\n", x, y, z);
                }
            }
        }
    }

    MPI_Finalize();
    return 0;
}
