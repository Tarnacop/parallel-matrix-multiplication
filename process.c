#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>
#include <math.h>

long double calc(int total, int start, int iterations);
int main(int argc, char **argv) {
    long double pi, total;


    long long totaliterations = 10000000000;
    long long iterations = 10000000;
    total = 0.0;
    for(long long current = 0; current<totaliterations; current+=iterations){
        printf("total %lld, current, %lld, iterations %lld, total %Lf\n",totaliterations,current,iterations,total);
        total+= calc(totaliterations, current, iterations);
    }


    printf("\nComputing approximation to pi using %lld iterations\n", totaliterations);

    /*for (i=1; i<=iterations; i++) {
        c = ((long double)i - 0.5) / ((long double)iterations);
        b = pow(c, 2.0);
        a = 1.0 + b;
        calc = 1.0/a;
        total += calc;
    }*/
    
    pi = total * 4.0 / ((long double)totaliterations);

    printf("\nPi has been calculated to be: %.100Lf\n", pi);

    return 0;
}

long double calc(int totaliterations, int current, int iterations){
    long double a,b,c,calc = 0.0;
    for (long i=current; i<current+iterations; i++) {
        c = ((long double)i - 0.5) / ((long double)totaliterations);
        b = pow(c, 2.0);
        a = 1.0 + b;
        calc += 1.0/a;
    }
    return calc;
}
