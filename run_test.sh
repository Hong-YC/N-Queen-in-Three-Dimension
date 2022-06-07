#!/bin/bash
cd src
if [ "$1" == "serial2D" ]
then
    make serial_2D_test
    ./serial_2D_test $2
elif [ "$1" == "mpi2D" ]
then
    make mpi_2D_test
    mpiexec -n $3 ./mpi_2D_test $2
elif [ "$1" == "omp2D" ]
then
    make omp_2D_test
   ./omp_2D_test $2 $3 
elif [ "$1" == "serial3D" ]
then
    make serial_3D_test
    ./serial_3D_test $2
elif [ "$1" == "mpi3D" ]
then
    make mpi_3D_test
    mpiexec -n $3 ./mpi_3D_test $2
elif [ "$1" == "mpi_omp3D" ]
then
    make mpi_omp_3D_test
    mpiexec -n $3 -x OMP_NUM_THREADS=$4 ./mpi_omp_3D_test $2
fi
cd ..
