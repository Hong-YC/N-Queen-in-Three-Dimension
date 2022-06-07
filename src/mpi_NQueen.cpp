#include <iostream>
#include <vector> 
#include <sys/time.h> 
#include "util.h"
#include <mpi.h>

int main(int argc, char **argv) {

    int number_of_processes, rank;
    double startTime, endTime; 
    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &number_of_processes);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);


    std::vector<int*> local_result;
    std::vector<int> candidate;

    int NumberOfQueen = atoi(argv[1]);

    startTime = cpuTime();

//=========================================================================================

    MPI_Bcast(&NumberOfQueen, 1, MPI_INT, 0, MPI_COMM_WORLD);

    int local_size = NumberOfQueen / number_of_processes;
    int local_size_zero = local_size + NumberOfQueen % number_of_processes;
    int startIdx, endIdx;

    if(rank == 0){
        startIdx = 0;
        endIdx = local_size_zero - 1;
        local_size = local_size_zero;
    }
    else{
        startIdx = local_size_zero + (rank - 1) * local_size;
        endIdx = local_size_zero + rank * local_size - 1;
    }


    for(int i = startIdx; i <= endIdx; i++){
        candidate.clear();
        candidate.push_back(i);
        FindNQueeen2D(1, candidate, local_result, NumberOfQueen);
    }

    int local_result_size = local_result.size();


    //Change result from vector to array for massage passing

    
    int * local_result_array = new int[local_result_size * NumberOfQueen];
    for(int i = 0; i < local_result_size; i++){
        for(int j = 0; j < NumberOfQueen; j++){
            local_result_array[i*NumberOfQueen+j] = local_result[i][j];
        }
    }

    //Need to gather how the size of local result in each process
    int* result_size_array;
    int total_result_count;

    if(rank == 0){
        result_size_array = new int[number_of_processes];
        result_size_array[0] = local_result_size;
        total_result_count = local_result_size;
        int receive_size;
        for(int i = 1; i < number_of_processes; i++){
            MPI_Recv(&receive_size, 1, MPI_INT, i, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
            result_size_array[i] = receive_size;
            total_result_count += receive_size;
        }
    }
    else{
        MPI_Send(&local_result_size, 1, MPI_INT, 0, 0, MPI_COMM_WORLD);
    }

    MPI_Bcast(&total_result_count, 1, MPI_INT, 0, MPI_COMM_WORLD);

    //Calculate the displacement array and size count array
    int *displs = (int *)malloc(number_of_processes*sizeof(int));
    int *scounts = (int *)malloc(number_of_processes*sizeof(int));
    if(rank == 0){
        int offset = 0;
        for (int i = 0; i < number_of_processes; ++i) {
            displs[i] = offset;
            scounts[i] = result_size_array[i] * NumberOfQueen;
            offset += scounts[i];   
        }    
    }

    MPI_Bcast(displs, number_of_processes, MPI_INT, 0, MPI_COMM_WORLD);
    MPI_Bcast(scounts, number_of_processes, MPI_INT, 0, MPI_COMM_WORLD);

    //Use Gatherv to accumulate the result
    int* result_array = new int[total_result_count*NumberOfQueen];
    MPI_Allgatherv(local_result_array, local_result_size * NumberOfQueen, MPI_INT, 
    result_array, scounts, displs, MPI_INT, MPI_COMM_WORLD);

    
 //================================================================================   
    if(rank==0){
            //printResult(result, NumberOfQueen);
        endTime = cpuTime();
        //printf("Number of 2D: %d\n", total_result_count);
        printf("\nN = %d, Number of 2D: %d\n", NumberOfQueen, total_result_count);
        std::cout << "2D calculation time:" << endTime - startTime << std::endl;
        delete [] result_size_array;
    }

    delete [] result_array;
    free(displs);
    free(scounts);
    freeResult(local_result);
    delete [] local_result_array;

    MPI_Finalize();
    return 0;




}