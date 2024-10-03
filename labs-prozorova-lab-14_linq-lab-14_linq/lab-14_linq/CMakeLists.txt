cmake_minimum_required(VERSION 3.22.1)
project(lab_14_linq)

set(CMAKE_CXX_STANDARD 14)

include_directories(include)

add_executable(lab-14_linq
        include/linq.hpp
        src/test.cpp
        # src/smoke_test.cpp
        # minimal_smoke_test.cpp
)
