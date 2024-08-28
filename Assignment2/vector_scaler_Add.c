#include <stdio.h>
#include <omp.h>
#include <time.h>

int main()
{
    int n = 100000;
    int scalar = 5;
    int vector[n];
    int result_seq[n];
    int result_par[n];

    // Initialize the vector with values
    for (int i = 0; i < n; i++)
    {
        vector[i] = i;
    }

    // Sequential vector-scalar addition
    clock_t start_seq = clock();
    for (int i = 0; i < n; i++)
    {
        result_seq[i] = vector[i] + scalar;
    }
    clock_t end_seq = clock();

    // Parallel vector-scalar addition
    double start_par = omp_get_wtime();
#pragma omp parallel for
    for (int i = 0; i < n; i++)
    {
        result_par[i] = vector[i] + scalar;
    }
    double end_par = omp_get_wtime();

    // Execution time analysis
    double time_seq = (double)(end_seq - start_seq) / CLOCKS_PER_SEC;
    double time_par = end_par - start_par;

    printf("Sequential Execution Time: %f seconds\n", time_seq);
    fflush(stdout);
    printf("Parallel Execution Time: %f seconds\n", time_par);
    fflush(stdout);

    // Calculate Speedup and Efficiency
    double speedup = time_seq / time_par;
    int num_threads = omp_get_max_threads();
    double efficiency = speedup / num_threads;

    printf("Speedup: %f\n", speedup);
    fflush(stdout);
    printf("Efficiency: %f\n", efficiency);
    fflush(stdout);

    // Analysis of execution times
    if (time_seq > time_par)
    {
        printf("Parallel approach is faster by %f seconds.\n", time_seq - time_par);
    }
    else if (time_seq < time_par)
    {
        printf("Sequential approach is faster by %f seconds.\n", time_par - time_seq);
    }
    else
    {
        printf("Both approaches have the same execution time.\n");
    }

    return 0;
}
