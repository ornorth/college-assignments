#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>
#include <sched.h>

//changing this macro will update all relevant areas so only 8 threads are created
#define NUM_THREADS 8

typedef struct
{
    int threadIdx;
} threadParams_t;


// POSIX thread declarations and scheduling attributes
//
pthread_t threads[NUM_THREADS];
threadParams_t threadParams[NUM_THREADS];

//global variable for threads
//could also be added to struct, but this is less overhead
int n;

void *counterThread(void *threadp)
{
    int sum=0, i;
    threadParams_t *threadParams = (threadParams_t *)threadp;

    for(i=1; i < n+1; i++)
        sum=sum+i;

    //Special case - n = 1,000,000 and output is erroneous
    if (n == 1000000 && sum != 1784293664)
        printf("ERROR: Thread idx=%d, sum[0...%d]=%d\n", threadParams->threadIdx, n, sum);
    else
        printf("Thread idx=%d, sum[0...%d]=%d\n", threadParams->threadIdx, n, sum);
}


int main (int argc, char *argv[])
{
    //Ensure a value for n has been given, exit if not
    if (argc < 2)
    {
        printf("Usage: ./pthread <n>\n");
        exit(0);
    }

    n = atoi(argv[1]);
    int rc;
    int i;

    for(i=0; i < NUM_THREADS; i++)
    {
        threadParams[i].threadIdx=i;

        pthread_create(&threads[i],             // pointer to thread descriptor
                      (void *)0,                // use default attributes
                      counterThread,            // thread function entry point
                      (void *)&(threadParams[i])// parameters to pass in
                      );

    }

    for(i=0;i<NUM_THREADS;i++)
        pthread_join(threads[i], NULL);

    printf("TEST COMPLETE\n");
}
