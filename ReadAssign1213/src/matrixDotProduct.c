#include "matrixDotProduct.h"


void showMatrix(float **matrix) {

	int i,j;

	for (i = 0; i < size; i++) {
		for (j = 0; j < size; j++) {
			printf(" %f ",matrix[i][j]);
		}
		printf("\n");
	}
}


float** transposeMatrix(float** matrix) {

	int i,j;
	float** result = initMatrix();

	for (i = 0; i < size; i++) {
		for (j = 0; j < size; j++){
			result[i][j] = matrix[j][i];
		}	
	}
	return result;
}


int dotProductTransposed (float** matrixA, float** matrixB, float** matrixC) {

	int i,j,k;
	float acc = 0;	
	float** tMatrix = transposeMatrix(matrixB);

	for (i = 0; i < size; i++) {
		for (j = 0; j < size; j++) {
			for(k = 0; k < size; k++) {
				acc += matrixA[i][k] * tMatrix[j][k];				
			}		
			matrixC[i][j] = acc;	
			acc = 0;
		}
	}		
	
	return 0;

}


int dotProduct (float** matrixA, float** matrixB, float** matrixC) {


	int i,j,k;
	float acc = 0;	

	for (i = 0; i < size; i++) {
		for (j = 0; j < size; j++) {
			for(k = 0; k < size; k++) {
				acc += matrixA[i][k] * matrixB[k][j];				
			}		
			matrixC[i][j] = acc;	
			acc = 0;
		}
	}		
	
	return 0;
}

int dotProduct_papi () {


	int i,j,k;
	float acc = 0;	

	for (i = 0; i < size; i++) {
		for (j = 0; j < size; j++) {
			for(k = 0; k < size; k++) {
				acc += m->matrixA[i][k] * m->matrixB[k][j];				
			}		
			m->matrixC[i][j] = acc;	
			acc = 0;
		}
	}		
	
	return 0;
}

float** initRandMatrix() {

	int i,j;
	float **matrix = (float**) malloc(size * sizeof(float*));

	for (i = 0; i < size; i++) {
		matrix[i] = (float*) malloc(size * sizeof(float));
		for (j = 0; j < size; j++) {			
			matrix[i][j] = (rand() % 100) + 1;
		}
	}

	return matrix;

}


float** initMatrix() {

	int i;
	float **matrix = (float**) malloc(size * sizeof(float*));

	for (i = 0; i < size; i++) {
		matrix[i] = (float*) malloc(size * sizeof(float));							
	}

	return matrix;

}


float** initUnitMatrix() {

	int i,j;
	float **matrix = (float**) malloc(size * sizeof(float*));

	for (i = 0; i < size; i++) {
		matrix[i] = (float*) malloc(size * sizeof(float));
		for (j = 0; j < size; j++) {			
			matrix[i][j] = 1;
		}
	}

	return matrix;

}


// int mainNoOpt (int argc, char** argv) {


// 	float** matrixA = initRandMatrix();
// 	float** matrixB = initUnitMatrix();
// 	float** matrixC = initMatrix();	
// 	dotProduct(matrixA, matrixB, matrixC);	
// 	showMatrix(matrixC);

// 	return 0;

// }

