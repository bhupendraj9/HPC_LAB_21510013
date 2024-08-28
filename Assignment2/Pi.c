#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include <time.h>
#include <math.h>

int main()
{
    long long num_points = 1000000;     // Total number of random points
    long long points_in_circle_seq = 0; // Points that fall inside the circle (sequential)
    long long points_in_circle_par = 0; // Points that fall inside the circle (parallel)
    double x, y;
    double pi_estimate_seq, pi_estimate_par;
    double start_time, end_time;
    double seq_time, par_time;

    // Seed the random number generator
    srand(12345);

    // Sequential calculation of Pi
    clock_t seq_start = clock();
    for (long long i = 0; i < num_points; i++)
    {
        // Generate random (x, y) points
        x = (double)rand() / RAND_MAX;
        y = (double)rand() / RAND_MAX;

        // Check if the point is inside the unit circle
        if (x * x + y * y <= 1.0)
        {
            points_in_circle_seq++;
        }
    }
    clock_t seq_end = clock();
    seq_time = (double)(seq_end - seq_start) / CLOCKS_PER_SEC;

    // Estimate Pi using the sequential method
    pi_estimate_seq = 4.0 * points_in_circle_seq / num_points;

    // Parallel calculation of Pi
    start_time = omp_get_wtime();
#pragma omp parallel for private(x, y) reduction(+ : points_in_circle_par)
    for (long long i = 0; i < num_points; i++)
    {
        // Generate random (x, y) points
        x = (double)rand() / RAND_MAX;
        y = (double)rand() / RAND_MAX;

        // Check if the point is inside the unit circle
        if (x * x + y * y <= 1.0)
        {
            points_in_circle_par++;
        }
    }
    end_time = omp_get_wtime();
    par_time = end_time - start_time;

    // Estimate Pi using the parallel method
    pi_estimate_par = 4.0 * points_in_circle_par / num_points;

    // Output the estimated values of Pi
    printf("Sequential Pi Estimate: %f\n", pi_estimate_seq);
    printf("Parallel Pi Estimate: %f\n", pi_estimate_par);

    // Output the execution times
    printf("Sequential Execution Time: %f seconds\n", seq_time);
    printf("Parallel Execution Time: %f seconds\n", par_time);

    // Calculate and output Speedup and Efficiency
    double speedup = seq_time / par_time;
    int num_threads = omp_get_max_threads();
    double efficiency = speedup / num_threads;

    printf("Speedup: %f\n", speedup);
    printf("Efficiency: %f\n", efficiency);

    // Analysis of the accuracy of the estimate
    double actual_pi = 3.141592653589793;
    printf("Error in Sequential Estimate: %f\n", abs(pi_estimate_seq - actual_pi));
    printf("Error in Parallel Estimate: %f\n", abs(pi_estimate_par - actual_pi));

    return 0;
}
