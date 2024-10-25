# Usage
## compile 
source /opt/intel/oneapi/2024.1/oneapi-vars.sh  
mpiicpx -o mpi_performance_score mpi_performance_score.cpp
## Run
mpirun -np 2 -ppn 1 ./mpi_performance_score

## Performance example
```
(itex_test) gta@DUT7301PVC:~/kazuki/mpi_performance_score$ mpirun -np 2 -ppn 1 ./mpi_performance_score
Processor DUT7301PVC, rank 0: average time = 0.0143139seconds
Processor DUT7301PVC, rank 1: average time = 0.0144356seconds
(itex_test) gta@DUT7301PVC:~/kazuki/mpi_performance_score$ mpirun -np 4 -ppn 1 ./mpi_performance_score
Processor DUT7301PVC, rank 1: average time = 0.0143617seconds
Processor DUT7301PVC, rank 2: average time = 0.0145375seconds
Processor DUT7301PVC, rank 0: average time = 0.0145584seconds
Processor DUT7301PVC, rank 3: average time = 0.014789seconds
```
