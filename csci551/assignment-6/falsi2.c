//https://www.codewithc.com/c-program-for-regula-falsi-method/
//
#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<time.h>

struct Node
{
    double val;
    struct Node *next;
};
struct Node *root = NULL;
int nodesContain(double val, double allerr)
{
    struct Node* iter = root;
    double diff;
    while (iter)
    {
        diff = iter->val - val;
        if (diff < 0) diff *= -1.0;
        if (diff < allerr) return 1;
        iter = iter->next;
    }
    return 0;
}
void addVal(double val, double allerr, double lower, double upper)
{
    if (val < lower || val > upper) return;
    if (nodesContain(val, allerr)) return;
    struct Node *prev, *iter = root;
    while (iter && iter->val < val)
    {
        prev = iter;
        iter = iter->next;
    }
    if (iter == root)
    {
        root = (struct Node*) malloc(sizeof(struct Node));
        root->val = val;
        root->next = iter;
    }
    else
    {
        struct Node *tmp = (struct Node*) malloc(sizeof(struct Node));
        tmp->val = val;
        prev->next = tmp;
        tmp->next = iter;
    }
}
void printNodes()
{
    struct Node *iter = root;
    int ctr = 0;
    while (iter)
    {
        printf("| %6.4f ", iter->val);
        iter = iter->next;
        ctr++;
        if (ctr % 5 == 0) printf("|\n");
    }
    printf("\n");
}


double f(double x)
{
    //return cos(x) - x*exp(x);                     //example from source code
    //return (-(x*x*x) + 9.7*(x*x) -1.3*x -105.7);  //problem 1
    //return -1.5*x + 2.5 + sin(x*x);                 //problem 2a (f(x))
    return cos(x*x);                                //problem 2a (g(x))
    //return cos(x*x) + 1.5*x - 2.5 - sin(x*x);     //problem 2b (intersection)
}

void regula (double *x, double x0, double x1, double fx0, double fx1, int *itr)
{
    *x = x0 - ((x1 - x0) / (fx1 - fx0))*fx0;
    ++(*itr);
    //printf("Iteration no. %3d X = %7.5f \n", *itr, *x);
}

int main(void)
{
    int itr, maxmitr, rc;
    double xitr,x0,x1,x2,x3,allerr, time_elapsed, lower, upper, interval;
    struct timespec start_time, end_time;
    printf("Enter the lower bound, upper bound, interval, allowed error and maximum iterations:\n");
    rc = scanf("%lf %lf %lf %lf %d", &lower, &upper, &interval, &allerr, &maxmitr);
    //get start_time
    clock_gettime(CLOCK_MONOTONIC, &start_time);

    for (xitr = lower; xitr < upper; xitr += interval)
    {
        x0 = xitr;
        x1 = xitr + interval;
        itr = 0;
        //printf("x0=%6.4f, x1=%6.4f\n", x0, x1);
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
                addVal(x3, allerr, lower, upper);
                break;
            }
            x2=x3;
        }
        while (itr<maxmitr);
    }

    clock_gettime(CLOCK_MONOTONIC, &end_time);
    time_elapsed = ((double)end_time.tv_sec + (double)end_time.tv_nsec / 1000000000.0) - ((double)start_time.tv_sec + (double)start_time.tv_nsec / 1000000000.0);
    printNodes();
    printf("Time taken: %e seconds\n", time_elapsed);
    return 0;
}
