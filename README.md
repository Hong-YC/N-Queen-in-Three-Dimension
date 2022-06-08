# Parallelized appproach to the N-Queen problem in Three Dimension
## Introduction
In this project, we use OpenMP and OpenMPI to speed up the [double backtracking alogrithm](https://www.researchgate.net/publication/318479872_A_Novel_Double_Backtracking_Approach_to_the_N-Queens_Problem_in_Three_Dimensions) for solving N-Queen problem in three dimension.

[Project Report](Report.pdf)

## Environment
g++ (GCC) 4.8.5

mpiexec (OpenRTE) 3.0.0

## Experiment
Run the following commands to test different parallelization for the algorithm.

First, change the test script to executable by:
```bash
chmod +x run_test.sh
```
Available tests:
1. Use backtracking algorithm to find all solutions to the N-Queen problem
```bash
./run_test.sh serial2D ${Number of Queen}
```
2. Use OpenMPI to speed up the backtracking algorithm for finding all solutions to the N-Queen problem
```bash
./run_test.sh mpi2D ${Number of Queen} ${Number of Process}
```
3. Use OpenMP to speed up the backtracking algorithm for finding all solutions to the N-Queen problem
```bash
./run_test.sh omp2D ${Number of Queen} ${Number of Thread}
```
4. Use double backtracking algorithm to find all solutions to the N-Queen problem in three dimension
```bash
./run_test.sh serial3D ${Number of Queen}
```
5. Use OpenMPI to speed up the double backtracking algorithm for finding all solutions to the N-Queen problem in three dimension
```bash
./run_test.sh mpi3D ${Number of Queen} ${Number of Process}
```
6. Use OpenMPI + OpenMP to speed up the double backtracking algorithm for finding all solutions to the N-Queen problem in three dimension
```bash
./run_test.sh mpi_omp3D ${Number of Queen} ${Number of Process} ${Number of Thread}
```
