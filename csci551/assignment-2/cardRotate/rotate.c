/*
 * File: rotate.c
 * Author: Owen North
 *
 * Code taken from:
 *  matrotate.c (rotate a matrix)
 *  sharpen.c (read and write a .ppm file)
 */

#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>
#include <time.h>
#include <omp.h>


#define numCards (52)
#define IMG_WIDTH (690)
#define IMG_HEIGHT (920)
#define DIM (IMG_WIDTH > IMG_HEIGHT ? IMG_WIDTH : IMG_HEIGHT)

typedef unsigned char UINT8;

UINT8 P[DIM][DIM];
UINT8 convP[DIM][DIM];

char cardNames[numCards][30] = {
    "/tmp/cards_3x4_pgm/AC.pgm",  "/tmp/cards_3x4_pgm/AD.pgm",  "/tmp/cards_3x4_pgm/AH.pgm",  "/tmp/cards_3x4_pgm/AS.pgm",
    "/tmp/cards_3x4_pgm/2C.pgm",  "/tmp/cards_3x4_pgm/2D.pgm",  "/tmp/cards_3x4_pgm/2H.pgm",  "/tmp/cards_3x4_pgm/2S.pgm",
    "/tmp/cards_3x4_pgm/3C.pgm",  "/tmp/cards_3x4_pgm/3D.pgm",  "/tmp/cards_3x4_pgm/3H.pgm",  "/tmp/cards_3x4_pgm/3S.pgm",
    "/tmp/cards_3x4_pgm/4C.pgm",  "/tmp/cards_3x4_pgm/4D.pgm",  "/tmp/cards_3x4_pgm/4H.pgm",  "/tmp/cards_3x4_pgm/4S.pgm",
    "/tmp/cards_3x4_pgm/5C.pgm",  "/tmp/cards_3x4_pgm/5D.pgm",  "/tmp/cards_3x4_pgm/5H.pgm",  "/tmp/cards_3x4_pgm/5S.pgm",
    "/tmp/cards_3x4_pgm/6C.pgm",  "/tmp/cards_3x4_pgm/6D.pgm",  "/tmp/cards_3x4_pgm/6H.pgm",  "/tmp/cards_3x4_pgm/6S.pgm",
    "/tmp/cards_3x4_pgm/7C.pgm",  "/tmp/cards_3x4_pgm/7D.pgm",  "/tmp/cards_3x4_pgm/7H.pgm",  "/tmp/cards_3x4_pgm/7S.pgm",
    "/tmp/cards_3x4_pgm/8C.pgm",  "/tmp/cards_3x4_pgm/8D.pgm",  "/tmp/cards_3x4_pgm/8H.pgm",  "/tmp/cards_3x4_pgm/8S.pgm",
    "/tmp/cards_3x4_pgm/9C.pgm",  "/tmp/cards_3x4_pgm/9D.pgm",  "/tmp/cards_3x4_pgm/9H.pgm",  "/tmp/cards_3x4_pgm/9S.pgm",
    "/tmp/cards_3x4_pgm/10C.pgm", "/tmp/cards_3x4_pgm/10D.pgm", "/tmp/cards_3x4_pgm/10H.pgm", "/tmp/cards_3x4_pgm/10S.pgm",
    "/tmp/cards_3x4_pgm/JC.pgm",  "/tmp/cards_3x4_pgm/JD.pgm",  "/tmp/cards_3x4_pgm/JH.pgm",  "/tmp/cards_3x4_pgm/JS.pgm",
    "/tmp/cards_3x4_pgm/QC.pgm",  "/tmp/cards_3x4_pgm/QD.pgm",  "/tmp/cards_3x4_pgm/QH.pgm",  "/tmp/cards_3x4_pgm/QS.pgm",
    "/tmp/cards_3x4_pgm/KC.pgm",  "/tmp/cards_3x4_pgm/KD.pgm",  "/tmp/cards_3x4_pgm/KH.pgm",  "/tmp/cards_3x4_pgm/KS.pgm"
};

char rCardNames[numCards][30] = {
    "/tmp/cards_rotated/AC.pgm",  "/tmp/cards_rotated/AD.pgm",  "/tmp/cards_rotated/AH.pgm",  "/tmp/cards_rotated/AS.pgm",
    "/tmp/cards_rotated/2C.pgm",  "/tmp/cards_rotated/2D.pgm",  "/tmp/cards_rotated/2H.pgm",  "/tmp/cards_rotated/2S.pgm",
    "/tmp/cards_rotated/3C.pgm",  "/tmp/cards_rotated/3D.pgm",  "/tmp/cards_rotated/3H.pgm",  "/tmp/cards_rotated/3S.pgm",
    "/tmp/cards_rotated/4C.pgm",  "/tmp/cards_rotated/4D.pgm",  "/tmp/cards_rotated/4H.pgm",  "/tmp/cards_rotated/4S.pgm",
    "/tmp/cards_rotated/5C.pgm",  "/tmp/cards_rotated/5D.pgm",  "/tmp/cards_rotated/5H.pgm",  "/tmp/cards_rotated/5S.pgm",
    "/tmp/cards_rotated/6C.pgm",  "/tmp/cards_rotated/6D.pgm",  "/tmp/cards_rotated/6H.pgm",  "/tmp/cards_rotated/6S.pgm",
    "/tmp/cards_rotated/7C.pgm",  "/tmp/cards_rotated/7D.pgm",  "/tmp/cards_rotated/7H.pgm",  "/tmp/cards_rotated/7S.pgm",
    "/tmp/cards_rotated/8C.pgm",  "/tmp/cards_rotated/8D.pgm",  "/tmp/cards_rotated/8H.pgm",  "/tmp/cards_rotated/8S.pgm",
    "/tmp/cards_rotated/9C.pgm",  "/tmp/cards_rotated/9D.pgm",  "/tmp/cards_rotated/9H.pgm",  "/tmp/cards_rotated/9S.pgm",
    "/tmp/cards_rotated/10C.pgm", "/tmp/cards_rotated/10D.pgm", "/tmp/cards_rotated/10H.pgm", "/tmp/cards_rotated/10S.pgm",
    "/tmp/cards_rotated/JC.pgm",  "/tmp/cards_rotated/JD.pgm",  "/tmp/cards_rotated/JH.pgm",  "/tmp/cards_rotated/JS.pgm",
    "/tmp/cards_rotated/QC.pgm",  "/tmp/cards_rotated/QD.pgm",  "/tmp/cards_rotated/QH.pgm",  "/tmp/cards_rotated/QS.pgm",
    "/tmp/cards_rotated/KC.pgm",  "/tmp/cards_rotated/KD.pgm",  "/tmp/cards_rotated/KH.pgm",  "/tmp/cards_rotated/KS.pgm"
};

