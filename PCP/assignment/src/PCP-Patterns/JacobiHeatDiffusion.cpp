
#include <stdio.h>
#include <stdlib.h>
#include  <omp.h>

#define size 2048  // testar também 1024 ou 2048 (não deve escalar)
#define iter 100

double domain[size][size];
double aux[size][size];

inline void stencil(double in[size][size], double out[size][size], int i, int j) {
    out[i][j]= 0.25 * (in[i-1][j]+in[i+1][j]+in[i][j-1]+in[i][j+1]);    
}

void jacobi(double a[size][size]){
    
    #pragma omp parallel num_threads(8)
    for(int k=0; k<iter; k++) {
    
//#pragma omp parallel for num_threads(4)  /* less efficient */
        #pragma omp  for
        for(int i=1; i<size-1; i++) {
            for(int j=1; j<size-1; j++) {
                stencil(a,aux,i,j);
            }
        }
        
//#pragma omp parallel for num_threads(4) /* less efficient */
        #pragma omp  for
        for(int i=1; i<size-1; i++) {
            for(int j=1; j<size; j++) {
                stencil(aux,a,i,j);
            }
        }
        
    }

}

double MFlops(double time) {
    
    return(4.0*(size-2.0)*(size-2.0)*iter/(time*1000000.0));
}

int main(int argc, char * argv[]) {
    
    
    omp_set_num_threads(atoi(argv[1]));
    double starttime = omp_get_wtime();
    
    jacobi(domain);
    
    double walltime = omp_get_wtime()-starttime;
    
    printf("F=%0.1f Time=%.0.2f; %.0f MFlop/s\n",domain[10][10],walltime, MFlops(walltime) );
    
    return 0;
}

