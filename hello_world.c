#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>

int main(void) {
    int rank, size;

    MPI_Init(NULL, NULL);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    printf("Hello World! I am %d of %d\n", rank, size);

    MPI_Finalize();
}
