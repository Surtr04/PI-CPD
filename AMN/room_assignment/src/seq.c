#include <stdio.h>
#include <stdlib.h>
#include "distribute.h"
#include "helpers.h"


int main (int argc, char **argv) {

	unsigned long *rooms;
	unsigned long *dislikes;
	unsigned long students;
	unsigned long laststudent;


	if ( argc > 1 )
		students = strtoul(argv[1], NULL, 10);
	else
		students = 0;


	dislikes = (unsigned long*) malloc ( students * students * sizeof (unsigned long));
	rooms    = (unsigned long*) malloc ( students * sizeof (unsigned long));

	rand_dislikes(dislikes, students, 1, 10);


	printMatrix(dislikes, students, students);


}