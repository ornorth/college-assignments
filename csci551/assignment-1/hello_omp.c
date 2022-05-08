#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

void Hello_thread(void);

int main(int argc, char *argv[])
{
    int thread_count=4; // good default for ecc-linux

    if(argc < 2)
        printf("usage: hello_omp <number threads>\n");
    else
    {
        sscanf(argv[1], "%d", &thread_count);
    }

    printf("Main program thread will now create all threads requested ...\n");

    for (int i = 0; i < 4; i++)
    {
#pragma omp parallel num_threads(thread_count)
    //for (int i = 0; i < 4; i++) Hello_thread();
    Hello_thread();
    }
    printf("All threads now done, main program proceeding to exit\n");

    return 0;
}

void Hello_thread(void)
{
    int my_rank = omp_get_thread_num();
    int thread_count = omp_get_num_threads();

    printf("Hello from OMP thread %d of %d\n", my_rank, thread_count);
}
