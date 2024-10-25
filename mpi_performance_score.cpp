#include <mpi.h>
#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>

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

    // Seed the random number generator
    srand(time(NULL) + world_rank);

    // Define the size of the array to be summed
    int array_size = 1000000;

    // Start the timer
    double start_time = MPI_Wtime();

    // Perform the computation
    double result = perform_computation(array_size);

    // Stop the timer
    double end_time = MPI_Wtime();
    double elapsed_time = end_time - start_time;

    // Print the result and the time taken
    std::cout << "Processor " << processor_name << ", rank " << world_rank
              << " out of " << world_size << " processors: result = " << result
              << ", time = " << elapsed_time << " seconds" << std::endl;

    // Calculate the performance score (e.g., operations per second)
    double performance_score = array_size / elapsed_time;
    std::cout << "Processor " << processor_name << ", rank " << world_rank
              << ": performance score = " << performance_score << " operations/second" << std::endl;

    // Finalize the MPI environment
    MPI_Finalize();
    return 0;
}
