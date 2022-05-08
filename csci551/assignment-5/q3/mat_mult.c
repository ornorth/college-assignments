#include <stdio.h>
#include <stdlib.h>
#include <time.h>

//hard code test cases
int testm1[3][3] = { { 1, 2, 3, },
                     { 4, 5, 6, },
                     { 7, 8, 9, }, };

int testm2[3][3] = { { 9, 8, 7, },
                     { 6, 5, 4, },
                     { 3, 2, 1, }, };

int testv1[3] = { 11, 7, 13, };

void print_mat(int **mat, int n);
void print_vect(int *vect, int n);

int main(int argc, char *argv[])
{
    int i, j, k, n, using_default=0, verbose=0;
    int **m1, **m2, **mxm, *v1, *mxv;
    struct timespec start_time, end_time;
    double time_elapsed;

    printf("\n---Matrix Multiplier (sequential version)---\n\n");
    if (argc < 2)
    {
        printf("Usage: ./mult <n> <1=print, 0=don't print>\n");
        printf("Using default 3x3 matrices with set values\n");
        using_default = 1;
        n = 3;
    }
    else
    {
        sscanf(argv[1], "%d", &n);

        if (argc > 2)
        {
            sscanf(argv[2], "%d", &verbose);
            printf("Verbose flag set to %s\n", verbose? "True: matrices will be displayed" : "False: matrices will not be displayed");
        }
        else
        {
            printf("Verbose flag not specified, defaulting to False\n");
        }

        srand((unsigned) time(NULL));
    }

    //allocate arrays
    m1 = malloc(n * sizeof(*m1));
    m2 = malloc(n * sizeof(*m2));
    mxm = malloc(n * sizeof(*mxm));
    v1 = malloc(n * sizeof(*v1));
    mxv = malloc(n * sizeof(*mxv));
    for (i = 0; i < n; i++)
    {
        m1[i] = malloc(n * sizeof(*m1));
        m2[i] = malloc(n * sizeof(*m2));
        mxm[i] = malloc(n * sizeof(*mxm));
        v1[i] = (using_default ? testv1[i] : rand() % 10);
        mxv[i] = 0;
        for (j = 0; j < n; j++)
        {
            m1[i][j] = (using_default ? testm1[i][j] : rand() % 10);
            m2[i][j] = (using_default ? testm2[i][j] : rand() % 10);
            mxm[i][j] = 0;
        }
    }

    if (verbose || using_default)
    {
        printf("starting matrix 1\n"); print_mat(m1, n);
        printf("starting matrix 2\n"); print_mat(m2, n);
        printf("starting vector\n"); print_vect(v1, n);
    }

    //matrix * matrix
    printf("\nStarting matrix by matrix multipication...");
    clock_gettime(CLOCK_MONOTONIC, &start_time);
    for (i = 0; i < n; i++)
    {
        for (j = 0; j < n; j++)
        {
            for (k = 0; k < n; k++)
            {
                mxm[i][j] += m1[i][k] * m2[k][j];
            }
        }
    }
    clock_gettime(CLOCK_MONOTONIC, &end_time);
    time_elapsed = ((double)end_time.tv_sec + (double)end_time.tv_nsec / 1000000000.0) - ((double)start_time.tv_sec + (double)start_time.tv_nsec / 1000000000.0);
    printf("Finished\nTime=%e seconds\n\n", time_elapsed);

    //matrix * vector
    printf("Starting matrix by vector multipication...");
    clock_gettime(CLOCK_MONOTONIC, &start_time);
    for (i = 0; i < n; i++)
    {
        for (j = 0; j < n; j++)
        {
            mxv[i] += m1[i][j] * v1[j];
        }
    }
    clock_gettime(CLOCK_MONOTONIC, &end_time);
    time_elapsed = ((double)end_time.tv_sec + (double)end_time.tv_nsec / 1000000000.0) - ((double)start_time.tv_sec + (double)start_time.tv_nsec / 1000000000.0);
    printf("Finished\nTime=%e seconds\n\n", time_elapsed);

    if (verbose || using_default)
    {
        printf("resulting matrix\n"); print_mat(mxm, n);
        printf("resulting vector (multiplied by starting matrix 1)\n"); print_vect(mxv, n);
    }
    return 0;
}


void print_mat(int **mat, int n)
{
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            printf("  %d", mat[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

void print_vect(int *vect, int n)
{
    for (int i = 0; i < n; i++)
    {
        printf("  %d\n", vect[i]);
    }
    printf("\n");
}
