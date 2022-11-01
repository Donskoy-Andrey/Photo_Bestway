#include <iostream>
#include <vector>
#include "run_py_script.h"
#include "data_preparing/open_file.h"
#include "algorithm/search.h"
#include "drawing/get_line.h"


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
    int arr[N][M];
    std::string filepath = "../data/txt/input.txt"; 
    open_file(filepath, &arr[0][0], N);

    // Find best ways
    int best_way[N][N];
    find_best_way(&best_way[0][0], &arr[0][0], N);

/*
    // Check results of array
    for (int i = 0; i < N; ++i){
        for (int j = 0; j < N; ++j){
            std::cout << best_way[i][j] << " ";
        }
        std::cout << std::endl;
    }
*/

    // Draw line
    std::vector <int> xs;
    std::vector <int> ys;
    final_line(&best_way[0][0], N, xs, ys);
    draw(xs, ys, file_input, file_output);

    return 0;
}