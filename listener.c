#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>

int main(int argc, char * argv) {
    int N = 0;
    long double PI = 0.0;

    MPI_Init(argc, argv);

    while(1) {
        // Listen for a finished calculation
        long double result;
        MPI_Status status;
        MPI_recv(&result, 1, MPI_LONG_DOUBLE, MPI_ANY_SOURCE, MPI_ANY_TAG, MPI_COMM_WORLD, &status);
        if(status) {
            sprintf(STDERR, "Error: %d\n", status_);
        }
        PI += result;
        printf("PI: %d\n", PI);
    }
 
    MPI_Finalize();
    
}

