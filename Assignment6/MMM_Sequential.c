#include <omp.h>
#include <stdio.h>
#include <stdlib.h>

#define N 500 // Smaller size for visibility

void initialize_matrix(int **matrix)
{
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            matrix[i][j] = rand() % 10;
        }
    }
}

void matrix_multiply(int **a, int **b, int **c)
{
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            c[i][j] = 0;
            for (int k = 0; k < N; k++)
            {
                c[i][j] += a[i][k] * b[k][j];
            }
        }
    }
}

void matrix_multiply_parallel(int **a, int **b, int **c)
{
#pragma omp parallel for collapse(2)
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            c[i][j] = 0;
            for (int k = 0; k < N; k++)
            {
                c[i][j] += a[i][k] * b[k][j];
            }
        }
    }
}

void print_matrix(int **matrix)
{
    for (int i = 0; i < 5; i++)
    { // Print only first 5 rows for brevity
        for (int j = 0; j < 5; j++)
        {
            printf("%d ", matrix[i][j]);
        }
        printf("\n");
    }
}

int main()
{
    int **a = malloc(N * sizeof(int *));
    int **b = malloc(N * sizeof(int *));
    int **c = malloc(N * sizeof(int *));
    for (int i = 0; i < N; i++)
    {
        a[i] = malloc(N * sizeof(int));
        b[i] = malloc(N * sizeof(int));
        c[i] = malloc(N * sizeof(int));
    }

    initialize_matrix(a);
    initialize_matrix(b);

    // Sequential
    double start = omp_get_wtime();
    matrix_multiply(a, b, c);
    double end = omp_get_wtime();
    double seq_time = end - start;
    printf("Sequential Time: %f seconds\n", seq_time);

    printf("Result Matrix (Sequential):\n");
    print_matrix(c);

    // Parallel
    start = omp_get_wtime();
    matrix_multiply_parallel(a, b, c);
    end = omp_get_wtime();
    double par_time = end - start;
    printf("Parallel Time: %f seconds\n", par_time);

    printf("Result Matrix (Parallel):\n");
    print_matrix(c);

    // Calculate Speedup and Efficiency
    double speedup = seq_time / par_time;
    int num_threads = omp_get_max_threads();
    double efficiency = speedup / num_threads;

    printf("Speedup: %f\n", speedup);
    printf("Efficiency: %f\n", efficiency);

    for (int i = 0; i < N; i++)
    {
        free(a[i]);
        free(b[i]);
        free(c[i]);
    }
    free(a);
    free(b);
    free(c);

    return 0;
}
