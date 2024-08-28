#include <omp.h>
#include <stdio.h>
#include <stdlib.h>
#define N 10

void hello_world()
{
    printf("Hello world\n");
}
void print(int i)
{
    printf("Value %d\n", i);
}
int main()
{
#pragma omp parallel
    {
#pragma omp for nowait

        for (int i = 0; i < N; i++)
        {
            print(i);
        }
        hello_world();
    }
}