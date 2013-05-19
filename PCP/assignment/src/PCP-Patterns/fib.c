#include <stdio.h>
#include <omp.h>

double seq_fib(double n) {
    double i, j;
    if (n<2) return(n);
    
    return(seq_fib(n-2)+seq_fib(n-1));
}    


double fib(double n) {
       double i, j;
       if (n<2) return(n);

    //if (n<30) return(fib(n-2)+fib(n-1));
    if (n<30) return(seq_fib(n));

    
#pragma omp task shared(i)
       i = fib(n-1);

       j = fib(n-2);
#pragma omp taskwait

        return(i+j);
}

int main() {

    double r;
    
    double time = omp_get_wtime();
    
#pragma omp parallel num_threads(4)
#pragma omp single
    r = fib(47);
    
    printf("F=%.0f Time=%f\n",r,omp_get_wtime()-time);
   return(1);
}
