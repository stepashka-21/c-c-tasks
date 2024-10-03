cmake_minimum_required(VERSION 3.22.1)
project(lab-12_exceptions)

set(CMAKE_CXX_STANDARD 14)

include_directories(include)

add_executable(lab-12_exceptions
        include/matrix.h
        src/matrix.cpp
        src/main.cpp
        README.md)
