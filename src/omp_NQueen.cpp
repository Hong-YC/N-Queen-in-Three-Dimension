#include <iostream>
#include <vector>  
#include <sys/time.h>
#include <omp.h>
#include <algorithm>
#include "util.h"

bool compareBoard(int* b1, int* b2){
    if(b1[0] < b2[0]){
        return true;
    }
    else if(b1[0] > b2[0]){
        return false;
    }
    else{
        return (b1[1] < b2[1]);
    }
}

int main(int argc, char **argv) {

    //Use vector or array or vector of array?
    std::vector<int*> result;
    

    int NumberOfQueen = atoi(argv[1]);
    int NumberOfThread = atoi(argv[2]);
    double startTime = cpuTime();

    int i;

    #pragma omp parallel num_threads(NumberOfThread) default(none) private(i) shared(result, NumberOfQueen)
    {
        std::vector<int> candidate;
        std::vector<int*> local_result;
        #pragma omp for
        for(i = 0; i < NumberOfQueen; i++){
            candidate.clear();
            candidate.push_back(i);
            FindNQueeen2D(1, candidate, local_result, NumberOfQueen);
        }
        #pragma omp critical
        {
            result.insert(result.end(), local_result.begin(), local_result.end());
        }

        
    }
    std::sort(result.begin(), result.end(), compareBoard);
    
    double endTime = cpuTime();

    //printResult(result, NumberOfQueen);
    printf("\nN = %d, Number of 2D: %d\n", NumberOfQueen, result.size());
    std::cout << "2D calculation time:" << endTime - startTime << std::endl;
    freeResult(result);

    return 0;



}
