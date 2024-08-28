#include <stdio.h>
#include <stdlib.h>

#define ARRAY_SIZE 1000000

int main()
{
    int *array = (int *)malloc(ARRAY_SIZE * sizeof(int));
    long long total_sum = 0;

    // Initialize the array
    for (int i = 0; i < ARRAY_SIZE; i++)
    {
        array[i] = 1; // Simple initialization
    }

    // Sequential sum calculation
    for (int i = 0; i < ARRAY_SIZE; i++)
    {
        total_sum += array[i];
    }

    printf("Total sum (sequential): %lld\n", total_sum);

    free(array);
    return 0;
}
