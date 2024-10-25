# Usage
## compile 
source /opt/intel/oneapi/2024.1/oneapi-vars.sh  
mpiicpx -o mpi_performance_score mpi_performance_score.cpp
## Run
mpirun -np 2 -ppn 1 ./mpi_performance_score

## Performance example
```
(itex_test) gta@DUT7301PVC:~/kazuki/mpi_performance_score$ mpirun -np 2 -ppn 4 ./mpi_performance_score
MPI Version: 3.1
Copy to GPU time: 0.00399655 seconds
Compute time: 8.97449e-05 seconds
Copy to host time: 0.00263301 seconds
(itex_test) gta@DUT7301PVC:~/kazuki/mpi_performance_score$ mpirun -np 4 -ppn 4 ./mpi_performance_score
MPI Version: 3.1
Copy to GPU time: 0.00466524 seconds
Compute time: 0.000117116 seconds
Copy to host time: 0.00726988 seconds
(itex_test) gta@DUT7301PVC:~/kazuki/mpi_performance_score$ mpirun -np 4 -ppn 4 ./mpi_performance_score
MPI Version: 3.1
Copy to GPU time: 0.00385451 seconds
Compute time: 0.000109313 seconds
Copy to host time: 0.0036589 seconds
```
