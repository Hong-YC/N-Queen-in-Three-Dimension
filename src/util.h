#ifndef MY_UTIL
#define MY_UTIL

#include <vector> 

void printMatrix(int**, int);
bool validate(int, int , std::vector<int>& , int);
bool validate3D(int*, std::vector<int*>& , int );
double cpuTime();
void freeResult(std::vector<int* >&);
void freeResult(std::vector<int** >&);


void printResult(std::vector<int* >&, int);
void printResult3D(std::vector<int**>&, int);
void printResult3D(int*, int, int);


void FindNQueeen2D(int, std::vector<int>& , std::vector<int*>&, int);
void FindNQueeen3D(int, std::vector<int*>&, std::vector<int**>&, const std::vector<int*>& , int );
void FindNQueeen3DParallel(int , std::vector<int*>& , std::vector<int**>&, const std::vector<int*>& , int, int);
#endif