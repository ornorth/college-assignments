INCLUDE_DIRS = 
LIB_DIRS = 
CC = gcc

CDEFS=
CFLAGS= -g -O3
LIBS= -lm

PRODUCT= csvtostatic

HFILES= 
CFILES= csvtostatic.c

SRCS= ${HFILES} ${CFILES}
OBJS= ${CFILES:.c=.o}

all:	${PRODUCT}

clean:
	-rm -f *.o *.NEW *~
	-rm -f ${PRODUCT} ${DERIVED} ${GARBAGE}

csvtostatic: csvtostatic.c
	$(CC) $(CFLAGS) -o $@ $@.c $(LIBS)
