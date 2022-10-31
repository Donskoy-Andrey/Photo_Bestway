#include <vector>
#include <fstream>


inline void draw(std::vector <int> &xs, std::vector <int> &ys){
    /*
    Run python script to draw polygon.
    */
    std::ofstream file;
    file.open("../data/txt/output.txt");
    for (int i = 0; i < xs.size(); ++i){
        file << xs[i] << " " << ys[i] << "\n";
    }
    file.close();
    std::string command = "python3 ./../src/drawing/draw.py";
    system(command.c_str());
}