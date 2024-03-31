
#include "solve.h"
#include <iostream>
//iostream is used ONLY for visual purposes and is not 
//used for solving the maze

using namespace std;

// For the mandatory running time, assume that the time for
// operations of queue, unordered_set, and map are O(1). 
// (They are for average-case, but not worst-case).
//
// For the mandatory running time below, s is the length of 
// the input string representing the maze.
// 
// For a complete description of the maze string 
// and maze solution formats, see the assignment pdf.


// Returns a string representing a shortest solution to the maze.
// Has undefined behavior if the maze is not valid or has no solution.
//
// Must run in O(s) time.

//modified vertex.h to include breadcrumb and location of vertex
class Vertex{
    public:

    Vertex(int r, int c, int i){
        row = r;
        col = c;
        in = i;
        breadcrumb = nullptr;
    }
    // Corresponding row and column location in maze
    int row;
    int col;
    int in;
    Vertex* breadcrumb;
    // List of neighboring vertices
    vector<Vertex*> neighs;
};

class mazeSolver{
    void findNeighbors(Vertex* v){

    }
};

void print(string maze){
    for(int i=0; i < maze.size(); i++){
        cout << maze[i];
    }
    cout << endl;
}

string solve(string maze){
    cout << "unsolved: " << endl;
    print(maze);

    //code

    cout << "solved: " << endl;
    print(maze);

    return "";
}