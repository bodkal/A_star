cmake_minimum_required(VERSION 3.17)
project(test)

set(CMAKE_CXX_STANDARD 17)

add_executable(test main.cpp)
find_package(Python2 COMPONENTS Development NumPy)
target_include_directories(test  PRIVATE ${Python2_INCLUDE_DIRS} ${Python2_NumPy_INCLUDE_DIRS})
target_link_libraries(test  Python2::Python Python2::NumPy)
