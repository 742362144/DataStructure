cmake_minimum_required(VERSION 3.7)
project(DataStructure)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES library.cpp library.h B2017.cpp graphcopy.cpp DP.cpp 2015.cpp LCS.cpp sort.cpp file.cpp)
add_library(untitled ${SOURCE_FILES})


add_executable(B2017 B2017.cpp)
add_executable(C2017 C2017.cpp)
add_executable(DP DP.cpp)
add_executable(graph graph.cpp)
add_executable( sort sort.cpp)
add_executable( file file.cpp)