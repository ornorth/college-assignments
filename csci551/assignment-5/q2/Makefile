INCLUDE_DIRS = -I/opt/intel/compilers_and_libraries_2020.0.166/linux/mpi/intel64/include/
LIB_DIRS = -L/opt/intel/compilers_and_libraries_2020.0.166/linux/mpi/intel64/lib/debug -L/opt/intel/compilers_and_libraries_2020.0.166/linux/mpi/intel64/lib
#LIB_DIRS = -L/opt/intel/compilers_and_libraries_2020.0.166/linux/mpi/intel64/lib/release -L/opt/intel/compilers_and_libraries_2020.0.166/linux/mpi/intel64/lib
CC = gcc
MPICC = mpicc
CXX = mpicxx

CDEFS=
MPICFLAGS= -g -Wall $(INCLUDE_DIRS) $(CDEFS)
OMPCFLAGS= -g -fopenmp -O3
LIBS=

PRODUCT= omp_pi mpi_pi

HFILES= 
CFILES= omp_pi.c mpi_pi.c

SRCS= ${HFILES} ${CFILES}
OBJS= ${CFILES:.c=.o}

all:	${PRODUCT}

clean:
	-rm -f *.o *.NEW *~
	-rm -f ${PRODUCT} ${DERIVED} ${GARBAGE}

omp_pi: omp_pi.c
	$(CC) $(OMPCFLAGS) -o $@ $@.c 

mpi_pi:	mpi_pi.c
	$(MPICC) $(MPICFLAGS) -o $@ $@.c $(LIB_DIRS)
