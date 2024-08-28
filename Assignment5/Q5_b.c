#include <omp.h>
#include <stdio.h>
#include <stdlib.h>
void initialize_matrix(int **matrix, int N)
{
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            matrix[i][j] = rand() % 10;
        }
    }
}
void matrix_multiply_static(int **a, int **b, int **c, int N)
{
#pragma omp parallel for schedule(static)
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

int main()
{
    int N = 100; // Matrix size
    int **a = (int **)malloc(N * sizeof(int *));
    int **b = (int **)malloc(N * sizeof(int *));
    int **c = (int **)malloc(N * sizeof(int *));
    for (int i = 0; i < N; i++)
    {
        a[i] = (int *)malloc(N * sizeof(int));
        b[i] = (int *)malloc(N * sizeof(int));
        c[i] = (int *)malloc(N * sizeof(int));
    }

    initialize_matrix(a, N);
    initialize_matrix(b, N);

    double start = omp_get_wtime();
    matrix_multiply_static(a, b, c, N);
    double end = omp_get_wtime();

    double time_taken = end - start;
    printf("Static scheduling execution time: %f seconds\n", time_taken);

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
