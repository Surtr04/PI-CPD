#include <stdio.h>
#include <stdlib.h>

#define SIZE 2

void showMatrix(int **matrix) {

	int i,j;

	for (i = 0; i < SIZE; i++) {
		for (j = 0; j < SIZE; j++) {
			printf(" %d ",matrix[i][j]);
		}
		printf("\n");
	}
}

int dotProduct (int** matrixA, int** matrixB, int** matrixC) {


	int i,j,k;
	int acc;

	for (i = 0; i < SIZE; i++) {
		for (j = 0; j < SIZE; j++)
			for(k = 0; k < SIZE; k++) {
				acc += matrixA[i][k] * matrixB[k][j];				
			}
			printf("%d\n", acc);					
			matrixC[i][j] = acc;			
			acc = 0;
	}		
	return 0;
}

int** initRandMatrix() {

	int i,j;
	int **matrix = (int**) malloc(SIZE * sizeof(int*));

	for (i = 0; i < SIZE; i++) {
		matrix[i] = (int*) malloc(SIZE * sizeof(int));
		for (j = 0; j < SIZE; j++) {			
			matrix[i][j] = (rand() % 3) + 1;
		}
	}

	return matrix;

}


int** initMatrix() {

	int i;
	int **matrix = (int**) malloc(SIZE * sizeof(int*));

	for (i = 0; i < SIZE; i++) {
		matrix[i] = (int*) malloc(SIZE * sizeof(int));							
	}

	return matrix;

}


int** initUnitMatrix() {

	int i,j;
	int **matrix = (int**) malloc(SIZE * sizeof(int*));

	for (i = 0; i < SIZE; i++) {
		matrix[i] = (int*) malloc(SIZE * sizeof(int));
		for (j = 0; j < SIZE; j++) {			
			matrix[i][j] = 1;
		}
	}

	return matrix;

}


int main (int argc, char** argv) {

	int** matrixA = initRandMatrix();
	int** matrixB = initUnitMatrix();
	int** matrixC = initMatrix();

	dotProduct(matrixA, matrixB, matrixC);

	
	showMatrix(matrixC);

}