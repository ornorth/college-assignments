#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mpi.h>
#include <math.h>
#include <unistd.h>

//#include "mydata.h"

#define VERBOSE 0 //extra prints - for debugging
#define T_SCALE 286.478897565412 //time scale - stretch sine curves over 1800s instead of 2*pi
#define A_SCALE 0.2365893166123 //amplitude of acceleration function

double fvel(double x);
double faccel(double x);

int main(int argc, char* argv[])
{
        int comm_sz, my_rank;

        MPI_Init(NULL, NULL);
        MPI_Comm_size(MPI_COMM_WORLD, &comm_sz);
        MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);

        //get step count from input, broadcast to all nodes
        double steps_per_sec;
        if (my_rank == 0)
        {
            if (argc < 2)
            {
                printf("Usage: mpirun <...> ./mpi_interp <steps_per_sec>\n");
                printf("Using default step frequency of 10\n");
                steps_per_sec = 10;
            }
            else
            {
                sscanf(argv[1], "%lf", &steps_per_sec);
                printf("Using step count of %lfn", steps_per_sec);
            }
            printf("Step size = %lf\n", 1.0/steps_per_sec);
        }
        MPI_Bcast(&steps_per_sec, 1, MPI_DOUBLE, 0, MPI_COMM_WORLD);

        //determine local parameters
        double step_count = steps_per_sec*1800;
        double local_A = (step_count / comm_sz) * my_rank;
        double local_B = (step_count / comm_sz) * (my_rank+1);
        double step_size = 1.0 / (double)steps_per_sec;
        
        //VERBOSE: send local params to process 0 for printing
        if (VERBOSE)
        {
            if (my_rank != 0)
            {
                //tag 0 = A
                MPI_Send(&local_A, 1, MPI_DOUBLE, 0, 0, MPI_COMM_WORLD);
                //tag 1 = B
                MPI_Send(&local_B, 1, MPI_DOUBLE, 0, 1, MPI_COMM_WORLD);
            }
            else
            {
                printf("Process %d running from %f to %f\n", my_rank, local_A, local_B);
                double recv_A, recv_B;
                for (int i = 1; i < comm_sz; i++)
                {
                    MPI_Recv(&recv_A, 1, MPI_DOUBLE, i, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
                    MPI_Recv(&recv_B, 1, MPI_DOUBLE, i, 1, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
                    printf("Process %d running from %f to %f\n", i, recv_A, recv_B);
                }
            }
        }

        double cur_pos = 0;
        double cur_vel = 0;
        double time;
        //left riemann sum using acceleration and velocity equations
        for (int i = local_A; i < local_B; i++)
        {
            time = 0.0 + (step_size*(double)i);
            cur_pos += (fvel(time) + fvel(time + step_size)) * (step_size / 2);
            cur_vel += (faccel(time) + faccel(time + step_size)) * (step_size / 2);
        }

        MPI_Barrier(MPI_COMM_WORLD);
        double final_pos, final_vel;
        MPI_Reduce(&cur_pos, &final_pos, 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);
        MPI_Reduce(&cur_vel, &final_vel, 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);

        //print final value
        if (my_rank == 0)
        {
            printf("Final position: %f: variance of %lf\n", final_pos, (double)final_pos-122000.0);
            printf("Final velocity: %f\n", final_vel);
        }
        MPI_Finalize();
        return 0;
}

//mathematical representation of acceleration function
double faccel(double x)
{
    return (sin(x / T_SCALE) * A_SCALE);
}


//mathematical representation of velocity function
double fvel(double x)
{
    //Integral of acceleration function - the '+1' starts velocity at 0 instead of -1
    return ((-1 * (cos(x / T_SCALE)) + 1) * (T_SCALE*A_SCALE));
}







