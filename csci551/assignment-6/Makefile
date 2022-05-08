INCLUDE_DIRS = 
LIB_DIRS = 
CC = gcc

CDEFS=
CFLAGS= -g -fopenmp -O3
LIBS= -lm

PRODUCT= newton falsi falsi2 omp_falsi2

HFILES= 
CFILES= newton.c falsi.c falsi2.c omp_falsi2.c

SRCS= ${HFILES} ${CFILES}
OBJS= ${CFILES:.c=.o}

all:	${PRODUCT}

clean:
	-rm -f *.o *.NEW *~
	-rm -f ${PRODUCT} ${DERIVED} ${GARBAGE}

newton: newton.c
	$(CC) $(CFLAGS) -o $@ $@.c $(LIBS)

falsi: falsi.c
	$(CC) $(CFLAGS) -o $@ $@.c $(LIBS)

falsi2: falsi2.c
	$(CC) $(CFLAGS) -o $@ $@.c $(LIBS)

omp_falsi2: omp_falsi2.c
	$(CC) $(CFLAGS) -o $@ $@.c $(LIBS)
