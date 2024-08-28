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

void initialize_vector(int *vector)
{
    for (int i = 0; i < N; i++)
    {
        vector[i] = rand() % 10;
    }
}

void matrix_vector_multiply(int **a, int *x, int *y)
{
    for (int i = 0; i < N; i++)
    {
        y[i] = 0;
        for (int j = 0; j < N; j++)
        {
            y[i] += a[i][j] * x[j];
        }
    }
}

void matrix_vector_multiply_parallel(int **a, int *x, int *y)
{
#pragma omp parallel for
    for (int i = 0; i < N; i++)
    {
        y[i] = 0;
        for (int j = 0; j < N; j++)
        {
            y[i] += a[i][j] * x[j];
        }
    }
}

void print_vector(int *vector)
{
    for (int i = 0; i < 5; i++)
    { // Print only first 5 elements for brevity
        printf("%d ", vector[i]);
    }
    printf("\n");
}

int main()
{
    int **a = malloc(N * sizeof(int *));
    int *x = malloc(N * sizeof(int));
    int *y = malloc(N * sizeof(int));
    for (int i = 0; i < N; i++)
    {
        a[i] = malloc(N * sizeof(int));
    }

    initialize_matrix(a);
    initialize_vector(x);

    // Sequential
    double start = omp_get_wtime();
    matrix_vector_multiply(a, x, y);
    double end = omp_get_wtime();
    double seq_time = end - start;
    printf("Sequential Time: %f seconds\n", seq_time);

    printf("Result Vector (Sequential):\n");
    print_vector(y);

    // Parallel
    start = omp_get_wtime();
    matrix_vector_multiply_parallel(a, x, y);
    end = omp_get_wtime();
    double par_time = end - start;
    printf("Parallel Time: %f seconds\n", par_time);

    printf("Result Vector (Parallel):\n");
    print_vector(y);

    // Calculate Speedup and Efficiency
    double speedup = seq_time / par_time;
    int num_threads = omp_get_max_threads();
    double efficiency = speedup / num_threads;

    printf("Speedup: %f\n", speedup);
    printf("Efficiency: %f\n", efficiency);

    for (int i = 0; i < N; i++)
    {
        free(a[i]);
    }
    free(a);
    free(x);
    free(y);

    return 0;
}
