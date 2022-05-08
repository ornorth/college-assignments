INCLUDE_DIRS = 
LIB_DIRS = 
CC = gcc

CDEFS=
#CFLAGS= -O3 -msse3 $(INCLUDE_DIRS) $(CDEFS)
CFLAGS= -O3 -msse3 -malign-double $(INCLUDE_DIRS) $(CDEFS)
CFLAGS2= -O3 -msse3 -malign-double -fopenmp $(INCLUDE_DIRS) $(CDEFS)
LIBS= -lpthread

PRODUCT=pinum

HFILES= 
CFILES= pinum.c

SRCS= ${HFILES} ${CFILES}
OBJS= ${CFILES:.c=.o}

all:	${PRODUCT}

clean:
	-rm -f *.o *.NEW *~
	-rm -f ${PRODUCT} ${DERIVED} ${GARBAGE}

pinum:	pinum.o
	$(CC) $(LDFLAGS) $(CFLAGS2) -o $@ pinum.o $(LIBS)

depend:

.c.o:
	$(CC) $(CFLAGS) -c $<
