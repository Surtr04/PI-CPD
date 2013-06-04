#
# Makefile for lesson
#
FVLib_CONFIG=FVLib-config
FVLib_CXX    =`$(FVLib_CONFIG) --cxx`
LLVM=llvm-g++-4.2
FVLib_CFLAGS  =`$(FVLib_CONFIG) --cflags` -O3 -fopenmp -lpapi -D _DEBUGS
FVLib_LIBS     =`$(FVLib_CONFIG) --libs` 
OBJ_CODE = user.o functional.o main.o papi.o



poisson:  $(OBJ_CODE)  
	$(FVLib_CXX) $(FVLib_CFLAGS)  $(OBJ_CODE)  -o lesson  $(FVLib_LIBS)

clean:
	/bin/rm -f $(OBJ_CODE)  lesson 

.SUFFIXES: .c .cc .cpp .cxx .o

.cpp.o:
	$(FVLib_CXX)$  $(FVLib_CFLAGS) -c -g $<

.cc.o:
	$(FVLib_CXX)   $(FVLib_CFLAGS) -c  -g $<
