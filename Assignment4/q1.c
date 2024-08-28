#include <omp.h>
#include <stdio.h>
#include <stdlib.h>

int fibonacci(int n)
{
    int i, j;
    if (n < 2)
        return n;
    else
    {
#pragma omp task shared(i)
        i = fibonacci(n - 1);
#pragma omp task shared(j)
        j = fibonacci(n - 2);
#pragma omp taskwait
        return i + j;
    }
}

int main(int argc, char **argv)
{
    if (argc != 2)
    {
        printf("Usage: %s <number>\n", argv[0]);
        return -1;
    }

    int n = atoi(argv[1]);
    int result;
    double start_time, end_time;

    // Start timing
    start_time = omp_get_wtime();

#pragma omp parallel
    {
#pragma omp single
        result = fibonacci(n);
    }

    // End timing
    end_time = omp_get_wtime();

    printf("Result is %d\n", result);
    printf("Time taken: %f seconds\n", end_time - start_time);

    return 0;
}
