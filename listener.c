#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>

int main(int argc, char ** argv) {
    const int NUM_WORKERS = 99;
    const int WORK_PER_WORKER = 1000000;
    const int ITERATIONS = 100000000;

    long long N = 0;
    long long DONE = 0;
    long double PI = 0.0;

    MPI_Init(&argc, &argv);
 
    // Give the workers their initial work
    for(int i = 1; i <= NUM_WORKERS; i++) {
        MPI_Ssend(&N, 1, MPI_INT, i, 0, MPI_COMM_WORLD);
        N += WORK_PER_WORKER;
    }

    for(int i = 0; i < ITERATIONS; i++) {
        // Listen for a finished calculation
        long double result;
        MPI_Status status;
        MPI_Recv(&result, 1, MPI_LONG_DOUBLE, MPI_ANY_SOURCE, MPI_ANY_TAG, MPI_COMM_WORLD, &status);

        DONE += WORK_PER_WORKER;

        printf("There are %lld workers still going. %lld have finished!", N-DONE, DONE);  

        PI += result;
        
        // Tell the worker where to start from next
        MPI_Ssend(&N, 1, MPI_LONG_LONG, status.MPI_SOURCE, 0, MPI_COMM_WORLD); 
        N += WORK_PER_WORKER;
        
    }

    printf("PI is: %100.Lf\n", 4*PI/(double)N);
 
    MPI_Finalize();
    
}

