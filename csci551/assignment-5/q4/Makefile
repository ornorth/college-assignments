INCLUDE_DIRS = 
LIB_DIRS = 
CC=gcc

CDEFS=
CFLAGS= -O0 $(INCLUDE_DIRS) $(CDEFS)
#CFLAGS= -O0 -g -pg $(INCLUDE_DIRS) $(CDEFS)
LIBS= 

HFILES= 
CFILES= gewpp.c omp_gewpp.c

SRCS= ${HFILES} ${CFILES}
OBJS= ${CFILES:.c=.o}

all:	gewpp omp_gewpp

clean:
	-rm -f *.o *.d
	-rm -f gewpp omp_gewpp

distclean:
	-rm -f *.o *.d
	-rm -f gewpp omp_gewpp

gewpp: gewpp.o
	$(CC) $(LDFLAGS) $(CFLAGS) -o $@ $@.o

omp_gewpp: omp_gewpp.o
	$(CC) $(LDFLAGS) -fopenmp $(CFLAGS) -o $@ $@.o

depend:

.c.o:
	$(CC) $(CFLAGS) -c $<
