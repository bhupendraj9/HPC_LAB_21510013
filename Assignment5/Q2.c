#include <omp.h>
#include <stdio.h>

int main()
{
    int sum_of_squares = 0;

#pragma omp parallel
    {
        int tid = omp_get_thread_num();
        int square = tid * tid;
        printf("Thread %d square: %d\n", tid, square);

#pragma omp atomic
        sum_of_squares += square;
    }

    printf("Sum of squares of thread IDs: %d\n", sum_of_squares);
    return 0;
}
