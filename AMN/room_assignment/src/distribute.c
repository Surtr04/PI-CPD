#include "generators.h"
#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <math.h>

void randomseed (unsigned int seed) {
	srand(seed);
}

void rand_dislikes (unsigned long* dislike_matrix, unsigned long students, unsigned long min, unsigned long max) {

	unsigned long i,j;

	for (i = 0; i < students; ++i) {

		dislike_matrix[i * students + i] = ULONG_MAX;

		for (j = i + 1; j < students; ++j) {
			dislike_matrix[i * students + j] = dislike_matrix [j * students + i] = randomul_limited(min, max);
		}
			
	}

}

unsigned long distribute_random (unsigned long * dislikes, unsigned long * rooms, unsigned long * assigned, unsigned long nstudents) {
	unsigned long cost;
	unsigned long i;
	unsigned long laststudent = nstudents - 1;
	unsigned long nrooms = nstudents / 2;
	unsigned long s1;
	unsigned long s2;

	for ( i = 0 ; i < nstudents ; ++i )
		assigned[i] = ULONG_MAX;

	cost = 0;
	for ( i = 0 ; i < nrooms ; ++i )
	{
		do
		{
			s1 = randomul_limited(0, laststudent);
		}
		while (assigned[ s1 ] < ULONG_MAX);
		assigned[s1] = i;
		do
		{
			s2 = randomul_limited(0, laststudent);
		}
		while (assigned[s2] < ULONG_MAX);
		assigned[s2] = i;
		rooms[i * 2    ] = s1;
		rooms[i * 2 + 1] = s2;
		cost += dislikes[s1 * nstudents + s2];
	}

	return cost;
}


unsigned long distribute_wo_sa (unsigned long * dislikes, unsigned long * rooms, unsigned long nstudents) {
	unsigned long * assigned;
	unsigned long   cost;
	unsigned long   i, j;
	unsigned long   laststudent = nstudents - 1;
	unsigned long   max = nstudents * nstudents;
	unsigned long   p1;
	unsigned long   p2;
	unsigned long   r1;
	unsigned long   r2;
	unsigned long   sa;
	unsigned long   sb;
	unsigned long   s1;
	unsigned long   s2;
	unsigned long   s3;
	unsigned long   s4;
	long   dcost;

	assigned = (unsigned long *) malloc(nstudents * sizeof(unsigned long));
	if (!assigned)
	{
		fprintf(stderr, "Failed to allocate memory for the assigned vector!\n");
		fprintf(stderr, "\tERROR %d : %s\n", errno, strerror(errno));
		exit(errno);
	}

	cost = distribute_random(dislikes, rooms, assigned, nstudents);
	
	i = max;
	j = nstudents;

	while (cost && i && j) {
	// Find two students which are not roommates
		do
		{
			s1 = randomul_limited(0, laststudent);
			s2 = randomul_limited(0, laststudent);
		}
		while (assigned[s1] == assigned[s2]);

	
		// Room of the first student
		r1 = assigned[s1];
		sa = rooms[r1 * 2    ];
		sb = rooms[r1 * 2 + 1];
		p1 = (s1 == sa);
		s3 = p1 ? sb : sa;

		// Room of the second student
		r2 = assigned[s2];
		sa = rooms[r2 * 2    ];
		sb = rooms[r2 * 2 + 1];
		p2 = (s2 == sa);
		s4 = p2 ? sb : sa;
	
		dcost = dislikes[s1 * nstudents + s4]
		      + dislikes[s2 * nstudents + s3]
			  - dislikes[s1 * nstudents + s3]
			  - dislikes[s2 * nstudents + s4];
	
		if ( dcost < 0 ) {	
			assigned[s3] = r2;
			assigned[s4] = r1;
			rooms[r1 * 2 + p1] = s4;
			rooms[r2 * 2 + p2] = s3;	
			if (dcost) {
				cost += dcost;
				j = nstudents;
			} else
				--j;
			
			i = max;
		}
		else
		{
			--i;
		}
	}
	
	free(assigned);

	return cost;
}



unsigned long distribute_w_sa (unsigned long * dislikes, unsigned long * rooms, unsigned long nstudents, double t0) {
	
	unsigned long * assigned;
	unsigned long   cost;
	unsigned long   i, j;
	unsigned long   laststudent = nstudents - 1;
	unsigned long   max = nstudents * nstudents;
	unsigned long   p1;
	unsigned long   p2;
	unsigned long   r1;
	unsigned long   r2;
	unsigned long   sa;
	unsigned long   sb;
	unsigned long   s1;
	unsigned long   s2;
	unsigned long   s3;
	unsigned long   s4;
	long   dcost;

	double t = t0;


	assigned = (unsigned long *) malloc(nstudents * sizeof(unsigned long));
	if (!assigned)
	{
		fprintf(stderr, "Failed to allocate memory for the assigned vector!\n");
		fprintf(stderr, "\tERROR %d : %s\n", errno, strerror(errno));
		exit(errno);
	}
	
	cost = distribute_random(dislikes, rooms, assigned, nstudents);
	
	i = max;
	j = nstudents;

	while (cost && i && j) {
	// Find two students which are not roommates
		do
		{
			s1 = randomul_limited(0, laststudent);
			s2 = randomul_limited(0, laststudent);
		}
		while (assigned[s1] == assigned[s2]);

	// Find their roommates
		// Room of the first student
		r1 = assigned[s1];
		sa = rooms[r1 * 2    ];
		sb = rooms[r1 * 2 + 1];
		p1 = (s1 == sa);
		s3 = p1 ? sb : sa;

		// Room of the second student
		r2 = assigned[s2];
		sa = rooms[r2 * 2    ];
		sb = rooms[r2 * 2 + 1];
		p2 = (s2 == sa);
		s4 = p2 ? sb : sa;

	// Get the cost in swapping them
		dcost = dislikes[s1 * nstudents + s4]
		      + dislikes[s2 * nstudents + s3]
			  - dislikes[s1 * nstudents + s3]
			  - dislikes[s2 * nstudents + s4];	

		double r = randDouble();
		double f = (double) (- dcost) / (double) t;
		double e = exp(f);
		if (dcost < 0 || (e >= r)) {	
	// Swap the roommates
			assigned[s3] = r2;
			assigned[s4] = r1;
			rooms[r1 * 2 + p1] = s4;
			rooms[r2 * 2 + p2] = s3;
	// Update the total cost
			if (dcost) {
				cost += dcost;
				j = nstudents;
			} else
				--j;

			// since sometimes dcost is negative and |dcost| > cost, if such happens, assume the value should be zero and wrap up			
				if (cost && dcost < 0 && ((unsigned long)(- dcost)) > cost)
					cost = 0;			
			//Reset iterations
			i = max;
		}
		else {
			--i;
		}

		//cool the system
			t *= 0.999;
	}
	
	free(assigned);

	return cost;
}

