#include <fstream>
#include <vector>
#include <iostream>
#include <sstream>
#include <string>
#include "open_file.h"
#include "algorithm/classes.h"


int open_file(std::string filepath, Vertex *arr, int N, int M)
{
    std::ifstream file(filepath);
    int current_line = 0;
    std::string line;
    while(std::getline(file, line))
    {
        std::stringstream line_stream;
        std::vector <int> coordinates;
        line_stream << line;
        std::string point;
        while(std::getline(line_stream, point, ' ')){
        
            try
            {
                coordinates.push_back(std::stoi(point));
            }
            catch (std::invalid_argument){
                std::cerr << "Not valid file" << std::endl;
                return -1;
            }
        }
        for (int j = 0; j < M; ++j){
            arr[current_line*N+j].weight = coordinates[j];
        }
        ++current_line;
    }
    return 0;
}