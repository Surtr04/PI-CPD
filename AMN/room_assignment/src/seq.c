#include <stdio.h>
#include <stdlib.h>
#include "distribute.h"
#include "helpers.h"


int main (int argc, char **argv) {
	
	unsigned long *rooms;
	unsigned long *dislikes;
	unsigned long students;
	unsigned long laststudent;
	unsigned long i,j;
	unsigned long c1;
	unsigned long c2;
	double t0;



	if ( argc > 1 )
		students = strtoul(argv[1], NULL, 10);
	else 
		students = 0;		

	if ( argc > 2 ) 
		t0 = atof(argv[2]);
	else
		t0 = 1.0;
		
	

	laststudent = students - 1;


	dislikes = (unsigned long*) malloc ( students * students * sizeof (unsigned long));
	rooms    = (unsigned long*) malloc ( students * sizeof (unsigned long));
	rand_dislikes(dislikes, students, 1, 10);

	for (i = 0; i < laststudent; i += 2) {
		j = i + 1;
		dislikes[i * students + j] = 0;
		dislikes[j * students + i] = 0;
	}


	c1 = distribute_wo_sa(dislikes, rooms, students);
	c2 = distribute_w_sa(dislikes, rooms, students,t0);

	printf("%lu %lu;\n", c1, c2);


}