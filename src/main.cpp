#include <iostream>
#include <lodepng.h>
#include <vector>
#include <cstdint>
#include <string>
#include <iostream>
#include <vector>
#include <limits>
#include "drawing/run_py_script.h"
#include "data_preparing/open_file.h"
#include "algorithm/search.h"
#include "drawing/get_line.h"
#include "algorithm/classes.h"
#include <iterator>
#include <algorithm>


using namespace std;

void decodeFromPng(std::vector<unsigned char>& image, const char* filename, unsigned height, unsigned width) {
    /*
     * Функция для чтения png файла
     */
    std::vector<unsigned char> png;
    //load and decode
    unsigned error = lodepng::load_file(png, filename);
    if(!error) error = lodepng::decode(image, width, height, png);

    //if there's an error, display it
    if(error) std::cout << "decoder error " << error << ": " << lodepng_error_text(error) << std::endl;

    //the pixels are now in the vector "image", 4 bytes per pixel, ordered RGBARGBA..., use it as texture, draw it, ... 
}

void getBlueChannel(const std::vector<unsigned char>& image, int** arr, int rows, int cols) {
    /*
     * Функция, которая выделяет синий канал из одномерного вектора и
     * заполняет им двумерный массив
     */
    for (int i = 2, j = 0, k = 0; i < image.size(); i += 4, ++k) {
        if (k == cols) {
            k = 0; // обнуляем номер столбца
            ++j; // увеличиваем номер строки
        }
        arr[j][k] = int(image[i]);
    }
}
void printArray(int** arr, int rows, int cols) { 
    /*
     * Функция для вывода массива в консоль
     */
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j)
            cout << arr[i][j] << " ";
        cout << endl;    
    }
}

void drawPath(const vector<int>& path, vector<unsigned char>& image, int rows, int cols, const char* output_file) {
    int i = 0, j = -1;
    int previousPoint = -1;
    for (auto& e : path) {
        if (previousPoint == e)
            ++i;
        else
            j = e;
        previousPoint = e;
        // draw red path R = 255, G = 0, B = 0
        int index = (i*cols + j)*4;
        image[index] = (unsigned char)255;
        image[++index] = (unsigned char)0;
        image[++index] = (unsigned char)0;
    }


    
    //Encode the image
    unsigned error = lodepng::encode(output_file, image, cols, rows);

    //if there's an error, display it
    if(error) std::cout << "encoder error " << error << ": "<< lodepng_error_text(error) << std::endl;
}

void findOptimalPath(int** arr, vector<int>& path, int x_i, int x_f, int rows, int cols) {
}

int main(int argc, char* argv[]) {
    // $ ./main ../data/images/input.png 100 100 0 99 ../data/images/output.png
    
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
    std::vector <int> path;
    std::vector <int> ys;
    final_line(&arr[0][0], path, ys, N, M, x_start, x_end);    
    // draw(xs, ys, file_input, file_output);
    std::reverse(path.begin(), path.end());

    char *input_file = argv[1], *output_file = argv[6];
    
    std::vector<unsigned char> image; 
    decodeFromPng(image, input_file, N, M); 
    drawPath(path, image, N, M, output_file);
}

