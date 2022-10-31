#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <algorithm>

void cmd(std::vector <int> &xs, std::vector <int> &ys){
    /*
    Run python script to draw polygon.
    */
    std::ofstream file;
    file.open("../result.txt");
    for (int i = 0; i < xs.size(); ++i){
        file << xs[i] << " " << ys[i] << "\n";
    }
    file.close();
    std::string command = "python3 ./../draw.py ";
    system(command.c_str());
}


int main(){
    std::ifstream file("../map.txt");
    std::string line;
    int N = 5;
    int arr[N][N];
    int best_way[N][N];
    int i = 0;

    for (int i = 0; i < N; ++i){
        for (int j = 0; j < N; ++j){
            best_way[i][j] = 300;
        }
    }

    // read file
    while(std::getline(file, line))
    {
        std::vector <double> coordinates;
        std::stringstream line_stream;
        line_stream << line;
        std::string point;
        while(std::getline(line_stream, point, ' ')) 
        {
            try
            {
                coordinates.push_back(std::stod(point));
            }
            catch (std::invalid_argument){
                return -1;
            }
        }
        for (int j = 0; j < N; ++j){
            arr[i][j] = coordinates[j];
        }
        ++i;
    }

    int value, left, right, down, up;
    best_way[0][0] = 0;
    for (int i = 0; i < N; ++i){
        for (int j = 0; j < N; ++j){
            value = best_way[i][j];
            // std::cout << i << " " << j << std::endl;
            if ((i == 0) and (j == 0)){ // best_way[0][0] = 0
                best_way[i][j+1] = arr[i][j+1];
                best_way[i+1][j] = arr[i+1][j];
                best_way[i][j] = value; 
                continue;
            } 

            if ((j != 0) and (j != N-1) and (i != N-1)){
                left = arr[i][j-1];
                right = arr[i][j+1];
                down = arr[i+1][j];

                best_way[i][j-1] = std::min(best_way[i][j-1], value + left);
                best_way[i][j+1] = std::min(best_way[i][j+1], value + right);
                best_way[i+1][j] = std::min(best_way[i+1][j], value + down);
                
            }

            if ((j == 0) and (i != N-1)){ // 1st column
                right = arr[i][j+1];
                down = arr[i+1][j];

                best_way[i][j+1] = std::min(best_way[i][j+1], value + right);
                best_way[i+1][j] = std::min(best_way[i+1][j], value + down);
            }

            if ((j == N-1) and (i != N-1)) { // last column
                left = arr[i][j-1];
                down = arr[i+1][j];
                
                best_way[i][j-1] = std::min(best_way[i][j-1], value + left);
                best_way[i+1][j] = std::min(best_way[i+1][j], value + down);
            }

            if ((i == N-1) and (j != 0) and (j != N-1)){ // last row
                left = arr[i][j-1];
                right = arr[i][j+1];
                best_way[i][j-1] = std::min(best_way[i][j-1], value + left);
                best_way[i][j+1] = std::min(best_way[i][j+1], value + right);
            }
        }
    }    
    int check_i = N-1, check_j = N-1;
    int min_value;
    std::vector <int> xs = {check_j};
    std::vector <int> ys = {check_i};

    while ((check_i != 0) or (check_j != 0)){
        left = 300;
        right = 300;
        up = 300;

        if ((check_j != N-1) and (check_j != 0)){
            left = best_way[check_i][check_j-1];
            right = best_way[check_i][check_j+1];
            up = best_way[check_i-1][check_j];
        }

        if (check_j == N-1){ // last column
            left = best_way[check_i][check_j-1];
            up = best_way[check_i-1][check_j];
            // std::cout << "Last column " << left << " " << up << std::endl;
        }

        if (check_j == 0){ // 1st column
            right = best_way[check_i][check_j+1];
            up = best_way[check_i-1][check_j];
            // std::cout << "1st column " << right << " " << up << std::endl;
        }

        if (check_i == 0){ // 1st row
            left = best_way[check_i][check_j-1];
            right = best_way[check_i][check_j+1];
            // std::cout << "1st row " << left << " " << right << std::endl;
        }


        min_value = std::min(left, std::min(right, up));
        // std::cout << min_value << std::endl;
        if (min_value == best_way[check_i][check_j-1]){
            // std::cout << "Next step = LEFT" << std::endl;
            --check_j; // left
        }
        else if (min_value == best_way[check_i-1][check_j]){
            // std::cout << "Next step = UP" << std::endl;
            --check_i; // up
        }
        else if (min_value == best_way[check_i][check_j+1]){
            // std::cout << "Next step = RIGHT" << std::endl;
            ++check_j; // right
        }
        // std::cout << "New coordinates = "<< check_i << ", " << check_j << std::endl;
        // std::cout << std::endl;
        xs.push_back(check_j);
        ys.push_back(check_i);
    }

    // check matrix
    for (int i = 0; i < N; ++i)
    {
        for (int j = 0; j < N; ++j)
        {
            std::cout << best_way[i][j] << " ";
        }
        std::cout << std::endl;
    }
    
    cmd(xs, ys);

    return 0;
}