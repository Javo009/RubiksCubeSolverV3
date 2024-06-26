//
// Created by Aaryan Javalekar's Laptop Lenovo Legion 5 on 18-06-2024.
//
// This main function only shows the implementation of IDA* Solver using Bitboard representation and the rest of the part is commented out

#include <bits/stdc++.h>
// #include "Model/RubiksCube3dArray.cpp"
// #include "Model/RubiksCube1dArray.cpp"
#include "Model/RubiksCubeBitboard.cpp"
// #include "Solver/DFSSolver.h"
// #include "Solver/BFSSolver.h"
// #include "Solver/IDDFSSolver.h"
#include "Solver/IDAstarSolver.h"
// #include "PatternDatabases/CornerDBMaker.h"


using namespace std;

int main() {
    // RubiksCube3dArray cube;
    // RubiksCube1dArray cube;
    RubiksCubeBitboard cube;

    cube.print();

    if (cube.isSolved()) cout << "SOLVED\n\n";
    else cout << "NOT SOLVED\n\n";

    vector<GenericRubiksCube::MOVE> moves = cube.randomShuffleCube(14);
    cube.print();

    for(auto it: moves) cout << cube.getMove(it) << " ";
    cout << "\n";


    string fileName = R"(C:\Users\Lenovo\CLionProjects\RubiksCubeSolverV1\Databases\yoyo.txt)";


    // DFSSolver<RubiksCubeBitboard, HashBitboard> dfsSolver(cube);
    // IDDFSSolver<RubiksCubeBitboard, HashBitboard> iddfssolver(cube);
    // BFSSolver<RubiksCubeBitboard, HashBitboard> bfsSolver(cube);
    IDAstarSolver<RubiksCubeBitboard, HashBitboard> idastarsolver(cube,fileName);


    vector<GenericRubiksCube::MOVE> solves = idastarsolver.solve();
    // vector<GenericRubiksCube::MOVE> solves = iddfssolver.solve();
    // vector<GenericRubiksCube::MOVE> solves = bfsSolver.solve();
    // vector<GenericRubiksCube::MOVE> solves = dfsSolver.solve();

    idastarsolver.rubiksCube.print();
    // //
    for(auto it: solves) cout << cube.getMove(it) << " ";
    cout << "\n";

   // Code to create Corner Database
    // CornerDBMaker dbMaker(fileName, 0x99);
    // dbMaker.bfsAndStore();


    cout << "yoyo"; //tells us everything went right
    return 0;
}