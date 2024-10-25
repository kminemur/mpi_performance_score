# Usage
## compile 
source /opt/intel/oneapi/2024.1/oneapi-vars.sh  
mpiicpx -fsycl -o mpi_performance_score mpi_performance_score.cpp
## Run
mpirun -np 2 -ppn 4 ./mpi_performance_score

## Performance example
```
(itex_test) gta@DUT7301PVC:~/kazuki/mpi_performance_score$ mpirun -np 1 -ppn 4 ./mpi_performance_score
MPI Version: 3.1
Average copy to GPU time: 0.152077 seconds
Average compute time: 0.0075197 seconds
Average copy to host time: 0.169095 seconds
(itex_test) gta@DUT7301PVC:~/kazuki/mpi_performance_score$ mpirun -np 2 -ppn 4 ./mpi_performance_score
MPI Version: 3.1
Average copy to GPU time: 0.103328 seconds
Average compute time: 0.00363815 seconds
Average copy to host time: 0.132195 seconds
(itex_test) gta@DUT7301PVC:~/kazuki/mpi_performance_score$ mpirun -np 4 -ppn 4 ./mpi_performance_score
MPI Version: 3.1
Average copy to GPU time: 0.0947346 seconds
Average compute time: 0.00244697 seconds
Average copy to host time: 0.103237 second
```
