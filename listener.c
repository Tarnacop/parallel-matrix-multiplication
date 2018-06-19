#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>

int main(int argc, char * argv) {
    const int WORK_PER_WORKER = 10;

    int N = 0;
    long double PI = 0.0;

    MPI_Init(argc, argv);
 
    // TODO: initialise workers

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
        
        // Tell the worker where to start from next
        int send_value = N;
        MPI_send(&send_value, 1, MPI_INT, status.MPI_SOURCE, 0, MPI_COMM_WORLD); 
        N += WORK_PER_WORKER;
        
    }
 
    MPI_Finalize();
    
}

