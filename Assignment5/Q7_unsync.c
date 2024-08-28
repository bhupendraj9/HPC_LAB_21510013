#include <omp.h>
#include <stdio.h>
#include <stdlib.h>

#define ARRAY_SIZE 1000000

int main()
{
    int *array = (int *)malloc(ARRAY_SIZE * sizeof(int));
    long long total_sum = 0; // Shared variable

    // Initialize the array
    for (int i = 0; i < ARRAY_SIZE; i++)
    {
        array[i] = 1; // Simple initialization
    }

// Parallel region without synchronization
#pragma omp parallel
    {
        long long local_sum = 0;
#pragma omp for
        for (int i = 0; i < ARRAY_SIZE; i++)
        {
            local_sum += array[i];
        }

// Update total_sum concurrently (unsynchronized)
#pragma omp atomic
        total_sum += local_sum;
    }

    printf("Total sum (unsynchronized): %lld\n", total_sum);

    free(array);
    return 0;
}
