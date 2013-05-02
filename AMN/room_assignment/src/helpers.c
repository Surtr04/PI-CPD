#include "helpers.h"

void printMatrix (unsigned long * matrix, unsigned long rows, unsigned long cols) {
	unsigned long i,j;
	for (i = 0; i < rows; ++i) {
		if (cols) {
			printf("%lu", matrix[i * cols]);
			for (j = 1; j < cols; ++j) {
				printf(" %lu", matrix[i * cols + j]);
			}
			printf("\n");
		}
	}
}