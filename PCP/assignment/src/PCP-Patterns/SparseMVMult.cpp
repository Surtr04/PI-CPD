#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include "random.h"

/* original code from SciMark */


double *x;
double *y;
double *val;
int *col;
int *row;

void initialize(int N, int nz, Random R) {
    
    /* initialize vector multipliers and storage for result */
    /* y = A*x;  */
    
    x = RandomVector(N, R);
    y = (double*) malloc(sizeof(double)*N);
    
#if 0
    // initialize square sparse matrix
    //
    // for this test, we create a sparse matrix with M/nz nonzeros
    // per row, with spaced-out evenly between the begining of the
    // row to the main diagonal.  Thus, the resulting pattern looks
    // like
    //             +-----------------+
    //             +*                +
    //             +***              +
    //             +* * *            +
    //             +** *  *          +
    //             +**  *   *        +
    //             +* *   *   *      +
    //             +*  *   *    *    +
    //             +*   *    *    *  +
    //             +-----------------+
    //
    // (as best reproducible with integer artihmetic)
    // Note that the first nr rows will have elements past
    // the diagonal.
#endif
    
    int nr = nz/N;      /* average number of nonzeros per row  */
    int anz = nr *N;    /* _actual_ number of nonzeros         */
    
    val = RandomVector(anz, R);
    col = (int*) malloc(sizeof(int)*nz);
    row = (int*) malloc(sizeof(int)*(N+1));
    int r=0;
    int cycles=1;
    
    row[0] = 0;
    for (int r=0; r<N; r++)
    {
        /* initialize elements for row r */
        
        int rowr = row[r];
        int step = r/ nr;
        int i=0;
        
        row[r+1] = rowr + nr;
        if (step < 1) step = 1;   /* take at least unit steps */
        
        
        for (i=0; i<nr; i++)
            col[rowr+i] = i*step;
        
    }
}

void free() {
    free(row);
    free(col);
    free(val);
    free(y);
    free(x);
    
}

double SparseCompRow_num_flops(int N, int nz, int num_iterations) {
    /* Note that if nz does not divide N evenly, then the
     actual number of nonzeros used is adjusted slightly.
     */
    int actual_nz = (nz/N) * N;
    return ((double)actual_nz) * 2.0 * ((double) num_iterations);
}

/* computes  a matrix-vector multiply with a sparse matrix
 held in compress-row format.  If the size of the matrix
 in MxN with nz nonzeros, then the val[] is the nz nonzeros,
 with its ith entry in column col[i].  The integer vector row[]
 is of size M+1 and row[i] points to the begining of the
 ith row in col[].
 */

void SparseCompRow_matmult( int M, double *y, double *val, int *row,
                           int *col, double *x, int NUM_ITERATIONS) {
    
    for (int reps=0; reps<NUM_ITERATIONS; reps++) {
        
#pragma omp parallel for num_threads(8)
        for (int r=0; r<M; r++) {
            double sum = 0.0;
           for (int i=row[r]; i<row[r+1]; i++)
                sum += x[ col[i] ] * val[i];
            y[r] = sum;
        }
    }
}

const int LG_SPARSE_SIZE_M = 100000;
const int LG_SPARSE_SIZE_nz =1000000;
const int RANDOM_SEED = 101010;
const int REPS =10000;

int main(int argc, char **argv) {
    
    
    Random R = new_Random_seed(RANDOM_SEED);
    
    int N = 4096;
    int nz = 4096;
    
    initialize(N, nz, R);
    omp_set_num_threads(atoi(argv[1]));
    double starttime = omp_get_wtime();
    
    SparseCompRow_matmult(N, y, val, row, col, x, REPS);
       
    double walltime = omp_get_wtime()-starttime;
    
    printf("F=%0.1f Time=%0.2f; %.0f MFlop/s\n",y[10],walltime, SparseCompRow_num_flops(N, nz, REPS)/walltime * 1e-6 );
    
    free();
    
    return 0;
}
