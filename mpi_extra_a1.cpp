#include <stdio.h>
#include "mpi.h"
#include <iostream>
#include <time.h>
#include <stdlib.h>

using namespace std;

/**
    В каждом подчиненном процессе дано целое число. Переслать эти числа в главный
    процесс, используя функции MPI_Send и MPI_Recv (стандартные блокирующие функции для
    передачи и приема сообщения), и вывести их в главном процессе. Полученные числа выводить в
    порядке возрастания рангов переславших их процессов.
*/

int main(int argc, char **argv)
{

    int rank, size;
    MPI_Init(&argc, &argv);

    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);


    if (rank == 0) {
        int received = 0;
        int *data = new int[size];
        for (int i = 1; i < size; i++) {
            MPI_Recv(&data[i], 1, MPI_INT, i, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
            received++;

            if (received == size-1) {
                for (int i = 1; i < size; i++) {
                    printf("%d, ", data[i]);
                }
                printf("\n");
            }
        }

    } else {
        int number = rank * 3;
        printf("Я #%d процесс и моя цифра %d\n", rank, number);
        MPI_Send(&number, 1, MPI_INT, 0, 0, MPI_COMM_WORLD);
    }


    MPI_Finalize();
    return 0;
}
