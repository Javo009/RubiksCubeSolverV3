cmake_minimum_required(VERSION 3.28)
project(RubiksCubeSolverV1)

set(CMAKE_CXX_STANDARD 17)

add_executable(RubiksCubeSolverV1 main.cpp
        GenericRubiksCube.cpp
        GenericRubiksCube.h)
