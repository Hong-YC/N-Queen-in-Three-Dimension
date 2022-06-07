
#include "util.h"
#include <iostream>
#include <sys/time.h> 


void printMatrix(int** matrix, int N){
    for(int i = 0; i < N; i++){
        for(int j = 0; j < N; j++){
            printf("%d, ", matrix[i][j]);
        }
        printf("\n");
    }
}

bool validate(int rowIdx, int colIdx, std::vector<int>& candidate,  int N){
    
    for(int i = 0; i < colIdx; i++){
        if(candidate[i] == rowIdx){
            return false;
        }
        if(colIdx - i == abs(rowIdx - candidate[i])){
            return false;
        }
    }
    return true;
}

bool validate3D(int* candidate, std::vector<int*>& temp3D, int N){
    for(int h = 0; h < temp3D.size(); h++){
        for(int i = 0; i < N; i++){
            if(candidate[i] == temp3D[h][i]){
                return false;
            }
        }
    }
    return true;
}

double cpuTime(){
    struct timeval tp;
    gettimeofday(&tp, NULL);
    return ((double)tp.tv_sec+(double)tp.tv_usec*1.e-6);
}


void freeResult(std::vector<int* >& res){
    for(int i = 0; i < res.size(); i++){
        delete [] res[i];
    }
}

void freeResult(std::vector<int** >& res){
    for(int i = 0; i < res.size(); i++){
        delete [] res[i];
    }
}

void printResult(std::vector<int* >& res, int N){
    for(int i = 0; i < res.size(); i++){
        //int* sol = res[i];
        for(int j = 0; j < N; j++){
            printf("%d, ", res[i][j]);
        }
        printf("\n");
    }
}

void printResult3D(std::vector<int**>& res, int N){
    for(int i = 0; i< res.size(); i++){
        printf("3D Board %d:\n", i);
        for(int h = 0; h < N; h++){
            for(int k = 0; k < N; k++){
                printf("%d, ",res[i][h][k]);
            }
            printf("\n");
        }
        
    }
}

void printResult3D(int* res, int size, int N){
    for(int i = 0; i< size; i++){
        printf("3D Board %d:\n", i);
        for(int h = 0; h < N; h++){
            for(int k = 0; k < N; k++){
                printf("%d, ",res[i*N*N+h*N+k]);
            }
            printf("\n");
        }
        
    }
}

void FindNQueeen2D(int colIdx, std::vector<int>& candidate, std::vector<int*>& res, int N){
    if(colIdx == N){

        int* result_array = new int[N];
        for(int i = 0; i < N; i++){
            result_array[i] = candidate[i];
        }
        res.push_back(result_array);
        return;
    }
    for(int i = 0; i < N; i++){
        if(validate(i, colIdx, candidate, N)){
            candidate.push_back(i);
            FindNQueeen2D(colIdx+1, candidate, res, N);
            candidate.pop_back();
        }
    }


}

void FindNQueeen3D(int height, std::vector<int*>& candidate, 
                    std::vector<int**>&res, const std::vector<int*>& sol2D, int N){
/*
    height: the height for the current search tree
    candidata: the potentiall solution currently built
    res: store the final solution found
    sol2D: 2D block for building the 3D solution
    startIdx: the start index we should start founf the sol2D
    N: the height of the final solution 
*/
    if(height == N){
        int** cube = new int*[N];
        for(int h = 0; h < N; h++){
            for(int i = 0; i < N; i++){
                cube[h] = candidate[h];
            }
        }
        
        res.push_back(cube);
        return;
    }
    for(int i = 0; i < sol2D.size(); i++){
        if(sol2D[i][0] == height){
            if(validate3D(sol2D[i], candidate, N)){
                candidate.push_back(sol2D[i]);
                FindNQueeen3D(height+1, candidate, res, sol2D, N);
                candidate.pop_back();
            }
        }
        else if (sol2D[i][0] > height){
            break;
        }   
    }

}

void FindNQueeen3DParallel(int height, std::vector<int*>& candidate, 
                    std::vector<int**>&res, const std::vector<int*>& sol2D, int startIdx, int N){
/*
    height: the height for the current search tree
    candidata: the potentiall solution currently built
    res: store the final solution found
    sol2D: 2D block for building the 3D solution
    startIdx: the start index we should start founf the sol2D
    N: the height of the final solution 
*/
    if(height == N){
        int** cube = new int*[N];
        for(int h = 0; h < N; h++){
            for(int i = 0; i < N; i++){
                cube[h] = candidate[h];
            }
        }
        
        res.push_back(cube);
        //printf("Find solution: %d\n", res.size());
        //printMatrix(N, N, cube);
        return;
    }
    for(int i = startIdx; i < sol2D.size(); i++){
        if(sol2D[i][0] == height){
            if(validate3D(sol2D[i], candidate, N)){
                candidate.push_back(sol2D[i]);
                FindNQueeen3DParallel(height+1, candidate, res, sol2D, startIdx, N);
                candidate.pop_back();
            }
        }
        else if (sol2D[i][0] > height){
            break;
        }

        
    }


}

