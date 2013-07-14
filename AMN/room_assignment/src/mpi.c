#include <errno.h>
#include <limits.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include "distribute.h"
#include "helpers.h"

#include <mpi.h>

int main ( int argc , char * argv[] ) {
	unsigned long * dislikes;
	unsigned long   c1;
	unsigned long   c2;
	unsigned long   i;
	unsigned long   j;
	unsigned long   laststudent;
	unsigned long   lc1;
	unsigned long   lc2;
	unsigned long   nstudents;
	unsigned long * rooms;
	double   t0;
	int    mpi_rank;
	int    mpi_size;

	MPI_Init(&argc , &argv);
	MPI_Comm_rank(MPI_COMM_WORLD,&mpi_rank);
	MPI_Comm_size (MPI_COMM_WORLD, &mpi_size);

	if (!mpi_rank)
	{		
		if ( argc > 1 )
			nstudents = strtoul(argv[1], NULL, 10);
		if (argc > 2)
			t0 = atof(argv[2]);
		else
			t0 = 1.0;
	}

	MPI_Bcast (&nstudents, 1, MPI_UNSIGNED_LONG, 0, MPI_COMM_WORLD);
	MPI_Bcast(&t0, 1, MPI_DOUBLE, 0, MPI_COMM_WORLD);

	laststudent = nstudents - 1;

	dislikes = (unsigned long *) malloc( nstudents * nstudents * sizeof(unsigned long));

	randomseed(time(NULL) * (mpi_rank + 1));

	if (!mpi_rank)
	{
		//0. Generate dislike matrices
		rand_dislikes(dislikes , nstudents , 1 , 10);

		//0. Add perfect solution
		for (i = 0 ; i < laststudent ; i += 2)
		{
			j = i + 1;
			dislikes[i * nstudents + j] = 0;
			dislikes[j * nstudents + i] = 0;
		}
	}
	MPI_Bcast (dislikes, nstudents * nstudents, MPI_UNSIGNED_LONG, 0, MPI_COMM_WORLD);

	//0. Create arrays
	rooms = (unsigned long*) malloc (nstudents * sizeof (unsigned long));
	
	//1. No simulated annealing
	lc1 = distribute_wo_sa(dislikes, rooms, nstudents);

	//2. Now with simulated annealing
	lc2 = distribute_w_sa(dislikes, rooms, nstudents, t0);

	MPI_Reduce (&lc1, &c1, 1, MPI_UNSIGNED_LONG, MPI_MIN, 0, MPI_COMM_WORLD);
	MPI_Reduce (&lc2, &c2, 1, MPI_UNSIGNED_LONG, MPI_MIN, 0, MPI_COMM_WORLD);

	if (!mpi_rank) {		
		printf("%lu %lu\n", c1, c2);
	}

	free (rooms);
	free (dislikes);

	MPI_Finalize();
	
	return 0;
}