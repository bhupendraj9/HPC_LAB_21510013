#include <omp.h>
#include <stdio.h>

int main()
{
    // Variable declaration
    int Aryabhatta = 10; // Value of Aryabhatta
    int num_threads = 4; // Number of threads (can be adjusted)

    // Parallel region with private variable Aryabhatta
#pragma omp parallel num_threads(num_threads) private(Aryabhatta)
    {
        // Initialize private variable for each thread
        Aryabhatta = 10;

        // Get thread ID
        int tid = omp_get_thread_num();

        // Perform multiplication
        int result = tid * Aryabhatta;

        // Print result
        printf("Thread %d: %d * %d = %d\n", tid, tid, Aryabhatta, result);
    }

    return 0;
}
