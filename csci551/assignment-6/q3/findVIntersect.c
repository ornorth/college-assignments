//Code adapted from https://www.ecst.csuchico.edu/~sbsiewert/csci551/code/functiongen/timeinterp.c
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

#include "aLin.h"
#include "aNonlin.h"

//default steps per second
#define STEPS_PER_SEC 1

//used by table_accel to decide which acceleration profile to use
enum func{ linear, nonLinear, intersect }; 

//table_accel used by faccel, returns value from specified acceleration profile
double table_accel(int timeidx, enum func profile);

//estimates value between points in the table using linear interpolation
double faccel(double time, enum func profile);

//determines equality of two floating point values within a specified tolerance
int isEqual(double a, double b, double tolerance);

///////////////////////////////////////////// MAIN ////////////////////////////////////////////////
int main(int argc, char *argv[])
{
    int idx;
    int steps_per_sec=STEPS_PER_SEC;
    double time, dt, precision;


    printf("argc=%d, argv[0]=%s\n", argc, argv[0]);

    if(argc == 2)
    {
        sscanf(argv[1], "%d", &steps_per_sec);
        printf("Will use %d steps per sec\n", steps_per_sec);
    }
    else if (argc == 3)
    {
        sscanf(argv[1], "%d", &steps_per_sec);
        printf("Will use %d steps per sec\n", steps_per_sec);
        sscanf(argv[2], "%lf", &precision);
        printf("Will use precision of %lf\n", precision);
    }
    else
    {
        printf("Use: trainprofile [steps_per_sec] [precision]\n");
        printf("Will use default time profile and precision of 0.1\n");
    }

    dt = 1.0 / steps_per_sec;

    printf("Step size of %lf\n", dt);

    // Verify the static initializer or loaded CSV array for size and values
    //
    // And use it to generate values between 1 second given values.
    //
    printf("Number of values in profile = %lu for 1801 expected\n", sizeof(aLin)/sizeof(double));

    double pLinFinal=0, pNonlinFinal=0, vLinFinal=0, vNonlinFinal=0;
    for(idx=0; idx <= (steps_per_sec*1800); idx++)
    {
        // time you would use in your integrator and faccel(time) is the fuction to integrate
        time = 0.0 + (dt*(double)idx);

        vLinFinal += faccel(time, linear) * dt;
        pLinFinal += vLinFinal * dt;

        vNonlinFinal += faccel(time, nonLinear) * dt;
        pNonlinFinal += vNonlinFinal * dt;

        if (isEqual(pLinFinal, pNonlinFinal, precision) && time >= 600.0  && time <= 800.0)
        {
            printf("EQUALITY: time=%lf, linear=%lf, nonlinear=%lf\n", time, vLinFinal, vNonlinFinal);
        }
    }
    printf("Linear: velocity=%lf, position=%lf\n", vLinFinal, pLinFinal);
    printf("NonLinear: velocity=%lf, position=%lf\n", vNonlinFinal, pNonlinFinal);
    //printf("%d : %d : %d\n", linear, nonLinear, intersect); /* 0 : 1 : 2 */
    return 0;
}
////////////////////////////////////////////////////////////////////////////////////////////////////

// Simple look-up in accleration profile array
//
// Added array bounds check for known size of train arrays
//
double table_accel(int timeidx, enum func profile)
{
    //assume both arrays are the same length
    long unsigned int tsize = sizeof(aLin) / sizeof(double);

    // Check array bounds for look-up table
    if(timeidx > tsize)
    {
        printf("timeidx=%d exceeds table size = %lu and range %d to %lu\n", timeidx, tsize, 0, tsize-1);
        exit(-1);
    }

    if (profile == linear)
    {
        return aLin[timeidx];
    }
    else if (profile == nonLinear)
    {
        return aNonlin[timeidx];
    }
    return (aLin[timeidx] - aNonlin[timeidx]);
}


// Simple linear interpolation example for table_accel(t) for any floating point t value
// for a table of accelerations that are 1 second apart in time, evenly spaced in time.
//
// accel[timeidx] <= accel[time] < accel[timeidx_next]
//
//
double faccel(double time, enum func profile)
{
    // The timeidx is an index into the known acceleration profile at a time <= time of interest passed in
    //
    // Note that conversion to integer truncates double to next lowest integer value or floor(time)
    //
    int timeidx = (int)time;

    // The timeidx_next is an index into the known acceleration profile at a time > time of interest passed in
    //
    // Note that the conversion to integer truncates double and the +1 is added for ceiling(time)
    //
    int timeidx_next = ((int)time)+1;

    // delta_t = time of interest - time at known value < time
    //
    // For more general case
    // double delta_t = (time - (double)((int)time)) / ((double)(timeidx_next - timeidx);
    //
    // If time in table is always 1 second apart, then we can simplify since (timeidx_next - timeidx) = 1.0 by definition here
    double delta_t = time - (double)((int)time);

    return ( 
               // The accel[time] is a linear value between accel[timeidx] and accel[timeidx_next]
               // 
               // The accel[time] is a value that can be determined by the slope of the interval and accel[timedix] 
               //
               // I.e. accel[time] = accel[timeidx] + ( (accel[timeidx_next] - accel[timeidx]) / ((double)(timeidx_next - timeidx)) ) * delta_t
               //
               //      ((double)(timeidx_next - timeidx)) = 1.0
               // 
               //      accel[time] = accel[timeidx] + (accel[timeidx_next] - accel[timeidx]) * delta_t
               //
               table_accel(timeidx, profile) + ( (table_accel(timeidx_next, profile) - table_accel(timeidx, profile)) * delta_t)
           );
}

int isEqual(double a, double b, double tolerance)
{
    double diff = a - b;
    if (diff < 0) diff *= -1.0;
    return (diff < tolerance);
}
