CC=gcc
MPICC=mpicc
CFLAGS=	-Wall -Wextra -std=c99 -pedantic -g
LDFLAGS= -lm
OBJS=seq.o generators.o distribute.o helpers.o
MPIOBJS=mpi.o generators.o distribute.o helpers.o

.PHONY: clean

all: $(OBJS)
	$(CC) $(CFLAGS) $^ $(LDFLAGS)

mpi: $(MPIOBJS)
	$(MPICC) $(CFLAGS) $^ $(LDFLAGS)

mpi.o: mpi.c distribute.h helpers.h
	$(MPICC) $(CFLAGS) -c mpi.c

seq.o: seq.c distribute.h
	$(CC) $(CFLAGS) -c seq.c 


generators.o: generators.c generators.h
	$(CC) $(CFLAGS) -c generators.c


distribute.o: distribute.c generators.h
	$(CC) $(CFLAGS) -c distribute.c

helpers.o: helpers.c helpers.h
	$(CC) $(CFLAGS) -c helpers.c




clean:
	rm *.o
