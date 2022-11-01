#include <vector>
#include <fstream>
#include <iostream>
#include <string>


inline void draw(std::vector <int> &xs, std::vector <int> &ys, std::string file_input, std::string file_output){
    /*
    Run python script to draw polygon.
    */
    std::ofstream file;
    file.open("../data/txt/output.txt");
    for (int i = 0; i < xs.size(); ++i){
        file << xs[i] << " " << ys[i] << "\n";
    }
    file.close();
    std::string command = "python3 ../src/drawing/draw.py " + file_input + " " + file_output;
    system(command.c_str());
}


inline void image_to_array(std::string path_input){
    /*
    Run python script to get txt-array from the photo.
    */
    std::string command = "python3 ../src/drawing/image.py " + path_input;
    system(command.c_str());
}
