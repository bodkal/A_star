cmake_minimum_required(VERSION 3.17)
project(D_star_lite_test)

set(CMAKE_CXX_STANDARD 17)

add_executable(D_star_lite_test main.cpp utils.cpp utils.h grid.cpp grid.h grid.cpp grid.h priority_queue.cpp priority_queue.h d_star_lite.cpp d_star_lite.h)
