cmake_minimum_required(VERSION 3.28)
project(RubiksCubeSolverV1)

set(CMAKE_CXX_STANDARD 17)

add_executable(RubiksCubeSolverV1
        main.cpp
        Model/GenericRubiksCube.cpp
        Model/GenericRubiksCube.h
        Model/RubiksCube3dArray.cpp
        Model/RubiksCube1dArray.cpp
        Model/RubiksCubeBitboard.cpp
        Model/PatternDatabase/PatternDatabase.h
        Solver/DFSSolver.h
        Solver/BFSSolver.h
        Solver/IDDFSSolver.h
        Solver/IDAstarSolver.h
        PatternDatabases/CornerDBMaker.h
        PatternDatabases/CornerPatternDatabase.h
        PatternDatabases/math.h
        PatternDatabases/NibbleArray.h
        PatternDatabases/PatternDatabase.h
        PatternDatabases/PermutationIndexer.h
        PatternDatabases/CornerDBMaker.cpp
        PatternDatabases/CornerPatternDatabase.cpp
        PatternDatabases/math.cpp
        PatternDatabases/NibbleArray.cpp
        PatternDatabases/PatternDatabase.cpp
)
