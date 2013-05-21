#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <time.h>
#include <sys/time.h>
#include <cilk/cilk.h>
#include <cilk/cilk_api.h>


#define IND(A, x, y, d) A[(x)*(d)+(y)]

void showMatrix(float *matrix,int n) {

	int i,j;

	for (i = 0; i < n; ++i) {
		for (j = 0; j < n; ++j) {
			printf("%.2f ",matrix[i * n + j]);
		}
		printf("\n");
	}

	return;
}

float* matrixDot (float *a, float *b, int n) {

	
	float value = 0;
	float *res = (float*) malloc(n * n * sizeof(float));

	cilk_for (int i = 0; i < n; ++i) {
		cilk_for(int j = 0; j < n; ++j) {			
			for(int k = 0; k < n; ++k) {
					value += a[i * n + k] * b[k * n + j];
			}
			res[i * n + j] = value;
			value = 0;
		}
	}
	
	
	return res;

}

int main (int argc, char **argv) {

	int size = 4096;
	int i,j;

	struct timeval stop;
	struct timeval start;

	
	srand(time(NULL));

	float *mA = (float*) malloc(size * size * sizeof(float));
	float *mB = (float*) malloc(size * size * sizeof(float));


	for (i = 0; i < size; ++i) {
		for (j = 0; j < size; ++j) {
			mA[i * size + j] = (float) ((rand() % 10) + 1);			
			mB[i * size + j] = (float) ((rand() % 10) + 1);
		}		
	}

	// showMatrix(mA, size);
	// printf("\n");
	// showMatrix(mB, size);
	__cilkrts_set_param("nworkers", "4");
	gettimeofday(&start, NULL); 
	float *res = matrixDot(mA,mB,size);
	gettimeofday(&stop, NULL); 
	printf("\n");
	showMatrix(res, size);

	printf("\n\nComputing time: %lu s - %d us\n",stop.tv_sec - start.tv_sec,stop.tv_usec - start.tv_usec);

	return 0;
}