void zeroMats()
{
    int i, j;
    for (i = 0; i < DIM; i++)
    {
        for (j = 0; j < DIM; j++)
        {
            P[i][j]     = 0;
            convP[i][j] = 0;
        }
    }
}
void rotateLeft()
{
    //Transpose first
    int i, j;
    for (i = 0; i < DIM; i++)
    {
        for (j = 0; j < DIM; j++)
        {
            convP[j][i] = P[i][j];
        }
    }

    //Then rotate left
    for (i = 0; i < DIM; i++)
    {
        for (j = 0; j < DIM; j++)
        {
            convP[i][j] = P[DIM-1-i][j];
        }
    }
}
void rotateRight()
{
    //Transpose first
    int i, j;
    for (i = 0; i < DIM; i++)
    {
        for (j = 0; j < DIM; j++)
        {
            convP[j][i] = P[i][j];
        }
    }

    //Then rotate right
    for (i = 0; i < DIM; i++)
    {
        for (j = 0; j < DIM; j++)
        {
            convP[i][j] = P[i][DIM-1-j];
        }
    }
}

int main()
{
    struct timespec start, end;
    clock_gettime(CLOCK_MONOTONIC, &start);
    
    //Create directory for rotated cards
    struct stat st = {0};
    if (stat("/tmp/cards_rotated", &st) == -1)
    {
        mkdir("/tmp/cards_rotated", 0700);
    }

    int fdin, fdout, curCard, bytesRead=0, bytesWritten=0, bytesLeft, rc, i, pixel, readcnt=0, writecnt=0;
    UINT8 header[40];

    for (curCard = 0; curCard < numCards; curCard++)
    {
        zeroMats();

        //Open I/O files
        if ((fdin = open(cardNames[curCard], O_RDONLY, 0644)) < 0)
        {
            printf("Error opening %s\n", cardNames[0]);
        }

        if ((fdout = open(rCardNames[curCard], (O_RDWR | O_CREAT), 0644)) < 0)
        {
            printf("Error opening %s\n", rCardNames[0]);
        }

        //Read in header
        bytesLeft = 38;
        bytesLeft = read(fdin, (void *)header, bytesLeft);
        printf("header = %s\n", header);
        //header[26] = '9';
        //header[27] = '2';

        //Read in image
        bytesRead = 0;
        printf("START: read %d, bytesRead=%d, bytesLeft=%d\n", readcnt, bytesRead, bytesLeft);
        for (int i = 0; i < IMG_HEIGHT; i++)
        {
            for (int j = 0; j < IMG_WIDTH; j++)
            {
                bytesRead = read(fdin, (void *)&P[i][j], 1);
                bytesRead++;
            }
        }
        close(fdin);

        printf("END: read %d, bytesRead=%d, bytesLeft=%d\n", readcnt, bytesRead, bytesLeft);

        //Rotate the image
        /*if (curCard % 4 == 0 | curCard % 4 == 3)
        {
            printf("Rotating %s right\n", cardNames[curCard]);
            rotateRight();
        }
        else
        {
            printf("Rotating %s left\n", cardNames[curCard]);
            rotateLeft();
        }*/

        //Write header to output
        bytesLeft = 38;
        bytesWritten = write(fdout, (void *)header, bytesLeft);
        
        //Write image to output
        bytesWritten = 0;
        printf("START: write %d, bytesWritten=%d, bytesLeft=%d\n", writecnt, bytesWritten, bytesLeft);
        for (int i = 0; i < DIM; i++)
        {
            for (int j = 0; j < DIM; j++)
            {
                bytesWritten = write(fdout, (void *)&convP[i][j], 1);
                bytesWritten++;
            }
        }
        printf("END: write %d, bytesWritten=%d, bytesLeft=%d\n", writecnt, bytesWritten, bytesLeft);
        close(fdout);
    }

    clock_gettime(CLOCK_MONOTONIC, &end);
    double time = ((double)end.tv_sec + (double)end.tv_nsec / 1000000000.0) - ((double)start.tv_sec + (double)start.tv_nsec / 1000000000.0);
    printf("Elapsed time: %f seconds\n", time);

    return 0;
}
