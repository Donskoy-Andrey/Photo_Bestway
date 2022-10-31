#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <algorithm>
#include <typeinfo>
#include "search.h"


int find_best_way(int* best_way, int* arr, int N){
    for (int i = 0; i < N; ++i){
        for (int j = 0; j < N; ++j){
            best_way[i*N+j] = 300;
        }
    }

    best_way[0] = 0; // 1st element is zero

    int path_to_point = 0;
    int current_value = 0;

    for (int i = 0; i < N; ++i){
        for (int j = 0; j < N; ++j){
            current_value = arr[i*N+j];
            path_to_point = best_way[i*N+j];

            if ((j != 0) and (j != N-1) and (i != (N-1))){
                // std::cout << "=1=" << std::endl;
                // std::cout << current_value << " " << path_to_point << std::endl;
                best_way[i*N+j-1] = std::min(best_way[i*N+j-1], current_value + path_to_point);
                best_way[i*N+j+1] = std::min(best_way[i*N+j+1], current_value + path_to_point);
                best_way[(i+1)*N+j] = std::min(best_way[(i+1)*N+j], current_value + path_to_point);
                
            }

            if ((j == 0) and (i != N-1)){ // 1st column
                // std::cout << "=2=" << std::endl;
                best_way[i*N+j+1] = std::min(best_way[i*N+j+1], current_value + path_to_point);
                best_way[(i+1)*N+j] = std::min(best_way[(i+1)*N+j], current_value + path_to_point);
            }

            if ((j == N-1) and (i != N-1)) { // last column
                // std::cout << "=3=" << std::endl;
                // std::cout << current_value << " " << path_to_point << std::endl;
                best_way[i*N+j-1] = std::min(best_way[i*N+j-1], current_value + path_to_point);
                best_way[(i+1)*N+j] = std::min(best_way[(i+1)*N+j], current_value + path_to_point);
            }

            if ((i == N-1) and (j != 0) and (j != N-1)){ // last row
                // std::cout << "=4=" << std::endl;
                // std::cout << current_value << " " << path_to_point << std::endl;
                best_way[i*N+j-1] = std::min(best_way[i*N+j-1], current_value + path_to_point);
                best_way[i*N+j+1] = std::min(best_way[i*N+j+1], current_value + path_to_point);
            }
        }
    }    

    return 0;
}