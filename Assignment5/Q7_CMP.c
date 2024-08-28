#include <omp.h>
#include <stdio.h>
#include <stdlib.h>

#define ARRAY_SIZE 1000000

// Function to calculate sum
void calculate_sum(long long *total_sum, int *array, int use_critical)
{
    *total_sum = 0; // Initialize total_sum
    double start_time = omp_get_wtime();

#pragma omp parallel
    {
        long long local_sum = 0;
#pragma omp for
        for (int i = 0; i < ARRAY_SIZE; i++)
        {
            local_sum += array[i];
        }

        // Synchronization
        if (use_critical)
        {
#pragma omp critical
            {
                *total_sum += local_sum;
            }
        }
        else
        {
#pragma omp atomic
            *total_sum += local_sum;
        }
    }

    double end_time = omp_get_wtime();
    printf("Total sum: %lld\n", *total_sum);
    printf("Execution time: %f seconds\n", end_time - start_time);
}

int main()
{
    int *array = (int *)malloc(ARRAY_SIZE * sizeof(int));

    // Initialize the array
    for (int i = 0; i < ARRAY_SIZE; i++)
    {
        array[i] = 1; // Simple initialization
    }

    long long total_sum;

    // Unsynchronized version
    printf("Unsynchronized version:\n");
    calculate_sum(&total_sum, array, 0);

    // Synchronized version with critical
    printf("\nSynchronized version with critical:\n");
    calculate_sum(&total_sum, array, 1);

    free(array);
    return 0;
}
