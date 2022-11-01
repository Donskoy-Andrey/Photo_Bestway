#pragma once
#include <limits>

enum previous{
    left = 0,
    right = 1,
    up = 2,
    none = 3,
};
struct Vertex{
    bool visited = false;
    int path_to = std::numeric_limits<int>::max();
    int weight = std::numeric_limits<int>::max();
    previous way = previous::none;
};