#include <iostream>
#include <vector>
#include "run_py_script.h"
#include "data_preparing/open_file.h"
#include "algorithm/search.h"
#include "drawing/get_line.h"


int main(int argc, char **argv){
    int N = 5;
    
    if (argc != 2){
        std::cerr << "Incorrect amount of the params." << std::endl;
        return -1;
    }

    // Read file
    int arr[N][N];
    std::string filepath = argv[1]; 
    open_file(filepath, &arr[0][0], N);

    // Find best ways
    int best_way[N][N];
    find_best_way(&best_way[0][0], &arr[0][0], N);

    // Check result array
    for (int i = 0; i < N; ++i){
        for (int j = 0; j < N; ++j){
            std::cout << best_way[i][j] << " ";
        }
        std::cout << std::endl;
    }

    // Draw line
    std::vector <int> xs;
    std::vector <int> ys;
    final_line(&best_way[0][0], N, xs, ys);
    draw(xs, ys);

    return 0;
}