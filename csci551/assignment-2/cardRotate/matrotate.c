#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>


#define DIMX (8)
#define DIMY (12)

#define max(X, Y) ((X) > (Y) ? (X) : (Y))

unsigned int P[max(DIMX, DIMY)][max(DIMX, DIMY)];
unsigned int TP[max(DIMX, DIMY)][max(DIMX, DIMY)];
unsigned int RRP[max(DIMX, DIMY)][max(DIMX, DIMY)];
unsigned int RLP[max(DIMX, DIMY)][max(DIMX, DIMY)];

void zeroIntMat(unsigned int Mat[][max(DIMX, DIMY)]);
void fillIntMat(unsigned int Mat[][max(DIMX, DIMY)]);
void printIntMat(unsigned int Mat[][max(DIMX, DIMY)]);
void transposeIntMat(unsigned int Mat[][max(DIMX, DIMY)], unsigned int TMat[][max(DIMX, DIMY)]);
void swapColIntMat(unsigned int Mat[][max(DIMX, DIMY)], unsigned int TMat[][max(DIMX, DIMY)]);
void swapRowIntMat(unsigned int Mat[][max(DIMX, DIMY)], unsigned int TMat[][max(DIMX, DIMY)]);


int main(int argc, char *argv[])
{
    int fdin, fdout;

    if(argc < 3)
    {
        printf("Example Use: matrotate <inputfile> <outputfile>\n");
    }

    else
    {
        //open binary file to read in data instead of using test pattern data
        if((fdin = open(argv[1], O_RDONLY, 0644)) < 0)
        {
            printf("Error opening %s\n", argv[1]);
        }

        //open binary file to write out data
        if((fdout = open(argv[2], O_WRONLY, 0644)) < 0)
        {
            printf("Error opening %s\n", argv[2]);
        }
    }

    //read in the PGM data here

    //if the PGM is for a club or spade, note that it must be rotated RIGHT
    //if the PGM is for a heart or diamond,  note that it must be rotated LEFT

    close(fdin);


    //initialize array with test data
    fillIntMat(P);

    printf("Matrix P=");printIntMat(P);

    transposeIntMat(P, TP);
    printf("Transpose (rotation about left-to-right diagonal) of P=");printIntMat(TP);
    printf("Transpose of P=");printIntMat(TP);

    swapColIntMat(TP, RRP);
    swapRowIntMat(TP, RLP);

    printf("P=");printIntMat(P);
    printf("Rotate Right (column rotate after TP), P=");printIntMat(RRP);
    printf("Rotate Right P=");printIntMat(RRP);
    printf("Rotate Left (rown rotate after TP), P=");printIntMat(RLP);
    printf("Rotate Left P=");printIntMat(RLP);


    //write out the modified PGM data here

    close(fdout);
}


void swapRowIntMat(unsigned int Mat[][max(DIMX, DIMY)], unsigned int TMat[][max(DIMX, DIMY)])
{
    int idx, jdx;

    for(idx=0; idx<max(DIMX, DIMY); idx++)       
        for(jdx=0; jdx<max(DIMX, DIMY); jdx++)  
        {
            //copy into TMat and swap row values         
            TMat[idx][jdx]=Mat[max(DIMX, DIMY)-1-idx][jdx];
        }
}


void swapColIntMat(unsigned int Mat[][max(DIMX, DIMY)], unsigned int TMat[][max(DIMX, DIMY)])
{
    int idx, jdx;

    for(idx=0; idx<max(DIMX, DIMY); idx++)       
        for(jdx=0; jdx<max(DIMX, DIMY); jdx++)  
        {
            //copy into TMat and swap column values         
            TMat[idx][jdx]=Mat[idx][max(DIMX, DIMY)-1-jdx];
        }
}


void fillIntMat(unsigned int Mat[][max(DIMX, DIMY)])
{
    int cnt, idx, jdx;

    for(idx=0; idx<max(DIMX, DIMY); idx++)       
        for(jdx=0; jdx<max(DIMX, DIMY); jdx++)
        {
            cnt = rand() % 10;
            Mat[idx][jdx]=(unsigned int)cnt;
        }
}


void zeroIntMat(unsigned int Mat[][max(DIMX, DIMY)])
{
    int idx, jdx;

    for(idx=0; idx<max(DIMX, DIMY); idx++)       
        for(jdx=0; jdx<max(DIMX, DIMY); jdx++)
        {
            Mat[idx][jdx]=0;
        }
}


void transposeIntMat(unsigned int Mat[][max(DIMX, DIMY)], unsigned int TMat[][max(DIMX, DIMY)])
{
    int idx, jdx;

    for(idx=0; idx<max(DIMX, DIMY); idx++)
        for(jdx=0; jdx<max(DIMX, DIMY); jdx++)
        {
            //transpose row as column
            TMat[jdx][idx]=Mat[idx][jdx];
        }
}


void printIntMat(unsigned int Mat[][max(DIMX,DIMY)])
{
    int idx, jdx;

    for(idx = 0; idx < max(DIMX,DIMY); idx++)
    {
        printf("\n");
        for(jdx=0; jdx < max(DIMX,DIMY); jdx++)
            printf("%d ", Mat[idx][jdx]);
    }
    printf("\n\n");;
}

