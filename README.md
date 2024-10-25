# Usage
## compile 
source /opt/intel/oneapi/2024.1/oneapi-vars.sh
mpiicpx -o mpi_performance_score mpi_performance_score.cpp
## Run
mpirun -np 2 -ppn 1 ./mpi_performance_score

## Performance example
```
(itex_test) gta@DUT7301PVC:~/kazuki/performance$ mpiicpx -o mpi_performance_score mpi_performance_score.cpp
(itex_test) gta@DUT7301PVC:~/kazuki/performance$ ./mpi_performance_score
Processor DUT7301PVC, rank 0 out of 1 processors: result = 499966, time = 0.0338547 seconds
Processor DUT7301PVC, rank 0: performance score = 2.9538e+07 operations/second
(itex_test) gta@DUT7301PVC:~/kazuki/performance$ mpirun -np 2 ./mpi_performance_score
Processor DUT7301PVC, rank 0 out of 2 processors: result = 499791, time = 0.0339241 seconds
Processor DUT7301PVC, rank 0: performance score = 2.94776e+07 operations/second
Processor DUT7301PVC, rank 1 out of 2 processors: result = 500218, time = 0.0341816 seconds
Processor DUT7301PVC, rank 1: performance score = 2.92555e+07 operations/second
(itex_test) gta@DUT7301PVC:~/kazuki/performance$ mpirun -np 4 ./mpi_performance_score
Processor DUT7301PVC, rank 2 out of 4 processors: result = 500115, time = 0.034112 seconds
Processor DUT7301PVC, rank 2: performance score = 2.93152e+07 operations/second
Processor DUT7301PVC, rank 1 out of 4 processors: result = 500052, time = 0.0345514 seconds
Processor DUT7301PVC, rank 1: performance score = 2.89424e+07 operations/second
Processor DUT7301PVC, rank 3 out of 4 processors: result = 500605, time = 0.0344121 seconds
Processor DUT7301PVC, rank 3: performance score = 2.90596e+07 operations/second
Processor DUT7301PVC, rank 0 out of 4 processors: result = 500239, time = 0.0342905 seconds
Processor DUT7301PVC, rank 0: performance score = 2.91626e+07 operations/second
(itex_test) gta@DUT7301PVC:~/kazuki/performance$ mpirun -np 8 ./mpi_performance_score
Processor DUT7301PVC, rank 3 out of 8 processors: result = 500063, time = 0.0327751 seconds
Processor DUT7301PVC, rank 3: performance score = 3.0511e+07 operations/second
Processor DUT7301PVC, rank 1 out of 8 processors: result = 499892, time = 0.0345392 seconds
Processor DUT7301PVC, rank 1: performance score = 2.89526e+07 operations/second
Processor DUT7301PVC, rank 7 out of 8 processors: result = 500342, time = 0.0347016 seconds
Processor DUT7301PVC, rank 7: performance score = 2.88171e+07 operations/second
Processor DUT7301PVC, rank 2 out of 8 processors: result = 499745, time = 0.034668 seconds
Processor DUT7301PVC, rank 2: performance score = 2.8845e+07 operations/second
Processor DUT7301PVC, rank 6 out of 8 processors: result = 499884, time = 0.0350094 seconds
Processor DUT7301PVC, rank 6: performance score = 2.85638e+07 operations/second
Processor DUT7301PVC, rank 5 out of 8 processors: result = 500432, time = 0.0348153 seconds
Processor DUT7301PVC, rank 5: performance score = 2.8723e+07 operations/second
Processor DUT7301PVC, rank 0 out of 8 processors: result = 499992, time = 0.0347455 seconds
Processor DUT7301PVC, rank 0: performance score = 2.87807e+07 operations/second
Processor DUT7301PVC, rank 4 out of 8 processors: result = 499950, time = 0.0348084 seconds
Processor DUT7301PVC, rank 4: performance score = 2.87287e+07 operations/second
```
