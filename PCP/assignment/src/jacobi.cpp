#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <time.h>
#include <sys/time.h>
#include <cilk/cilk.h>
#include <cilk/cilk_api.h>


void showMatrix(double *matrix,int n) {

	int i,j;

	for (i = 0; i < n; ++i) {
		for (j = 0; j < n; ++j) {
			printf("%.2f ",matrix[i * n + j]);
		}
		printf("\n");
	}

	return;
}

void showVector(double *vector, int n) {

	int i,j;

	for (i = 0; i < n; ++i) {
			printf("%.2f\n",vector[i]);				
	}

	return;

}

double* matrixVect (double *a, double *b, int n) {
	
	double value = 0;
	double *res = (double*) malloc(n * sizeof(double));

	for (int i = 0; i < n; ++i)	{ 
		for(int j = 0; j < n; ++j) {
			value += a[i * n + j] * b[j];
		}		
		res[i] = value;
		value = 0;
	}
	
	
	return res;

}

double* matrixDot (double *a, double *b, int n) {

	int i,k;
	double value = 0;
	double *res = (double*) malloc(n * n * sizeof(double));

	for (i = 0; i < n; ++i) {
		for(int j = 0; j < n; ++j) {
			for(k = 0; k < n; ++k) {
					value += a[i * n + k] * b[k * n + j];
			}
			res[i * n + j] = value;
			value = 0;
		}
	}
	
	
	return res;

}

double* diagonalInverse (double *coeff, int n) {

	double *inv = (double*) malloc (n * n * sizeof(double));

	cilk_for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			if (i == j) 
				inv[i * n + j] = (double)(1/coeff[i * n + j]);			
			else
				inv[i * n + j] = 0;
		}
	}

	return inv;
}

double *LUMatrix (double *coeff, int n) {

	double *r = (double*) malloc (n * n * sizeof(double));

	cilk_for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			if (i == j) 
				r[i * n + j] = 0;			
			else
				r[i * n + j] = coeff[i * n + j];
		}
	}

	return r;

}

int main(int argc, char **argv) {


	struct timeval stop;
	struct timeval start;

	int size = 2048;
	int iter = 100;
	__cilkrts_set_param("nworkers", argv[1]);
	double *coeff = (double*) malloc (size * size * sizeof(double));
	double *approx = (double*) malloc (size * sizeof(double));
	double *b = (double*) malloc (size * sizeof(double));

	srand(time(NULL));
	for(int i = 0; i < size; i++) {
		for(int j = 0; j < size; j++) {
			coeff[i * size + j] = (double) ((rand() % size) + 1) - size/2;		
		}
		approx[i] = (double) ((rand() % 10) + 1) ;
		b[i] = (double) ((rand() % 10) + 1);
	}
	gettimeofday(&start, NULL); 
	double *inv = diagonalInverse(coeff, size);
	double *r = LUMatrix(coeff, size);


	double *res,*temp;
	for (int ct = 0; ct < iter; ct++) {

		res = matrixVect(r, approx, size);
		temp = (double*) malloc (size * sizeof(double));

		cilk_for(int i = 0; i < size; i++)
			temp[i] = b[i] - res[i];

		res = matrixVect(inv, temp, size);

		cilk_for(int i = 0; i < size; i++) 
			approx[i] = res[i];

		printf("The Value after iteration %d is\n",ct);
        for(int i = 0; i<size; i++)
            printf("%.3f\n",approx[i]);

        free(res);
        free(temp);

	}
	gettimeofday(&stop, NULL); 
	printf("\n\nComputing time: %lu s - %d us\n",stop.tv_sec - start.tv_sec,stop.tv_usec - start.tv_usec);


	free(coeff);
	free(approx);
	free(b);
	free(inv);
	free(r);

	return 0;
}