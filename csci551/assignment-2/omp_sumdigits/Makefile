INCLUDE_DIRS = 
LIB_DIRS = 
CC=gcc

CDEFS=
CFLAGS= -g -fopenmp -O3 $(INCLUDE_DIRS) $(CDEFS)
LIBS= 

HFILES= 
CFILES= sumdigits.c

SRCS= ${HFILES} ${CFILES}
OBJS= ${CFILES:.c=.o}

all:	omp_sumdigits

clean:
	-rm -f *.o *.d
	-rm -f omp_sumdigits

distclean:
	-rm -f *.o *.d
	-rm -f omp_sumdigits

omp_sumdigits: omp_sumdigits.o
	$(CC) $(LDFLAGS) $(CFLAGS) -o $@ $@.o

depend:

.c.o:
	$(CC) $(CFLAGS) -c $<
