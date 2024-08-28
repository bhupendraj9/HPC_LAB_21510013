#include <omp.h>
#include <stdio.h>

int main()
{
    // Number of threads to use
    int num_threads = 2;

// Initialize the OpenMP parallel region
#pragma omp parallel num_threads(num_threads)
    {
        int thread_id = omp_get_thread_num(); // Get the thread id

        // Ensure that each series is printed by different threads
        if (thread_id == 0)
        {
            printf("Series of 2: ");
            for (int i = 2; i <= 20; i += 2)
            { // Print series of 2
                printf("%d ", i);
            }
            printf("\n");
        }
        else if (thread_id == 1)
        {
            printf("Series of 4: ");
            for (int i = 4; i <= 40; i += 4)
            { // Print series of 4
                printf("%d ", i);
            }
            printf("\n");
        }
    }

    return 0;
}
