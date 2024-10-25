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

    // Set up a DPC++ queue to target the GPU
    queue q{gpu_selector{}};

    // Define the size of the data (increase the workload)
    const int N = 1000000;
    std::vector<float> data(N, rank);

    // Allocate memory on the GPU
    float *d_data = malloc_device<float>(N, q);

    // Measure the time for copying data to the GPU
    double start_time = MPI_Wtime();
    q.memcpy(d_data, data.data(), N * sizeof(float)).wait();
    double copy_to_gpu_time = MPI_Wtime() - start_time;

    // warm-up
    q.parallel_for(range<1>(N), [=](id<1> i) {
        d_data[i] = std::sin(d_data[i]) * std::cos(d_data[i]);
    }).wait();
    
    // Measure the time for performing more complex computations on the GPU
    start_time = MPI_Wtime();
    q.parallel_for(range<1>(N), [=](id<1> i) {
        d_data[i] = std::sin(d_data[i]) * std::cos(d_data[i]);
    }).wait();
    double compute_time = MPI_Wtime() - start_time;

    // Measure the time for copying results back to the host
    start_time = MPI_Wtime();
    q.memcpy(data.data(), d_data, N * sizeof(float)).wait();
    double copy_to_host_time = MPI_Wtime() - start_time;

    // Free GPU memory
    free(d_data, q);

    // Gather results using MPI
    std::vector<float> all_data(N * size);
    MPI_Gather(data.data(), N, MPI_FLOAT, all_data.data(), N, MPI_FLOAT, 0, MPI_COMM_WORLD);

    // Print performance results on the root process
    if (rank == 0) {
        std::cout << "Copy to GPU time: " << copy_to_gpu_time << " seconds" << std::endl;
        std::cout << "Compute time: " << compute_time << " seconds" << std::endl;
        std::cout << "Copy to host time: " << copy_to_host_time << " seconds" << std::endl;
    }

    // Finalize MPI
    MPI_Finalize();

    return 0;
}
