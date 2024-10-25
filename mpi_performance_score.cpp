#include <sycl/sycl.hpp>
#include <mpi.h>
#include <iostream>
#include <vector>
#include <cmath>

using namespace sycl;

int main(int argc, char *argv[]) {
    // Initialize MPI
    MPI_Init(&argc, &argv);

    int rank, size;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    // Get and print the MPI version
    int version, subversion;
    MPI_Get_version(&version, &subversion);
    if (rank == 0) {
        std::cout << "MPI Version: " << version << "." << subversion << std::endl;
    }

    // Get and print the Intel compiler version
    #ifdef __INTEL_COMPILER
        if (rank == 0) {
            std::cout << "Intel Compiler Version: " << __INTEL_COMPILER << std::endl;
        }
    #endif
    
    // Set up a DPC++ queue to target the GPU and print backend information
    queue q{gpu_selector_v};
    if (rank == 0) {
        std::cout << "Running on device: " << q.get_device().get_info<info::device::name>() << std::endl;
    }

    // Define the size of the data (increase the workload)
    const int N = 1000000000;
    const int local_N = N / size;
    std::vector<float> data(local_N, rank);

    // Allocate memory on the GPU for each rank's portion of the data
    float *d_data = malloc_device<float>(local_N, q);

    // warm-up
    q.parallel_for(range<1>(local_N), [=](id<1> i) {
        d_data[i] = std::sin(d_data[i]) * std::cos(d_data[i]) + std::sqrt(d_data[i]);
    }).wait();
    
    // Initialize variables to accumulate times
    const int iterations = 1000;
    double total_copy_to_gpu_time = 0.0;
    double total_compute_time = 0.0;
    double total_copy_to_host_time = 0.0;

    for (int iter = 0; iter < iterations; ++iter) {
        // Measure the time for copying data to the GPU
        double start_time = MPI_Wtime();
        q.memcpy(d_data, data.data(), local_N * sizeof(float)).wait();
        total_copy_to_gpu_time += MPI_Wtime() - start_time;

        // Measure the time for performing more complex computations on the GPU
        start_time = MPI_Wtime();
        q.parallel_for(range<1>(local_N), [=](id<1> i) {
            d_data[i] = std::sin(d_data[i]) * std::cos(d_data[i]) + std::sqrt(d_data[i]);
        }).wait();
        total_compute_time += MPI_Wtime() - start_time;

        // Measure the time for copying results back to the host
        start_time = MPI_Wtime();
        q.memcpy(data.data(), d_data, local_N * sizeof(float)).wait();
        total_copy_to_host_time += MPI_Wtime() - start_time;
    }

    // Calculate average times
    double avg_copy_to_gpu_time = total_copy_to_gpu_time / iterations;
    double avg_compute_time = total_compute_time / iterations;
    double avg_copy_to_host_time = total_copy_to_host_time / iterations;

    // Free GPU memory
    free(d_data, q);

    // Gather results using MPI
    std::vector<float> all_data(N);
    MPI_Gather(data.data(), local_N, MPI_FLOAT, all_data.data(), local_N, MPI_FLOAT, 0, MPI_COMM_WORLD);

    // Print performance results on the root process
    if (rank == 0) {
        std::cout << "Average copy to GPU time: " << avg_copy_to_gpu_time << " seconds" << std::endl;
        std::cout << "Average compute time: " << avg_compute_time << " seconds" << std::endl;
        std::cout << "Average copy to host time: " << avg_copy_to_host_time << " seconds" << std::endl;
    }

    // Finalize MPI
    MPI_Finalize();

    return 0;
}
