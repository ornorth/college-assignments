#include <stdio.h>
#include <string.h>
#include <mpi.h>
#include <math.h>
#include <unistd.h>

const int MAX_STRING = 100;

#define A 0
#define B 3.14159265

double f(double x)
{
    return sin(x);
}


int main(int argc, char* argv[])
{
        int comm_sz, my_rank;

        MPI_Init(NULL, NULL);
        MPI_Comm_size(MPI_COMM_WORLD, &comm_sz);
        MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);

        //get step count from input, broadcast to all nodes
        int num_steps;
        if (my_rank == 0)
        {
            if (argc < 2)
            {
                printf("Usage: mpirun <...> ./mpi_riemann <num_steps>\n");
                printf("Using default step count on 10000\n");
                num_steps = 10000;
            }
            else
            {
                sscanf(argv[1], "%d", &num_steps);
                printf("Using step count of %d\n", num_steps);
            }
        }
        MPI_Bcast(&num_steps, 1, MPI_INT, 0, MPI_COMM_WORLD);

        //determine local parameters
        double local_A = ((B-A) / comm_sz) * my_rank;
        double local_B = ((B-A) / comm_sz) * (my_rank+1);
        double step_size = (double)(B-A) / num_steps;
        double sum = 0;

        //left sum
        for (double i = local_A; i < local_B; i += step_size)
        {
            sum += f(i)*step_size;
        }

        //send results to process 0
        if (my_rank != 0)
        {
            MPI_Send(&sum, 1, MPI_DOUBLE, 0, 0, MPI_COMM_WORLD);
        }
        //sum incoming messages
        else
        {
            double recv_sum;
            printf("Process 0 has sum %lf\n", sum);
            for (int i = 1; i < comm_sz; i++)
            {
                MPI_Recv(&recv_sum, 1, MPI_DOUBLE, i, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
                printf("Process %d sent a sum of %lf\n", i, recv_sum);
                sum += recv_sum;
            }
            printf("Final sum for %d steps: %lf\n", num_steps, sum);
        }

        MPI_Finalize();
        return 0;
}

