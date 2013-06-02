#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/time.h>
#include <cilk/cilk.h>
#include <cilk/cilk_api.h>

double seq_fib(double n) {
    double i, j;
    if (n<2) return(n);
    
    return(seq_fib(n-2)+seq_fib(n-1));
}    

double fib(double n) {
    if (n < 2)
        return n;

    if (n < 30)
        return seq_fib(n);

    double x = cilk_spawn fib(n-1);
    double y = fib(n-2);
    cilk_sync;
    return x + y;
}

int main(int argc, char *argv[]) {
    
    double n = 50;
    struct timeval stop;
    struct timeval start;

    // If we've got a parameter, assume it's the number of workers to be used
    if (argc > 1)
    {
        // Values less than 1, or parameters that aren't numbers aren't allowed
        if (atoi(argv[1]) < 1)
        {
            printf("Usage: fib [workers]\n");
            return 1;
        }

        // Set the number of workers to be used
        __cilkrts_set_param("nworkers", argv[1]);
    }

    // Time how long it takes to calculate the nth Fibonacci number
    gettimeofday(&start, NULL);
    double result = fib(n);
    gettimeofday(&stop, NULL); 

    // Display our results
     
    printf("Fibonacci number #%f is %.0f.\n", n, result);
    printf("Calculated in %lus %dus, using %d workers.\n",
           stop.tv_sec - start.tv_sec,stop.tv_usec - start.tv_usec, __cilkrts_get_nworkers());

    return 0;
}