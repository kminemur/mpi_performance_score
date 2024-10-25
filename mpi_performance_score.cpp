#include <mpi.h>
#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <numeric>
#include <sycl/sycl.hpp>

using namespace sycl;

// SYCLカーネル: 配列の合計を計算
double perform_computation(queue &q, int size) {
    std::vector<double> h_array(size);

    // 配列をランダムな値で初期化
    for (int i = 0; i < size; ++i) {
        h_array[i] = static_cast<double>(rand()) / RAND_MAX;
    }

    // デバイスメモリを割り当て
    buffer<double, 1> d_array(h_array.data(), range<1>(size));
    buffer<double, 1> d_result(1);

    // SYCLカーネルを起動
    q.submit([&](handler &h) {
        auto array = d_array.get_access<access::mode::read>(h);
        auto result = d_result.get_access<access::mode::write>(h);
        accessor<double, 1, access::mode::read_write, access::target::local> local_mem(range<1>(256), h);

        h.parallel_for<class sum_array>(nd_range<1>(range<1>((size + 255) / 256 * 256), range<1>(256)), [=](nd_item<1> item) {
            int tid = item.get_local_id(0);
            int i = item.get_global_id(0);
            local_mem[tid] = (i < size) ? array[i] : 0.0;
            item.barrier(access::fence_space::local_space);

            // Reduction
            for (int s = 256 / 2; s > 0; s >>= 1) {
                if (tid < s) {
                    local_mem[tid] += local_mem[tid + s];
                }
                item.barrier(access::fence_space::local_space);
            }

            if (tid == 0) {
                atomic_fetch_add(result[0], local_mem[0]);
            }
        });
    });

    // デバイスからホストへ結果を転送
    auto h_result = d_result.get_access<access::mode::read>();
    return h_result[0];
}

// Function to perform a simple computation: summing an array
double perform_computation(int size) {
    std::vector<double> array(size);

    // Initialize the array with random values
    for (int i = 0; i < size; ++i) {
        array[i] = static_cast<double>(rand()) / RAND_MAX;
    }

    // Sum the array
    double sum = 0.0;
    for (int i = 0; i < size; ++i) {
        sum += array[i];
    }

    return sum;
}

int main(int argc, char** argv) {
    // Initialize the MPI environment
    MPI_Init(&argc, &argv);

    // Get the number of processes
    int world_size;
    MPI_Comm_size(MPI_COMM_WORLD, &world_size);

    // Get the rank of the process
    int world_rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);

    // Get the name of the processor
    char processor_name[MPI_MAX_PROCESSOR_NAME];
    int name_len;
    MPI_Get_processor_name(processor_name, &name_len);

    // Get the MPI version
    int version, subversion;
    MPI_Get_version(&version, &subversion);

    // Print the MPI version information
    if (world_rank == 0) {
        std::cout << "MPI Version: " << version << "." << subversion << std::endl;
    }

    // SYCL queue
    queue q;
    
    // Seed the random number generator
    srand(time(NULL) + world_rank);

    // Define the size of the array to be summed
    int array_size = 10000000;

    // Define the number of iterations
    int num_iterations = 1000;

    // Vector to store the elapsed times for each iteration
    std::vector<double> elapsed_times(num_iterations);

    for (int i = 0; i < num_iterations; ++i) {
        // Start the timer
        double start_time = MPI_Wtime();

        // Perform the computation
        //double result = perform_computation(array_size);
        double result = perform_computation(q, array_size);

        // Stop the timer
        double end_time = MPI_Wtime();
        elapsed_times[i] = end_time - start_time;

        // Print the result and the time taken for this iteration
        //std::cout << "Processor " << processor_name << ", rank " << world_rank
        //          << " out of " << world_size << " processors: iteration " << i + 1
        //          << ", result = " << result << ", time = " << elapsed_times[i] << " seconds" << std::endl;
    }

    // Calculate the average elapsed time
    double total_time = std::accumulate(elapsed_times.begin(), elapsed_times.end(), 0.0);
    double average_time = total_time / num_iterations;

    // Calculate the average performance score (e.g., operations per second)
    double average_performance_score = array_size / average_time;
    std::cout << "Processor " << processor_name << ", rank " << world_rank
              << ": average time = " << average_time << "seconds" << std::endl;

    // Finalize the MPI environment
    MPI_Finalize();
    return 0;
}
