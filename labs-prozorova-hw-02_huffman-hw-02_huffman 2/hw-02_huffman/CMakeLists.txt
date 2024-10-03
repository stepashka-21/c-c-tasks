cmake_minimum_required(VERSION 3.22.1)
project(hw-02_huffman)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_FLAGS -O3)

include_directories(include)
include_directories(src)
include_directories(test)

add_executable(hw-02_huffman
        include/huff_archiver.h
        include/huff_tree.h
        src/huff_archiver.cpp
        src/huff_tree.cpp
        src/main.cpp
)

add_executable(hw-02_test
        include/huff_archiver.h
        include/huff_tree.h
        src/huff_archiver.cpp
        src/huff_tree.cpp
        test/doctest.h
        test/test.cpp
)

