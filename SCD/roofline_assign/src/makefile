CC = gcc
CFLAGS = -O3 -Wall -Wextra
LIBS = -lpapi
OBJS= matrixDotProduct.o papi.o

papi_test:$(OBJS)
	$(CC) $(CFLAGS) -o papi_test $(OBJS) $(LIBS)

papi.o:papi.c papi_errors.h matrixDotProduct.h
	$(CC) $(CFLAGS) -c papi.c

matrixDotProduct.o:matrixDotProduct.c matrixDotProduct.h papi_errors.h
	$(CC) $(CFLAGS) -c matrixDotProduct.c 

clean:
	rm *.o