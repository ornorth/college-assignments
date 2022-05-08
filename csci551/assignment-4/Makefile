INCLUDE_DIRS = -I/opt/intel/compilers_and_libraries_2020.0.166/linux/mpi/intel64/include/
LIB_DIRS = -L/opt/intel/compilers_and_libraries_2020.0.166/linux/mpi/intel64/lib/debug -L/opt/intel/compilers_and_libraries_2020.0.166/linux/mpi/intel64/lib
#LIB_DIRS = -L/opt/intel/compilers_and_libraries_2020.0.166/linux/mpi/intel64/lib/release -L/opt/intel/compilers_and_libraries_2020.0.166/linux/mpi/intel64/lib
#CC = gcc
MPICC = mpicc
#CXX = mpicxx

CDEFS=
MPI_CFLAGS= -g -Wall $(INCLUDE_DIRS) $(CDEFS)
CFLAGS= -O0 $(INCLUDE_DIRS) $(CDEFS)
LIBS= -lm

PRODUCT= left_double left_float trap_double trap_float

HFILES= 
CFILES= left_double.c left_float.c trap_double.c trap_float.c

SRCS= ${HFILES} ${CFILES}
OBJS= ${CFILES:.c=.o}

all:	${PRODUCT}

clean:
	-rm -f *.o *.NEW *~
	-rm -f ${PRODUCT} ${DERIVED} ${GARBAGE}

left_double: left_double.c
	$(MPICC) $(MPI_CFLAGS) -o $@ $@.c $(LIBS) $(LIB_DIRS)

left_float: left_float.c
	$(MPICC) $(MPI_CFLAGS) -o $@ $@.c $(LIBS) $(LIB_DIRS)

trap_double: trap_double.c
	$(MPICC) $(MPI_CFLAGS) -o $@ $@.c $(LIBS) $(LIB_DIRS)

trap_float: trap_float.c
	$(MPICC) $(MPI_CFLAGS) -o $@ $@.c $(LIBS) $(LIB_DIRS)
