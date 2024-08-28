#include <omp.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define N 2000
void add(int **a, int **b, int **c)
{
#pragma omp parallel for
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            c[i][j] = a[i][j] + b[i][j];
        }
    }
}
void input(int **a, int num)
{
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            a[i][j] = num;
        }
    }
}
void displayMatrix(int **a)
{

    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            printf("%d ", a[i][j]);
        }
        printf("\n");
    }
}

int main()
{
    int **a = (int **)malloc(sizeof(int *) * N);
    int **b = (int **)malloc(sizeof(int *) * N);
    int **c = (int **)malloc(sizeof(int *) * N);
    for (int i = 0; i < N; i++)
    {
        a[i] = (int *)malloc(sizeof(int) * N);
        b[i] = (int *)malloc(sizeof(int) * N);
        c[i] = (int *)malloc(sizeof(int) * N);
    }
    input(a, 1);
    input(b, 1);
    double start = omp_get_wtime();
    add(a, b, c);
    double end = omp_get_wtime();
    // display(c);
    printf("Time taken (para): %f\n", end - start);
}