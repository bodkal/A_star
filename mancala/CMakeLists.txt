cmake_minimum_required(VERSION 3.17)
project(mancala)

set(CMAKE_CXX_STANDARD 17)

add_executable(mancala main.cpp utils.cpp utils.h game.cpp game.h)