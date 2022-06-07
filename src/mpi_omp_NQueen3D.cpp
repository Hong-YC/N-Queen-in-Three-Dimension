#include <iostream>
#include <vector>  
#include <sys/time.h>
#include <mpi.h>
#include <omp.h>
#include "util.h"




int main(int argc, char **argv) {

    int number_of_processes, rank;
    double startTime, endTime; 
    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &number_of_processes);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    std::vector<int*> result2D;
    std::vector<int> candidate;
    int NumberOfQueen;
    int thread_count;
    if(rank == 0){
        NumberOfQueen = atoi(argv[1]);
        thread_count = omp_get_num_threads();
    }

    startTime = cpuTime();
//================================================================================
    MPI_Bcast(&NumberOfQueen, 1, MPI_INT, 0, MPI_COMM_WORLD);
    MPI_Bcast(&thread_count, 1, MPI_INT, 0, MPI_COMM_WORLD);
    FindNQueeen2D(0, candidate, result2D, NumberOfQueen);
    
    //Calculate how may 2D result start with index 0
    int total_zero_count = 0;
    while(result2D[total_zero_count][0] == 0){
        total_zero_count++;
    }
    int local_size = total_zero_count / number_of_processes;
    int local_size_zero = local_size + total_zero_count % number_of_processes;
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

    
    std::vector<int**> result3D;
    //Use OpenMP to further parallelize the generation of 3D result;
    int i;
    #pragma omp parallel num_threads(thread_count) default(none) private(i)\
                         shared(total_zero_count, result2D, result3D, NumberOfQueen, startIdx, endIdx)
    {
        std::vector<int*> candidate3D;
        std::vector<int**> local_result;
        #pragma omp for
        for(i = startIdx; i <= endIdx; i++){
            candidate3D.clear();
            candidate3D.push_back(result2D[i]);
            FindNQueeen3DParallel(1, candidate3D, result3D, result2D, total_zero_count, NumberOfQueen);
        }
        #pragma omp critical
        {
            result3D.insert(result3D.end(), local_result.begin(), local_result.end());
        }

        
    }



    int local_result_size = result3D.size();
        
    int* local_result_array = new int[local_result_size * NumberOfQueen * NumberOfQueen];
    for(int i = 0; i < local_result_size; i++){
        for(int j = 0; j < NumberOfQueen; j++){
            for(int k = 0; k < NumberOfQueen; k++){
                local_result_array[i*NumberOfQueen*NumberOfQueen +j * NumberOfQueen + k] = result3D[i][j][k];
            }
            
        }
    }


    //Need to gather the size of local result in each process
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

    


    //Calculate the displacement array and size count array
    int *displs, *scounts;
    if(rank == 0){
        displs = (int *)malloc(number_of_processes*sizeof(int));
        scounts = (int *)malloc(number_of_processes*sizeof(int));
        int offset = 0;
        for (int i = 0; i < number_of_processes; ++i) {
            displs[i] = offset;
            scounts[i] = result_size_array[i] * NumberOfQueen * NumberOfQueen;
            offset += scounts[i];   
        } 
         
    }
    //Use Gatherv to accumulate the result in each process
    int* result_array;
    if(rank == 0){
        result_array = new int[total_result_count * NumberOfQueen * NumberOfQueen];
    }
    MPI_Gatherv(local_result_array, local_result_size * NumberOfQueen* NumberOfQueen, MPI_INT, 
    result_array, scounts, displs, MPI_INT, 0, MPI_COMM_WORLD);


//====================================================================
    if(rank==0){
        endTime = cpuTime();
        printf("Number of 2D: %d\n", result2D.size());
        //printf("Number of 2D start with zero: %d\n", total_zero_count);
        printf("Number of unique 3D: %d\n", total_result_count);
        printResult3D(result_array, total_result_count, NumberOfQueen );
        std::cout << "3D calculation time:" << endTime - startTime << std::endl;
        delete [] result_size_array;
        delete [] result_array;
        free(displs);
        free(scounts);
    }
    
    
    
    freeResult(result2D);
    freeResult(result3D);

    MPI_Finalize();
    return 0;




}