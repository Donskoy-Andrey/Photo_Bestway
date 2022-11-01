#include <vector>
#include <iostream>
#include <limits>
#include "algorithm/classes.h"


int final_line(Vertex* arr, std::vector <int> &xs, std::vector <int> &ys, 
int N, int M, int x_start, int x_end){
    int current_x = x_end;
    int current_y = N-1;
    xs.push_back(current_x);
    ys.push_back(current_y);

    while ((current_x != x_start) or (current_y != 0))
    {
        // std::cout << current_y << " " << current_x << std::endl;
        auto way = arr[current_y*N+current_x].way;
        if (way == previous::left){
            --current_x;
            // std::cout << "1st " << current_x << current_y << std::endl;
        } else if (way == previous::right){
            ++current_x;
            // std::cout << "2nd " << current_x << current_y << std::endl;
        } else if (way == previous::up){
            --current_y;
            // std::cout << "3rd " << current_x << current_y << std::endl;
        } else {
            return 0;
        }
        xs.push_back(current_x);
        ys.push_back(current_y);
    }
    return 0;
}