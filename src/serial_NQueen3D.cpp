#include <iostream>
#include <vector>  
#include <sys/time.h>
#include "util.h"

int main(int argc, char **argv) {

    //Use vector or array or vector of array?
    std::vector<int*> result2D;
    std::vector<int> candidate;

    int NumberOfQueen = atoi(argv[1]);
    double startTime = cpuTime();
//================================================================================
    FindNQueeen2D(0, candidate, result2D, NumberOfQueen);
    std::vector<int*> candidate3D;
    std::vector<int**> result3D;
    FindNQueeen3D(0, candidate3D, result3D, result2D, NumberOfQueen);

//================================================================================
    double endTime = cpuTime();
    printResult3D(result3D, NumberOfQueen);
    printf("\nN = %d, Number of 2D: %d\n", NumberOfQueen, result2D.size());
    //printf("Number of unique 3D: %d\n", result3D.size()/factorial(NumberOfQueen));
    
    printf("Number of unique 3D: %d\n", result3D.size());
    
    std::cout << "3D calculation time:" << endTime - startTime << std::endl;
    freeResult(result2D);
    freeResult(result3D);



}