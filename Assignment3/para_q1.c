#include <omp.h>
#include <stdio.h>
#include <time.h>
#define n 100000

int sort(int nums[])
{
    int i, j;
    for (i = 0; i < n; i++)
    {
        int turn = i % 2;
#pragma omp parallel for
        for (j = turn; j < n - 1; j += 2)
            if (nums[j] > nums[j + 1])
            {
                int temp = nums[j];
                nums[j] = nums[j + 1];
                nums[j + 1] = temp;
            }
    }
}

int sort_des(int nums[])
{
    int i, j;
    for (i = 0; i < n; ++i)
    {
        int turn = i % 2;
#pragma omp parallel for
        for (j = turn; j < n - 1; j += 2)
        {
            if (nums[j] < nums[j + 1])
            {
                int temp = nums[j];
                nums[j] = nums[j + 1];
                nums[j + 1] = temp;
            }
        }
    }
}

int main()
{
    int nums1[n], nums2[n];
    for (int i = 0; i < n; i++)
    {
        nums1[i] = 10;
    }
    for (int i = 0; i < n; i++)
    {
        nums2[i] = 20;
    }

    // Set the number of threads
    omp_set_num_threads(4); // Example: Set to 4 threads

    // Print the number of threads used
    int num_threads = omp_get_max_threads();
    printf("Number of threads: %d\n", num_threads);

    clock_t t;
    t = clock();
    sort(nums1);
    sort_des(nums2);
    t = clock() - t;

    double time_taken = ((double)t) / CLOCKS_PER_SEC;
    printf("Time taken (para): %f\n", time_taken);

    int sum = 0;
    for (int i = 0; i < n; i++)
    {
        sum = sum + (nums1[i] * nums2[i]);
    }
    printf("Dot Product: %d\n", sum);

    return 0;
}
