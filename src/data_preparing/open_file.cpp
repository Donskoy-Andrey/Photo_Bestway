#include <fstream>
#include <vector>
#include <iostream>
#include <sstream>
#include <string>
#include "open_file.h"


int open_file(std::string filepath, int *arr, int N, int M)
{
    std::ifstream file(filepath);
    int current_line = 0;
    std::string line;
    while(std::getline(file, line))
    {
        std::stringstream line_stream;
        std::vector <double> coordinates;
        line_stream << line;
        std::string point;
        while(std::getline(line_stream, point, ' ')){
        
            try
            {
                coordinates.push_back(std::stod(point));
            }
            catch (std::invalid_argument){
                std::cerr << "Not valid file" << std::endl;
                return -1;
            }
        }
        for (int j = 0; j < M; ++j){
            arr[current_line*N+j] = coordinates[j];
        }
        ++current_line;
    }
    return 0;
}