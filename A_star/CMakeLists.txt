cmake_minimum_required(VERSION 3.17)
project(A_star)

set(CMAKE_CXX_STANDARD 17)

add_executable(A_star main.cpp grid.cpp grid.h utils.cpp utils.h A_star_lite.cpp A_star_lite.h)