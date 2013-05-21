#include <stdio.h>
#include <omp.h>

#define size 2048

double a1[size][size], b1[size][size], c1[size][size];


static void doMultiply(double a[size][size], double b[size][size], double c[size][size]) {
   
    #pragma omp parallel num_threads(4)
    for (int i=0; i<size; i++)
        for (int k=0; k<size; k++)
            for (int j=0; j<size; j++)
                c[i][j] += a[i][k] * b[k][j];
}

double MFlops(double time) {
    
    return(2.0*size*size*size/(time*1000000.0));
}

int main() {

    double starttime = omp_get_wtime();
   
    doMultiply(a1,b1,c1);
    
    double walltime = omp_get_wtime()-starttime;
    
    printf("F=%0.1f Time=%.0.2f; %.0f MFlop/s\n",a1[10][10],walltime, MFlops(walltime) );
    
    return 0;
}
