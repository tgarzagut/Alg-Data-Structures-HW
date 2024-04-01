
#include "solve.h"

//checklist
// [x] vertices
// [x] edges
// [x] start
// [x] end
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

//modified vertex.h to include breadcrumb of vertex
class Vertex{
    public:

    Vertex(int r, int c){
        row = r;
        col = c;
        breadcrumb = nullptr;
    }
    // Corresponding row and column location in maze
    int row;
    int col;
    Vertex* breadcrumb;
    // List of neighboring vertices
    vector<Vertex*> neighs;
};

class mazeSolver{
    void findNeighbors(Vertex* v){
        //code
    }
    //run through every index of maze string and if " " then identify neighbors
    //maybe bool for start so as to identify it.
    //BFS ? approach

};

bool onEdge(int rows, int cols, Vertex* v){
    return (v->row == 0 || v->col == 0 || v->row == rows - 1 || v->col == cols - 1);
}

string solve(string maze){
    int ver_rows = 0;
    int ver_cols = 0;
    vector<Vertex*> vertices;
    Vertex* start;
    Vertex* end;

    //find width
    int maze_rows = 0;
    for(int i = 0;i < maze.size(); i++){
        maze_rows++;
        if(maze[i] == '\n'){ 
          break;
        }
    }
    //find heigth
    int maze_cols = 0;
    for(int j=0;j < maze.size(); j++){
        if(maze[j] == '\n'){
            maze_cols++;
            break;
        }
    }

    for(int i=0;i<maze.size(); i++){
        if(maze[i] == ' '){
            Vertex *newVertex = new Vertex(ver_rows,ver_cols);
            vertices.push_back(newVertex);
            ver_rows++;
            if(start == nullptr && onEdge(maze_rows, maze_cols, newVertex)){
                start = newVertex;
            }
            else if(end == nullptr && onEdge(maze_rows, maze_cols, newVertex)){
                end = newVertex;
            }
        }
        else if(maze[i] == '\n'){
            ver_rows = 0;
            ver_cols++;
        }
    }

    return "";
}