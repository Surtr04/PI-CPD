CC=gcc
CFLAGS=	-Wall -Wextra -std=c99 -pedantic
LDFLAGS= -lm
OBJS=seq.o generators.o distribute.o helpers.o

all: $(OBJS)
	$(CC) $(CFLAGS) $^ $(LDFLAGS)



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