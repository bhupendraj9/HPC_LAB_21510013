#include <omp.h>
#include <stdio.h>

int main()
{
    // Array of family member names
    char *family_members[] = {"Sharvani", "Bhupendra", "Anita", "Baliram"};
    int num_members = 4;

    // Parallel region to print names with different threads
#pragma omp parallel for
    for (int i = 0; i < num_members; i++)
    {
        printf("Thread %d: %s\n", omp_get_thread_num(), family_members[i]);
    }
    return 0;
}
