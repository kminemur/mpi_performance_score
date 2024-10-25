# Usage
## compile 
source /opt/intel/oneapi/2024.1/oneapi-vars.sh  
mpiicpx -fsycl -o mpi_performance_score mpi_performance_score.cpp
## Run
mpirun -np 2 -ppn 1 ./mpi_performance_score

## Performance example
```
(itex_test) gta@DUT7301PVC:~/kazuki/mpi_performance_score$ mpirun -np 1 -ppn 4 ./mpi_performance_score
MPI Version: 3.1
Copy to GPU time: 0.157356 seconds
Compute time: 0.00735125 seconds
Copy to host time: 0.217063 seconds
(itex_test) gta@DUT7301PVC:~/kazuki/mpi_performance_score$ mpirun -np 2 -ppn 4 ./mpi_performance_score
MPI Version: 3.1
Copy to GPU time: 0.0673648 seconds
Compute time: 0.0034279 seconds
Copy to host time: 0.0844298 seconds
(itex_test) gta@DUT7301PVC:~/kazuki/mpi_performance_score$ mpirun -np 4 -ppn 4 ./mpi_performance_score
MPI Version: 3.1
Copy to GPU time: 0.086862 seconds
Compute time: 0.00172195 seconds
Copy to host time: 0.111544 seconds
```
