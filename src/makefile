serial_2D_test: serial_NQueen.o util.o
	g++ --std=c++11 -o serial_2D_test serial_NQueen.o util.o

serial_3D_test: serial_NQueen3D.o util.o
	g++ --std=c++11 -o serial_3D_test serial_NQueen3D.o util.o

mpi_2D_test: mpi_NQueen.o util.o
	mpic++ --std=c++11 -o mpi_2D_test mpi_NQueen.o util.o

omp_2D_test: omp_NQueen.o util.o
	g++ --std=c++11 -o omp_2D_test -fopenmp omp_NQueen.o util.o

mpi_3D_test: mpi_NQueen3D.o util.o
	mpic++ --std=c++11 -o mpi_3D_test mpi_NQueen3D.o util.o

mpi_omp_3D_test: mpi_omp_NQueen3D.o util.o
	mpic++ --std=c++11 -o mpi_omp_3D_test -fopenmp mpi_omp_NQueen3D.o util.o

util.o: util.cpp util.h
	g++ --std=c++11 -c util.cpp

serial_NQueen.o: serial_NQueen.cpp 
	g++ --std=c++11 -c serial_NQueen.cpp

mpi_NQueen.o: mpi_NQueen.cpp
	mpic++ --std=c++11 -c mpi_NQueen.cpp

omp_NQueen.o: omp_NQueen.cpp
	g++ --std=c++11 -c -fopenmp omp_NQueen.cpp

serial_NQueen3D.o: serial_NQueen3D.cpp 
	g++ --std=c++11 -c serial_NQueen3D.cpp

mpi_NQueen3D.o: mpi_NQueen3D.cpp
	mpic++ --std=c++11 -c mpi_NQueen3D.cpp

mpi_omp_NQueen3D.o: mpi_omp_NQueen3D.cpp
	mpic++ --std=c++11 -fopenmp -c mpi_omp_NQueen3D.cpp

clearAllTest:
	-rm *_test
clear:
	-rm *.o