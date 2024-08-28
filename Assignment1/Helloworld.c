#include <stdio.h>
#include <omp.h>

int main()
{
    int num_threads;
    double start_time, end_time, sequential_time, parallel_time;

    // Ask the user for the number of threads
    printf("Enter the number of threads: ");
    scanf("%d", &num_threads);

    // Sequential Execution
    printf("Sequential execution:\n");
    start_time = omp_get_wtime();
    for (int i = 0; i < num_threads; i++)
    {
        printf("Hello, World from thread %d\n", i);
    }
    end_time = omp_get_wtime();
    sequential_time = end_time - start_time;
    printf("Time taken for sequential execution: %f seconds\n", sequential_time);

    // Parallel Execution
    printf("\nParallel execution:\n");
    start_time = omp_get_wtime();
#pragma omp parallel num_threads(num_threads)
    {
        int thread_id = omp_get_thread_num();
        printf("Hello, World from thread %d\n", thread_id);
    }
    end_time = omp_get_wtime();
    parallel_time = end_time - start_time;
    printf("Time taken for parallel execution: %f seconds\n", parallel_time);

    // Analysis
    double speedup = sequential_time / parallel_time;
    double efficiency = speedup / num_threads;

    printf("\nAnalysis:\n");
    printf("Speedup: %f\n", speedup);
    printf("Efficiency: %f\n", efficiency);

    return 0;
}
