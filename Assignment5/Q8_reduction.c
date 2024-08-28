
#include <omp.h>
#include <stdio.h>
#include <stdlib.h>

#define ARRAY_SIZE 1000000

int main()
{
    int *array = (int *)malloc(ARRAY_SIZE * sizeof(int));
    long long total_sum = 0;

    // Initialize the array
    for (int i = 0; i < ARRAY_SIZE; i++)
    {
        array[i] = 1; // Simple initialization
    }

    double start_time = omp_get_wtime();

// Parallel sum calculation with reduction
#pragma omp parallel reduction(+ : total_sum)
    {
#pragma omp for
        for (int i = 0; i < ARRAY_SIZE; i++)
        {
            total_sum += array[i];
        }
    }

    double end_time = omp_get_wtime();
    printf("Total sum (parallel with reduction): %lld\n", total_sum);
    printf("Execution time: %f seconds\n", end_time - start_time);

    free(array);
    return 0;
}
