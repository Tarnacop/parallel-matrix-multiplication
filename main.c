#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>
#include <math.h>

int server(void);
int client(void);
long double calc(long long total,long long start,long long iterations);
    const long long NUM_WORKERS = 99;
    const long long WORK_PER_WORKER = 1000;
    const long long ITERATIONS = 100000;

int main(int argc, char ** argv){
    MPI_Init(&argc, &argv);

    int rank;
    MPI_Comm_rank(MPI_COMM_WORLD,&rank);

    if(rank == 0){
        server();
    } else {
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
        MPI_Ssend(&N, 1, MPI_INT, i, 0, MPI_COMM_WORLD);
        N += WORK_PER_WORKER;
    }

    for(long long i = 0; i < ITERATIONS; i++) {
        // Listen for a finished calculation
        long double result;
        MPI_Status status;
        MPI_Recv(&result, 1, MPI_LONG_DOUBLE, MPI_ANY_SOURCE, MPI_ANY_TAG, MPI_COMM_WORLD, &status);

        DONE += WORK_PER_WORKER;

        PI += result;
        
        // Tell the worker where to start from next
        MPI_Ssend(&N, 1, MPI_LONG_LONG, status.MPI_SOURCE, 0, MPI_COMM_WORLD); 
        N += WORK_PER_WORKER;
        
    }

    printf("PI is: %100.Lf\n", 4*PI/(double)N);
 
    MPI_Finalize();

    return 0;
}

int client(void) {
    long double total;


    total = 0.0;
    /*for(long long current = 0; current<totaliterations; current+=iterations){
        printf("total %lld, current, %lld, iterations %lld, total %Lf\n",totaliterations,current,iterations,total);
        total+= calc(totaliterations, current, iterations);
    }*/


    while(1) {
        total = 0.0;
        long long CURRENT;
        MPI_Status status;
        MPI_Recv(&CURRENT, 1, MPI_LONG_LONG, 0, MPI_ANY_TAG, MPI_COMM_WORLD, &status);

        total = calc(ITERATIONS, CURRENT, WORK_PER_WORKER);

        MPI_Ssend(&total, 1, MPI_LONG_DOUBLE, 0, 0, MPI_COMM_WORLD);
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
