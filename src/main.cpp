#include <iostream>
#include <vector>
#include <limits>
#include "run_py_script.h"
#include "data_preparing/open_file.h"
#include "algorithm/search.h"
#include "drawing/get_line.h"
#include "algorithm/classes.h"


int main(int argc, char **argv){
    // $ ./main ./../data/images/input.png 100 100 0 99 ../data/images/output.png
    
    std::string file_input;
    std::string file_output;
    int N, M, x_start, x_end;
    if (argc != 7){
        std::cerr << "Incorrect amount of the params." << std::endl;
        return -1;
    }
    try{
        file_input = argv[1];
        N = std::stoi(argv[2]);
        M = std::stoi(argv[3]);
        x_start = std::stoi(argv[4]);
        x_end = std::stoi(argv[5]);
        file_output = argv[6];

    } catch (std::exception) {
        std::cerr << "Can't convert input params." << std::endl;
        return -1;
    }

    image_to_array(file_input);

    // Read file
    Vertex arr[N][M];
    std::string filepath = "../data/txt/input.txt"; 
    if (open_file(filepath, &arr[0][0], N, M) < 0){
        return -1;
    };

    // Find best ways
    find_best_way(&arr[0][0], N, M, x_start, x_end);

/*
    // Check results of array
    for (int i = 0; i < N; ++i){
        for (int j = 0; j < M; ++j){
            std::cout << arr[i][j].path_to << " ";
        }
        std::cout << std::endl;
    }
*/

    // Draw line
    std::vector <int> xs;
    std::vector <int> ys;
    final_line(&arr[0][0], xs, ys, N, M, x_start, x_end);
    draw(xs, ys, file_input, file_output);

    return 0;
}