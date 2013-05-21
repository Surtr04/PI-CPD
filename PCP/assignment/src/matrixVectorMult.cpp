#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <time.h>
#include <sys/time.h>
#include <cilk/cilk.h>
#include <cilk/cilk_api.h>


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

void showVector(float *vector, int n) {

	int i,j;

	for (i = 0; i < n; ++i) {
			printf("%.2f\n",vector[i]);				
	}

	return;

}

float* matrixVect (float *a, float *b, int n) {
	
	float value = 0;
	float *res = (float*) malloc(n * sizeof(float));

	cilk_for (int i = 0; i < n; ++i)	{ 
		for(int j = 0; j < n; ++j) {
			value += a[i * n + j] * b[j];
		}		
		res[i] = value;
		value = 0;
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
	float *mB = (float*) malloc(size * sizeof(float));


	for (i = 0; i < size; ++i) {
		mB[i] = (float) ((rand() % 10) + 1);
		for (j = 0; j < size; ++j) {
			if ( i == j )
				mA[i * size + j] = (float) ((rand() % 10) + 1);						
		}		
	}

	 // showMatrix(mA, size);
	 // printf("\n");
	 // showVector(mB, size);

	gettimeofday(&start, NULL); 
	float *res = matrixVect(mA,mB,size);
	gettimeofday(&stop, NULL); 
	printf("\n");
	showVector(res, size);

	printf("\n\nComputing time: %lu s - %d us\n",stop.tv_sec - start.tv_sec,stop.tv_usec - start.tv_usec);

	return 0;
}