cmake_minimum_required(VERSION 3.2)
project(road LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 17) 


include_directories(src)
include_directories(src/drawing)
include_directories(src/data_preparing)
include_directories(src/algorithm)

add_executable(
main src/main.cpp
src/drawing/run_py_script.h
src/data_preparing/open_file.h
src/data_preparing/open_file.cpp
src/algorithm/search.h
src/algorithm/search.cpp
src/algorithm/classes.h
src/drawing/get_line.cpp
src/drawing/get_line.h
)
