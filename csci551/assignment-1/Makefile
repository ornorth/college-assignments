INCLUDE_DIRS = 
LIB_DIRS = 
CC = gcc
LDFLAGS = -lm

CDEFS=
CFLAGS= -g -Wall -fopenmp $(INCLUDE_DIRS) $(CDEFS)
CFLAGS2= -O3 -mssse3 $(INCLUDE_DIRS) $(CDEFS)
CFLAGS3= -g -O3 -fopenmp -mssse3 $(INCLUDE_DIRS) $(SDEFS)
LIBS= -lpthread

PRODUCT= hello_omp dct2 sharpen

HFILES= 
CFILES= sharpen.c matrotate.c hello_omp.c dct2.c

SRCS= ${HFILES} ${CFILES}
OBJS= ${CFILES:.c=.o}

all:	${PRODUCT}

clean:
	-rm -f *.o *.NEW *~
	-rm -f ${PRODUCT} ${DERIVED} ${GARBAGE}

hello_omp:	hello_omp.c
	$(CC) $(CFLAGS) -o $@ hello_omp.c

dct2: dct2.o
	$(CC) $(CFLAGS) -o $@ $@.o $(LDFLAGS)

sharpen: sharpen.o
	$(CC) $(LDFLAGS) $(CFLAGS2) -o $@ $@.o $(LIBS)

depend:

.c.o:
	$(CC) $(CFLAGS3) -c $<
