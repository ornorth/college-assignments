#include <stdio.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <fcntl.h>
#include <time.h>
#include <omp.h>



#define MAX (1000000000)
//#define MAX (0xFFFFFFFF)
#define HALT (1)
#define CONTINUE (0)

//for omp
#define THREAD_COUNT (8)

// Be careful sizing MAX to make sure you do not exceed available data segment
// size on your system.  Malloc might be a good alternative, but an array declaration
// was made here for simplicity.
//
// E.g. 1,000,000,000 would require a 1 gigabyte of memory for example.
//
unsigned char isprime[MAX+1];
unsigned int value[MAX+1];
void find_pi(unsigned int piofx);


void main(void)
{
    int x=10;
    struct timespec now, start;
    double fnow, fstart;

    clock_gettime(CLOCK_MONOTONIC_RAW, &start);
    fstart = (double)start.tv_sec  + (double)start.tv_nsec / 1000000000.0;
    printf("Starting pi test @ %lf\n", fstart);

    //MY STUFF
    find_pi(MAX);

    unsigned int max_prime = MAX;
    while(max_prime > 2)
    {
        if (isprime[max_prime]) break;
        max_prime--;
    }
    printf(": Max is %d:", max_prime);
    //END MY STUFF

    clock_gettime(CLOCK_MONOTONIC_RAW, &now);
    fnow = (double)now.tv_sec  + (double)now.tv_nsec / 1000000000.0;
    printf(" @ %lf sec elapsed", (fnow-fstart));
    fflush(stdout);

    printf("\n");

}

int checkTime(double fstart)
{
    struct timespec now;
    double fnow;

    clock_gettime(CLOCK_MONOTONIC_RAW, &now);
    fnow = (double)now.tv_sec  + (double)now.tv_nsec / 1000000000.0;

    if(fnow-fstart > 300.00)
        return HALT;
    else
        return CONTINUE;
}


//
// each try should run for no more than 300 seconds
//
void find_pi(unsigned int piofx)
{
    int i, j;
    unsigned int p=2, cnt=0;
    struct timespec start, now;
    double fstart=0.0, fnow=0.0;

    clock_gettime(CLOCK_MONOTONIC_RAW, &start);
    fstart = (double)start.tv_sec  + (double)start.tv_nsec / 1000000000.0;
    clock_gettime(CLOCK_MONOTONIC_RAW, &now);
    fnow = (double)now.tv_sec  + (double)now.tv_nsec / 1000000000.0;
    //printf("\nstart test for at %lf\n", fnow-fstart);


    // not prime by definition
    isprime[0]=0; value[0]=0;
    isprime[1]=0; value[1]=1;

    for(i=2; i<piofx+1; i++) { isprime[i]=1; value[i]=i; }

#pragma omp parallel for num_threads(THREAD_COUNT)
    while( (p*p) <=  piofx)
    {
        // invalidate all multiples of lowest prime so far
        for(j=2*p; j<piofx+1; j+=p)
        {
            //if(checkTime(fstart) == HALT) break;
            isprime[j]=0;
        }

        // find next lowest prime
        for(j=p+1; j<piofx+1; j++)
        {
            //if(checkTime(fstart) == HALT) break;
            if(isprime[j]) { p=j; break; } 
        }

        //if(checkTime(fstart) == HALT) break;
    }
    
    for(i=0; i<piofx+1; i++) { if(isprime[i]) { cnt++; } }

    clock_gettime(CLOCK_MONOTONIC_RAW, &now);
    fnow = (double)now.tv_sec  + (double)now.tv_nsec / 1000000000.0;
    //printf("\nstopped test for at %lf\n", fnow-fstart);

    printf("\nNumber of primes [0..%d]=%u", piofx, cnt);
}
