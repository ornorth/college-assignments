//https://www.codewithc.com/c-program-for-regula-falsi-method/
//
#include<stdio.h>
#include<math.h>
#include<time.h>

double f(double x)
{
    //return cos(x) - x*exp(x);                     //example from source code
    //return (-(x*x*x) + 9.7*(x*x) -1.3*x -105.7);  //problem 1
    //return -1.5*x + 2.5 + sin(x*x);               //problem 2a (f(x))
    return cos(x*x);                              //problem 2a (g(x))
    //return cos(x*x) + 1.5*x - 2.5 - sin(x*x);       //problem 2b (intersection)
}

void regula (double *x, double x0, double x1, double fx0, double fx1, int *itr)
{
    *x = x0 - ((x1 - x0) / (fx1 - fx0))*fx0;
    ++(*itr);
    //printf("Iteration no. %3d X = %7.5f \n", *itr, *x);
}

int main(void)
{
    int itr=0, maxmitr, rc;
    double x0,x1,x2,x3,allerr, time_elapsed;
    struct timespec start_time, end_time;
    printf("\nEnter x0, x1, allowed error and maximum iterations:\n");
    rc = scanf("%lf %lf %lf %d", &x0, &x1, &allerr, &maxmitr);
    //get start_time
    clock_gettime(CLOCK_MONOTONIC, &start_time);

    regula (&x2, x0, x1, f(x0), f(x1), &itr);
    do
    {
        if (f(x0)*f(x2) < 0)
            x1=x2;
        else
            x0=x2;
        regula (&x3, x0, x1, f(x0), f(x1), &itr);
        if (fabs(x3-x2) < allerr)
        {
            clock_gettime(CLOCK_MONOTONIC, &end_time);
            time_elapsed = ((double)end_time.tv_sec + (double)end_time.tv_nsec / 1000000000.0) - ((double)start_time.tv_sec + (double)start_time.tv_nsec / 1000000000.0);
            printf("Time elapsed: %e seconds\n After %d iterations, root = %6.4f\n", time_elapsed, itr, x3);
            return 0;
        }
        x2=x3;
    }
    while (itr<maxmitr);

    clock_gettime(CLOCK_MONOTONIC, &end_time);
    time_elapsed = ((double)end_time.tv_sec + (double)end_time.tv_nsec / 1000000000.0) - ((double)start_time.tv_sec + (double)start_time.tv_nsec / 1000000000.0);
    printf("Time taken: %e seconds\n Solution was not found or system did not converge\n", time_elapsed);
    return 1;
}
