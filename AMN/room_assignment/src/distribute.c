#include <limits.h>
#include "generators.h"


void rand_dislikes (unsigned long* dislike_matrix, unsigned long students, unsigned long min, unsigned long max) {

	unsigned long i,j;

	for (i = 0; i < students; ++i) {

		dislike_matrix[i * students + i] = ULONG_MAX;

		for (j = i + 1; j < students; ++j) {
			dislike_matrix[i * students + j] = dislike_matrix [j * students + i] = randomul_limited(min, max);
		}
			
	}

}