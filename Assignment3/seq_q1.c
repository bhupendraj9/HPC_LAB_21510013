
#include <stdio.h>
#include <time.h>
#define n 100000
int sort(int nums[])
{
    int i, j;
    for (i = 0; i < n - 1; i++)
        for (j = 0; j < n - i - 1; j++)
            if (nums[j] > nums[j + 1])
            {
                int temp = nums[j];
                nums[j] = nums[j + 1];
                nums[j + 1] = temp;
            }
}

int sortDesc(int nums[])
{
    int i, j;
    for (i = 0; i < n; i++)
    {

        for (j = i + 1; j < n; j++)
        {
            if (nums[i] < nums[j])
            {
                int a = nums[i];
                nums[i] = nums[j];
                nums[j] = a;
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
    clock_t t = clock();
    sort(nums1);
    sortDesc(nums2);
    t = clock() - t;
    double time = ((double)t) / CLOCKS_PER_SEC;
    printf("Time taken (seq): %f\n", time);
    int sum = 0;
    for (int i = 0; i < n; i++)
    {
        sum = sum + (nums1[i] * nums2[i]);
    }
    printf("%d\n", sum);
    return 0;
}