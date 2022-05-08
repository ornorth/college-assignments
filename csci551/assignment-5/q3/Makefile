INCLUDE_DIRS =
LIB_DIRS =
#LIB_DIRS = -L/opt/intel/compilers_and_libraries_2020.0.166/linux/mpi/intel64/lib/release -L/opt/intel/compilers_and_libraries_2020.0.166/linux/mpi/intel64/lib
CC = gcc

CDEFS=
CFLAGS= -g -Wall -O3 $(INCLUDE_DIRS) $(CDEFS)
OMPCFLAGS= -g -fopenmp -Wall -O3 $(INCLUDE_DIRS) $(CDEFS)
LIBS=

PRODUCT= mat_mult omp_mult

HFILES= 
CFILES= mat_mult.c omp_mult.c

SRCS= ${HFILES} ${CFILES}
OBJS= ${CFILES:.c=.o}

all:	${PRODUCT}

clean:
	-rm -f *.o *.NEW *~
	-rm -f ${PRODUCT} ${DERIVED} ${GARBAGE}

mat_mult: mat_mult.c
	$(CC) $(CFLAGS) -o $@ $@.c $(LIB_DIRS)

omp_mult: omp_mult.c
	$(CC) $(OMPCFLAGS) -o $@ $@.c $(LIB_DIRS)
