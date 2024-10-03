cmake_minimum_required(VERSION 3.22.1)
project(lab-13_array)

set(CMAKE_CXX_STANDARD 14)

include_directories(include)

add_executable(lab-13_array
        include/my_array.h
        README.md
        src/main.cpp)
