cmake_minimum_required(VERSION 3.19)
project(hw3)

set(CMAKE_CXX_FLAGS "-std=c++1z -Wconversion -Wall -Werror -Wextra -pedantic")

add_executable(hw3
        island.cpp
        randomcase.cpp)
