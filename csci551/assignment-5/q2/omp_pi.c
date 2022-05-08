#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

// The 2 series used for computation of pi are documented well by Wikipedia
//
// https://en.wikipedia.org/wiki/Leibniz_formula_for_%CF%80
//
// The first series is simply 1 - 1/3 + 1/5 - 1/7 + 1/9 - ... = pi/4
//
// The second series is the summation of 2 / ((4n+1)(4n+3)) for n=0 to infinity
//

int main(int argc, char** argv)
{
  int idx;
  double euler_g_sum=0.0;
  double g_sum=0.0, local_num=1.0;
  unsigned int length;
  struct timespec start_time, end_time;
  double time;

  if(argc < 2)
  {
      printf("usage: piseriesreduce <series n>\n");
      exit(-1);
  }
  else
  {
      sscanf(argv[1], "%u", &length);
  }

  printf("length=%u\n", length);

  clock_gettime(CLOCK_MONOTONIC, &start_time);
  // sum the sub-series for the rank for Leibniz's formula for pi/4
  #pragma omp parallel for num_threads(4) reduction(+: g_sum)
  for(idx = 0; idx < length; idx++)
  {
    g_sum += local_num  / ((2.0 * (double)idx) + 1.0);
    local_num = -local_num;
  }
  clock_gettime(CLOCK_MONOTONIC, &end_time);
  time = ((double)end_time.tv_sec + (double)end_time.tv_nsec / 1000000000.0) - ((double)start_time.tv_sec + (double)start_time.tv_nsec / 1000000000.0);
  printf("Madhava-Leibniz took %e seconds for %u iterations\n", time, length);

  clock_gettime(CLOCK_MONOTONIC, &start_time);
  // sum the sub-series for the rank for Euler improved convergence of the Madhava-Leibniz's formula for pi/4
  #pragma omp parallel for num_threads(4) reduction(+: euler_g_sum)
  for(idx = 0; idx < length; idx++)
  {
    euler_g_sum += 2.0 / (((4.0 * (double)idx) + 1.0) * (4.0 * (double)idx + 3.0));
  }
  clock_gettime(CLOCK_MONOTONIC, &end_time);
  time = ((double)end_time.tv_sec + (double)end_time.tv_nsec / 1000000000.0) - ((double)start_time.tv_sec + (double)start_time.tv_nsec / 1000000000.0);
  printf("Euler took %e seconds for %u iterations\n", time, length);

  printf("20 decimals of pi  =3.14159265358979323846\n");
  printf("C math library pi  =%15.14lf\n", M_PI);
  printf("Madhava-Leibniz pi =%15.14lf, ppb error=%15.14lf\n", (4.0*g_sum), 1000000000.0*(M_PI - (4.0*g_sum)));
  printf("Euler modified pi  =%15.14lf, ppb error=%15.14lf\n", (4.0*euler_g_sum), 1000000000.0*(M_PI - (4.0*euler_g_sum)));

  return 0;
}
