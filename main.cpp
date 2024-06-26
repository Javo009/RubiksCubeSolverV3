#include<bits/stdc++.h>
#include "Model/RubiksCube3dArray.cpp"
using namespace std;


int main() {
    RubiksCube3dArray object3DArray;
    object3DArray.print();

    RubiksCube3dArray cube1;
    // RubiksCube3dArray cube2;
    // if(cube1==cube2) cout << "yoyo";
    cube1.l();
    cube1.randomShuffleCube(4);
    cube1.print();
    // print(cube1);
}
