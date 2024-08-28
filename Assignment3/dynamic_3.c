#include <omp.h>
#include <stdio.h>
#include <stdlib.h>
#define N 200
int main()
{
    int *a = (int *)malloc(sizeof(int) * N);
    int *c = (int *)malloc(sizeof(int) * N);
    int b = 10;
    omp_set_num_threads(6);
    for (int i = 0; i < N; i++)
    {
        a[i] = 0;
    }
    double itime, ftime, exec_time;
    itime = omp_get_wtime();
#pragma omp parallel for schedule(dynamic, 8)
    for (int i = 0; i < N; i++)
    {
        c[i] = a[i] + b;
    }
    ftime = omp_get_wtime();
    exec_time = ftime - itime;
    printf("\n\nTime taken is %f\n", exec_time);
}