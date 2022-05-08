/*  omp_sumdigits.c
 *
 *  Author: Owen North
 *  Date Created:  2022/2/8
 *  Last Modified: 2022/2/8
 *
 *  Computes sum[1...1,000,000] in segments of 100,000 using a threaded approach
 *
 *  Inspiration for the segmented approach to sum calculation from Dr. Siewert's sumdigits.c
 *  Syntax for openmp gleaned from Siewert's hello_omp.c and omp_dct2.c and associated Makefiles
 */
#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

//hard coding values - could be made dynamic w/o too much difficulty
#define N 1000000
#define INTERVAL 100000
#define THREAD_COUNT 10

//returns sum of the "n-hundred thousandth" range (0 = 0-100.000, 1 = 100.001-200.000, etc.)
long int computeRange(int idx)
{
    //determine start and end points
    int start = (idx*INTERVAL)+1;
    int end = (idx+1)*INTERVAL;
    long int sum = 0; //running total

    for (int i = start; i <= end; i++)
    {
        sum += i;
    }
    printf("Range %d: calculated %ld\n", idx, sum);
    return sum;
}


int main(int argc, char *argv[])
{
    long int sum = 0;

//split loop into threads - 1 thread per iteration
#pragma omp parallel for num_threads(THREAD_COUNT)
    for (int i = 0; i < THREAD_COUNT; i++)
    {
        //calculate sum of current range and increment global sum accordingly
        sum += computeRange(i);
    };
    
    //display threaded sum in comparison to shortcut
    printf("Sum calculated by threads: %ld\nSum calculated by n(n+1)/2: %ld\n", sum, (long int)N*(N+1)/2);
    return 0;
}
