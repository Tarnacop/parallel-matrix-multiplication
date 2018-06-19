#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>
#include <math.h>

int server(void);
int client(void);
long double calc(long long total,long long start,long long iterations);
    const long long NUM_WORKERS = 99;
    const long long WORK_PER_WORKER = 10;
    const long long ITERATIONS = 990;

int main(int argc, char ** argv){
    MPI_Init(&argc, &argv);

    int rank;
    MPI_Comm_rank(MPI_COMM_WORLD,&rank);

    if(rank == 0){
        printf("Hey I'm a server :D\n");
        server();
    } else {
        printf("Hey I'm a client :)\n");
        client();
    }

    return 0;

}

int server(void) {

    long long N = 0;
    long long DONE = 0;
    long double PI = 0.0;

 
    // Give the workers their initial work
    for(int i = 1; i <= NUM_WORKERS; i++) {
        MPI_Send(&N, 1, MPI_LONG_LONG, i, 0, MPI_COMM_WORLD);
        N += WORK_PER_WORKER;
        printf("end of worker loop\n");
    }

    printf("finished allocating worker jobs\n");

    for(long long i = 0; i < ITERATIONS; i++) {
        printf("entered waiting loop (server)\n");

        // Listen for a finished calculation
        long double result;
        MPI_Status status;
        MPI_Recv(&result, 1, MPI_LONG_DOUBLE, MPI_ANY_SOURCE, MPI_ANY_TAG, MPI_COMM_WORLD, &status);

        DONE += WORK_PER_WORKER;

        PI += result;
        
        // Tell the worker where to start from next
        MPI_Send(&N, 1, MPI_LONG_LONG, status.MPI_SOURCE, 0, MPI_COMM_WORLD); 
        N += WORK_PER_WORKER;
        printf("poo\n");
        
    }

    printf("PI is: %.100Lf\n", 4*PI/(double)N);
 
    MPI_Finalize();

    return 0;
}

int client(void) {
    long double total;

    while(1) {
        total = 0.0;
        long long CURRENT;
        MPI_Status status;
        MPI_Recv(&CURRENT, 1, MPI_LONG_LONG, 0, MPI_ANY_TAG, MPI_COMM_WORLD, &status);

        int count;
        MPI_Get_count(&status, MPI_LONG_LONG, &count);
        printf("[client recv] source: %d, count: %d\n", status.MPI_source, count);

        total = calc(ITERATIONS, CURRENT, WORK_PER_WORKER);

        MPI_Send(&total, 1, MPI_LONG_DOUBLE, 0, 0, MPI_COMM_WORLD);
    }

    return 0;
}

long double calc(long long totaliterations, long long current, long long iterations){
    long double a,b,c,calc = 0.0;
    for (long i=current; i<current+iterations; i++) {
        c = ((long double)i - 0.5) / ((long double)totaliterations);
        b = pow(c, 2.0);
        a = 1.0 + b;
        calc += 1.0/a;
    }
    printf("calc: %Lf\n",calc);
    return calc;
}
