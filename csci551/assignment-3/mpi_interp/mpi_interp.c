#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mpi.h>
#include <math.h>
#include <unistd.h>

#include "mydata.h"

//Extra prints
#define VERBOSE 1

double table_accel(int timeidx);
double faccel(double time);


int main(int argc, char* argv[])
{
        int comm_sz, my_rank;

        MPI_Init(NULL, NULL);
        MPI_Comm_size(MPI_COMM_WORLD, &comm_sz);
        MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);

        //get step count from input, broadcast to all nodes
        int steps_per_sec;
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
                sscanf(argv[1], "%d", &steps_per_sec);
                printf("Using step count of %d\n", steps_per_sec);
            }
            printf("Step size = %lf\n", 1.0/steps_per_sec);
        }
        MPI_Bcast(&steps_per_sec, 1, MPI_INT, 0, MPI_COMM_WORLD);

        //determine local parameters
        int step_count = steps_per_sec*1800;
        double local_A = (step_count / comm_sz) * my_rank;
        double local_B = (step_count / comm_sz) * (my_rank+1);
        double step_size = 1.0 / (double)steps_per_sec;
        
        //Send local params to process 0
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
                printf("Process %d running from %lf to %lf\n", my_rank, local_A, local_B);
                double recv_A, recv_B;
                for (int i = 1; i < comm_sz; i++)
                {
                    MPI_Recv(&recv_A, 1, MPI_DOUBLE, i, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
                    MPI_Recv(&recv_B, 1, MPI_DOUBLE, i, 1, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
                    printf("Process %d running from %lf to %lf\n", i, recv_A, recv_B);
                }
            }
        }

        double cur_vel = 0;
        double max = faccel(0.0 + (step_size*local_A)) * step_size;
        double time;

        //left sum
        for (int i = local_A; i < local_B; i++)
        {
            time = 0.0 + (step_size*(double)i);
            cur_vel += faccel(time)*step_size;
            max = fmax(max, cur_vel);
        }

        //grab initial velocity from preceding process
        MPI_Barrier(MPI_COMM_WORLD);
        if (my_rank == 0 && VERBOSE)
        {
            printf("First loop finished (initial velocities attained), starting second\n");
        }
        double init_vel;
        if (my_rank != 0)
        {
            MPI_Recv(&init_vel, 1, MPI_DOUBLE, my_rank-1, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
            max += init_vel;
            cur_vel += init_vel;
        }
        if (my_rank != comm_sz - 1)
        {
            MPI_Send(&cur_vel, 1, MPI_DOUBLE, my_rank+1, 0, MPI_COMM_WORLD);
        }

        //sum again cause im dumb
        double cur_pos = 0;
        cur_vel = init_vel;
        for (int i = local_A; i < local_B; i++)
        {
            time = 0.0 + (step_size*(double)i);
            cur_vel += faccel(time)*step_size;
            cur_pos += cur_vel*step_size;
        }


        //send results to process 0
        if (my_rank != 0)
        {
            MPI_Send(&max, 1, MPI_DOUBLE, 0, 0, MPI_COMM_WORLD);
            MPI_Send(&cur_pos, 1, MPI_DOUBLE, 0, 0, MPI_COMM_WORLD);
        }
        //sum incoming messages
        else
        {
            double recv_max, recv_pos;
            //printf("Process 0 has max %lf\n", max);
            for (int i = 1; i < comm_sz; i++)
            {
                MPI_Recv(&recv_max, 1, MPI_DOUBLE, i, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
                //printf("Process %d sent a max of %lf\n", i, recv_max);
                max = fmax(max, recv_max);

                MPI_Recv(&recv_pos, 1, MPI_DOUBLE, i, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
                //printf("Process %d sent a position of %lf\n", i, recv_pos/1000);
                cur_pos += recv_pos;
            }
            printf("Overall max for %d steps: %lf\nOverall position: %lf\n", step_count, max, cur_pos/1000);
        }

        MPI_Finalize();
        return 0;
}


double table_accel(int timeidx)
{
    long unsigned int tsize = sizeof(DefaultProfile) / sizeof(double);

    // Check array bounds for look-up table
    if(timeidx > tsize)
    {
        printf("timeidx=%d exceeds table size = %lu and range %d to %lu\n", timeidx, tsize, 0, tsize-1);
        exit(-1);
    }

    return DefaultProfile[timeidx];
}

double faccel(double time)
{
    int timeidx = (int)time;
    int timeidx_next = ((int)time) + 1;
    double delta_t = time - (double)((int)time);
    return table_accel(timeidx) + ( (table_accel(timeidx_next) - table_accel(timeidx)) * delta_t);
}
