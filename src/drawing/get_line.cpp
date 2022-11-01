#include <vector>
#include <iostream>
#include <limits>


int final_line(int* best_way, int N, int M, std::vector <int> &xs, std::vector <int> &ys){
    int check_i = N-1, check_j = M-1;
    int min_value;
    xs.push_back(check_j);
    ys.push_back(check_i);

    int left, right, down, up;
    while ((check_i != 0) or (check_j != 0)){
        left = std::numeric_limits<int>::max();
        right = std::numeric_limits<int>::max();
        up = std::numeric_limits<int>::max();

        if ((check_j != M-1) and (check_j != 0)){
            left = best_way[check_i*N+check_j-1];
            right = best_way[check_i*N+check_j+1];
            up = best_way[(check_i-1)*N+check_j];
            // std::cout << left << " " << right << " " << up << std::endl;
        }

        if (check_j == N-1){ // last column
            left = best_way[check_i*N+check_j-1];
            up = best_way[(check_i-1)*N+check_j];
            // std::cout << "Last column " << left << " " << up << std::endl;
        }

        if (check_j == 0){ // 1st column
            right = best_way[check_i*N+check_j+1];
            up = best_way[(check_i-1)*N+check_j];
            // std::cout << "1st column " << right << " " << up << std::endl;
        }

        if (check_i == 0){ // 1st row
            left = best_way[check_i*N+check_j-1];
            right = best_way[check_i*N+check_j+1];
            // std::cout << "1st row " << left << " " << right << std::endl;
        }

        min_value = std::min(left, std::min(right, up));
        if (min_value == best_way[check_i*N+check_j-1]){
            // std::cout << "Next step = LEFT" << std::endl;
            --check_j; // left
        }
        else if (min_value == best_way[(check_i-1)*N+check_j]){
            // std::cout << "Next step = UP" << std::endl;
            --check_i; // up
        }
        else if (min_value == best_way[check_i*N+check_j+1]){
            // std::cout << "Next step = RIGHT" << std::endl;
            ++check_j; // right
        }
        // std::cout << "New coordinates = "<< check_i << ", " << check_j << std::endl;
        xs.push_back(check_j);
        ys.push_back(check_i);
    }
    return 0;
}