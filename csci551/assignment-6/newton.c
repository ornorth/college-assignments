// https://www.codewithc.com/c-program-for-newton-raphson-method/
//
#include<stdio.h>
#include<math.h>
#include<time.h>

double f(double x)
{
    //return x*log10(x) - 1.2;
    return (-(x*x*x) + 9.7*(x*x) -1.3*x -105.7);
}

double df (double x)
{
    //return log10(x) + 0.43429;
    return (-3*(x*x)+19.4*x-1.3);
}

int main(void)
{
    int itr, maxmitr, rc;
    double h, x0, x1, allerr, time_elapsed;
    struct timespec start_time, end_time;
    printf("\nEnter x0 guess to find first root, allowed error and maximum iterations\n");
    rc = scanf("%lf %lf %d", &x0, &allerr, &maxmitr);

    //get_time
    clock_gettime(CLOCK_MONOTONIC, &start_time);
    for (itr=1; itr<=maxmitr; itr++)
    {
        h=f(x0)/df(x0);
        x1=x0-h;
        //printf("Iteration: %3d, x = %9.6f\n", itr, x1);
        if (fabs(h) < allerr)
        {
            clock_gettime(CLOCK_MONOTONIC, &end_time);
            time_elapsed = ((double)end_time.tv_sec + (double)end_time.tv_nsec / 1000000000.0) - ((double)start_time.tv_sec + (double)start_time.tv_nsec / 1000000000.0);
            printf("Time taken: %e seconds\n After %3d iterations, root = %8.6f\n", time_elapsed, itr, x1);
            return 0;
        }
        x0=x1;
    }
    clock_gettime(CLOCK_MONOTONIC, &end_time);
    time_elapsed = ((double)end_time.tv_sec + (double)end_time.tv_nsec / 1000000000.0) - ((double)start_time.tv_sec + (double)start_time.tv_nsec / 1000000000.0);
    printf("Time taken: %e seconds\n The required solution does not converge or iterations are insufficient\n", time_elapsed);
    return 1;
}
