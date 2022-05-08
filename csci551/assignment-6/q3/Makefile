INCLUDE_DIRS = 
LIB_DIRS = 
CC = gcc

CDEFS=
CFLAGS= -g -fopenmp -O3
LIBS= -lm

PRODUCT= seqIntegrate ompIntegrate findIntersect findVIntersect

HFILES= 
CFILES= seqIntegrate.c ompIntegrate.c findIntersect.c findVIntersect.c

SRCS= ${HFILES} ${CFILES}
OBJS= ${CFILES:.c=.o}

all:	${PRODUCT}

clean:
	-rm -f *.o *.NEW *~
	-rm -f ${PRODUCT} ${DERIVED} ${GARBAGE}

seqIntegrate: seqIntegrate.c
	$(CC) $(CFLAGS) -o $@ $@.c $(LIBS)

ompIntegrate: ompIntegrate.c
	$(CC) $(CFLAGS) -o $@ $@.c $(LIBS)

findIntersect: findIntersect.c
	$(CC) $(CFLAGS) -o $@ $@.c $(LIBS)

findVIntersect: findVIntersect.c
	$(CC) $(CFLAGS) -o $@ $@.c $(LIBS)
