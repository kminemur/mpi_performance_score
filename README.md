# Usage
## compile 
source /opt/intel/oneapi/2024.1/oneapi-vars.sh  
mpiicpx -o mpi_performance_score mpi_performance_score.cpp
## Run
mpirun -np 2 -ppn 1 ./mpi_performance_score

## Performance example
```
(itex_test) gta@DUT7301PVC:~/kazuki/performance$ mpirun -np 2 -ppn 1 ./mpi_performance_score
\Processor DUT7301PVC, rank 0 out of 2 processors: result = 500078, time = 0.0323372 seconds
Processor DUT7301PVC, rank 0: performance score = 3.09242e+07 operations/second
Processor DUT7301PVC, rank 1 out of 2 processors: result = 500065, time = 0.0340608 seconds
Processor DUT7301PVC, rank 1: performance score = 2.93593e+07 operations/second
(itex_test) gta@DUT7301PVC:~/kazuki/performance$ mpirun -np 2 -ppn 2 ./mpi_performance_score
Processor DUT7301PVC, rank 1 out of 2 processors: result = 499707, time = 0.0329987 seconds
Processor DUT7301PVC, rank 1: performance score = 3.03042e+07 operations/second
Processor DUT7301PVC, rank 0 out of 2 processors: result = 499749, time = 0.0328878 seconds
Processor DUT7301PVC, rank 0: performance score = 3.04064e+07 operations/second
(itex_test) gta@DUT7301PVC:~/kazuki/performance$ mpirun -np 3 -ppn 1 ./mpi_performance_score
Processor DUT7301PVC, rank 2 out of 3 processors: result = 500017, time = 0.0328628 seconds
Processor DUT7301PVC, rank 2: performance score = 3.04295e+07 operations/second
Processor DUT7301PVC, rank 0 out of 3 processors: result = 499910, time = 0.033594 seconds
Processor DUT7301PVC, rank 0: performance score = 2.97672e+07 operations/second
Processor DUT7301PVC, rank 1 out of 3 processors: result = 500017, time = 0.0334627 seconds
Processor DUT7301PVC, rank 1: performance score = 2.98841e+07 operations/second
(itex_test) gta@DUT7301PVC:~/kazuki/performance$ mpirun -np 4 -ppn 1 ./mpi_performance_score
Processor DUT7301PVC, rank 1 out of 4 processors: result = 500308, time = 0.0330706 seconds
Processor DUT7301PVC, rank 1: performance score = 3.02384e+07 operations/second
Processor DUT7301PVC, rank 3 out of 4 processors: result = 499638, time = 0.0325191 seconds
Processor DUT7301PVC, rank 3: performance score = 3.07512e+07 operations/second
Processor DUT7301PVC, rank 2 out of 4 processors: result = 500116, time = 0.0336055 seconds
Processor DUT7301PVC, rank 2: performance score = 2.97571e+07 operations/second
Processor DUT7301PVC, rank 0 out of 4 processors: result = 499744, time = 0.0332452 seconds
Processor DUT7301PVC, rank 0: performance score = 3.00796e+07 operations/second
(itex_test) gta@DUT7301PVC:~/kazuki/performance$ mpirun -np 4 -ppn 4 ./mpi_performance_score
Processor DUT7301PVC, rank 3 out of 4 processors: result = 500244, time = 0.0316004 seconds
Processor DUT7301PVC, rank 3: performance score = 3.16451e+07 operations/second
Processor DUT7301PVC, rank 2 out of 4 processors: result = 500001, time = 0.0329657 seconds
Processor DUT7301PVC, rank 2: performance score = 3.03346e+07 operations/second
Processor DUT7301PVC, rank 1 out of 4 processors: result = 499788, time = 0.0334642 seconds
Processor DUT7301PVC, rank 1: performance score = 2.98827e+07 operations/second
Processor DUT7301PVC, rank 0 out of 4 processors: result = 499931, time = 0.0320118 seconds
Processor DUT7301PVC, rank 0: performance score = 3.12384e+07 operations/second
```
