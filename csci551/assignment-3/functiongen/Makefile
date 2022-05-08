INCLUDE_DIRS = 
LIB_DIRS = 
CC=gcc
#CC=icc

CDEFS=
OMP_CFLAGS= -O0 -fopenmp $(INCLUDE_DIRS) $(CDEFS)
#OMP_CFLAGS= -O0 -qopenmp $(INCLUDE_DIRS) $(CDEFS)
CFLAGS= -O0 $(INCLUDE_DIRS) $(CDEFS)
#CFLAGS= -O0 $(INCLUDE_DIRS) $(CDEFS)
LIBS= -lm

HFILES= 
CFILES= timeinterp.c csvtostatic.c

SRCS= ${HFILES} ${CFILES}
OBJS= ${CFILES:.c=.o}

all:	csvtostatic timeinterp

clean:
	-rm -f *.o *.d
	-rm -f csvtostatic timeinterp

distclean:
	-rm -f *.o *.d
	-rm -f csvtostatic

csvtostatic: csvtostatic.o
	$(CC) $(LDFLAGS) $(CFLAGS) -o $@ $@.o

timeinterp: timeinterp.o
	$(CC) $(LDFLAGS) $(CFLAGS) -o $@ $@.o $(LIBS)

depend:

.c.o:
	$(CC) $(CFLAGS) -c $<
