#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <algorithm>
#include <typeinfo>
#include "search.h"
#include "algorithm/classes.h"
#include <limits>


int find_best_way(Vertex* arr, int N, int M, int x_start, int x_end)
{
    int counter;
    int y_start = 0;
    int y_end = N-1;

    int min_x, min_y;
    int min_path;

    arr[y_start*N+x_start].path_to = 0;
    while (true){
        // count visited values
        counter = 0;
        for (int i = 0; i < N; ++i){
            for (int j = 0; j < M; ++j){
                counter += (arr[i*N+j].visited == true);
            }
        }
        if (counter == N*M){
            return 0;
        }

        // find minimal value 
        min_path = std::numeric_limits<int>::max();
        for (int i = 0; i < N; ++i){
            for (int j = 0; j < M; ++j){
                if ((arr[i*N+j].path_to < min_path) and (arr[i*N+j].visited == false)){
                    min_path = arr[i*N+j].path_to;
                    min_x = j;
                    min_y = i;
                }
            }
        }

        // check neighbour 
        int current_weight = arr[min_y*N + min_x].weight;
        int current_path_to = arr[min_y*N + min_x].path_to;
        arr[min_y*N + min_x].visited = true;
        // left
            if ((min_x - 1) > -1){
                int left_path_to = arr[min_y*N + min_x - 1].path_to;
                if (std::min(left_path_to, current_path_to+current_weight) != left_path_to){
                    arr[min_y*N + min_x - 1].way = previous::right;
                }
                arr[min_y*N + min_x - 1].path_to = std::min(left_path_to, current_path_to+current_weight);
            }
        // right
            if((min_x + 1) < M){
                int right_path_to = arr[min_y*N + min_x + 1].path_to;
                if (std::min(right_path_to, current_path_to+current_weight) != right_path_to){
                    arr[min_y*N + min_x + 1].way = previous::left;
                }
                arr[min_y*N + min_x + 1].path_to = std::min(right_path_to, current_path_to+current_weight);
            }
        // down
            if ((min_y + 1) < N){
                int down_path_to = arr[(min_y + 1)*N + min_x].path_to;
                if (std::min(down_path_to, current_path_to+current_weight) != down_path_to){
                    arr[(min_y + 1)*N + min_x].way = previous::up;
                }
                arr[(min_y + 1)*N + min_x].path_to = std::min(down_path_to, current_path_to+current_weight);
            }
    }
    return 0;
}