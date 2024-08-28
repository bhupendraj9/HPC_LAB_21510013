#include <omp.h>
#include <stdio.h>

#define N 20

int main()
{
    int total_sum = 0;   // To store the final result
    int partial_sum = 0; // To store the partial sum of each thread

    // Parallel region with multiple threads
#pragma omp parallel private(partial_sum)
    {
        // Initialize partial sum for each thread
        partial_sum = 0;

        // Parallel for loop to compute partial sums
#pragma omp for
        for (int i = 1; i <= N; i++)
        {
            // Each thread computes its portion of the sum
            partial_sum += i;
        }

        // Update total_sum with the last thread's partial_sum
#pragma omp critical
        {
            total_sum += partial_sum;
        }
    }

    // Print the final total_sum after parallel region
    printf("Total sum of first %d natural numbers: %d\n", N, total_sum);

    return 0;
}
