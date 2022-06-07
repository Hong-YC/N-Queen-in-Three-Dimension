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
    FindNQueeen2D(0, candidate, result2D, NumberOfQueen);
    double endTime = cpuTime();

    //printResult(result2D, NumberOfQueen);

    printf("\nN = %d, Number of 2D: %d\n", NumberOfQueen, result2D.size());
    std::cout << "2D calculation time:" << endTime - startTime << std::endl;
    freeResult(result2D);


}
