cmake_minimum_required(VERSION 3.17)
project(A_star)

set(CMAKE_CXX_STANDARD 17)

##include_directories("/home/koby/Desktop/matplotlib-cpp/")


add_executable(A_star_lite main.cpp grid.cpp grid.h utils.cpp utils.h A_star_lite.cpp A_star_lite.h)

find_package(Python2 COMPONENTS Development NumPy)
target_include_directories(A_star_lite  PRIVATE ${Python2_INCLUDE_DIRS} ${Python2_NumPy_INCLUDE_DIRS})
target_link_libraries(A_star_lite  Python2::Python Python2::NumPy)


