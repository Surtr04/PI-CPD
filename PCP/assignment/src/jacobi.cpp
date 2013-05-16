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

	for (int i = 0; i < n; ++i)	{ 
		for(int j = 0; j < n; ++j) {
			value += a[i * n + j] * b[j];
		}		
		res[i] = value;
		value = 0;
	}
	
	
	return res;

}

float* matrixDot (float *a, float *b, int n) {

	int i,k;
	float value = 0;
	float *res = (float*) malloc(n * n * sizeof(float));

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

float* diagonalInverse (float *coeff, int n) {

	float *inv = (float*) malloc (n * n * sizeof(float));

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			if (i == j) 
				inv[i * n + j] = (float)(1/coeff[i * n + j]);			
			else
				inv[i * n + j] = 0;
		}
	}

	return inv;
}

float *LUMatrix (float *coeff, int n) {

	float *r = (float*) malloc (n * n * sizeof(float));

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			if (i == j) 
				r[i * n + j] = 0;			
			else
				r[i * n + j] = coeff[i * n + j];
		}
	}

	return r;

}

int main() {

	int size = 10;
	int iter = 10;

	float *coeff = (float*) malloc (size * size * sizeof(float));
	float *approx = (float*) malloc (size * sizeof(float));
	float *b = (float*) malloc (size * sizeof(float));

	srand(time(NULL));
	for(int i = 0; i < size; i++) {
		for(int j = 0; j < size; j++) {
			coeff[i * size + j] = (float) ((rand() % 10) + 1);		
		}
		approx[i] = 0;
		b[i] = (float) ((rand() % 10) + 1);
	}

	float *inv = diagonalInverse(coeff, size);
	float *r = LUMatrix(coeff, size);

	float *res,*temp;
	for (int ct = 0; ct < iter; ct++) {

		res = matrixVect(r, approx, size);
		temp = (float*) malloc (size * sizeof(float));

		for(int i = 0; i < size; i++)
			temp[i] = b[i] - res[i];

		res = matrixVect(inv, temp, size);

		for(int i = 0; i < size; i++) 
			approx[i] = res[i];

		printf("The Value after iteration %d is\n",ct);
        for(int i = 0; i<size; i++)
            printf("%.3f\n",approx[i]);

        free(res);
        free(temp);

	}



	free(coeff);
	free(approx);
	free(b);
	free(inv);
	free(r);

	return 0;
}