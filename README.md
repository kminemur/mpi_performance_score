# Usage
## compile 
source /opt/intel/oneapi/2024.1/oneapi-vars.sh  
mpiicpx -o mpi_performance_score mpi_performance_score.cpp
## Run
mpirun -np 2 -ppn 1 ./mpi_performance_score

## Performance example
```
(itex_test) gta@DUT7301PVC:~/kazuki/mpi_performance_score$ mpirun -np 1 -ppn 1 ./mpi_performance_score
MPI Version: 3.1
Processor DUT7301PVC, rank 0: average time = 0.0135742seconds
(itex_test) gta@DUT7301PVC:~/kazuki/mpi_performance_score$ mpirun -np 2 -ppn 1 ./mpi_performance_score
MPI Version: 3.1
Processor DUT7301PVC, rank 1: average time = 0.0143851seconds
Processor DUT7301PVC, rank 0: average time = 0.0148761seconds
(itex_test) gta@DUT7301PVC:~/kazuki/mpi_performance_score$ mpirun -np 4 -ppn 1 ./mpi_performance_score
MPI Version: 3.1
Processor DUT7301PVC, rank 0: average time = 0.0136245seconds
Processor DUT7301PVC, rank 3: average time = 0.014263seconds
Processor DUT7301PVC, rank 2: average time = 0.0150204seconds
Processor DUT7301PVC, rank 1: average time = 0.0152163seconds
```
