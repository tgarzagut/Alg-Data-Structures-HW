#include "solve.h"
#include "vertex.h"
#include <string>
#include <unordered_set>
#include <queue>

#include <iostream>
using namespace std;

class Vertex{
    public:
        Vertex(int r, int c, int w){
            row = r;
            col = c;
            weight = w;
            marked = false;
        }
        Vertex() {
            row = 0;
            col = 0;
            weight = 1;
            marked = false;
        }
        int row;
        int col;
        int weight;
        Vertex* breadcrumb;
        bool marked;
        vector<Vertex*> neighbors;
                
};
Vertex* vertexFromindex(int r, int c, unordered_map<string, Vertex*>& m){
    string key = to_string(r) + "," + to_string(c);
        if(m.count(key) == 1)   {
            return m[key];
        }
        return nullptr;
}
void makeNeighbor(int row1, int col1, int row2, int col2,  unordered_map<string, Vertex*>& m){
        Vertex* p1 = vertexFromindex(row1, col1, m);
        Vertex* p2 = vertexFromindex(row2, col2, m);
        if(p1 && p2 && p1 != p2){
            p1->neighbors.push_back(p2);
        }
}

bool isValid(Vertex& p, int numRows, int numCols){
    return (p.row >= 0 && p.row < numRows && p.col >= 0 && p.col < numCols);
}

void shortestPath(string& maze, Vertex* start, Vertex* end, int numColumns){
    Vertex* sPtr = start;
    Vertex* ePtr = end;
    Vertex* current = ePtr;
    unordered_set<Vertex*> visited;
while (current != nullptr) {
    visited.insert(current);
    current = current->breadcrumb;
}
}

void BFS(string& maze, Vertex* start, Vertex* end, string& solution){
    queue<Vertex*>Q;
    start->marked = true;
    Q.push(start);
    while(!Q.empty()){
        Vertex* curr = Q.front();
        Q.pop();
        for(auto neigh: curr->neighbors){
            if(!neigh ->marked){
                neigh ->marked = true;
                Q.push(neigh);
                neigh->breadcrumb = curr;
            }
        }
    }
}
void createEdges(string& maze, int numRows, int numColumns, unordered_map<string, Vertex*>& m){
    for(int i = 0; i < numRows; i++){
        for(int j = 0; j < numColumns; j++){
            Vertex* current = vertexFromindex(i, j, m);
            if(current){
                if(i > 0 && vertexFromindex(i-1, j,m)){
                    makeNeighbor(i, j, i-1, j, m);
                }
                if((i < numRows -1) && vertexFromindex(i+1, j, m)){
                    makeNeighbor(i , j, i+1, j, m);
                }
                if (j > 0 && vertexFromindex(i, j-1, m)){
                    makeNeighbor(i, j, i, j-1, m);
                }
                if((j < numColumns -1) && vertexFromindex(i, j+1, m)){
                    makeNeighbor(i, j, i, j+1, m);
                }
            }
        }
    }
}

void connectPortals(vector<Vertex*> list){
    for(int i=0; i<list.size(); i++){
        for(int j=i+1; j<list.size(); j++){
            if(list[i]->weight == list[j]->weight){
                list[i]->neighbors.push_back(list[j]);
                list[j]->neighbors.push_back(list[i]);
            }
        }
    }
}
int findRows(string& maze){
    int h = 0;
    for(int i=0;i < maze.size(); i++){
        if(maze[i]== '\n'){
            h++;
        }
    }
    return h;
}
int findCols(string& maze){
    for(int i=0;i < maze.size(); i++){
        if(maze[i] == '\n'){
            return i;
        }
    }
    return -1;
}
void addVertex(Vertex* v, unordered_map<string, Vertex*>& m){
    string key = to_string(v->row) + "," + to_string(v->col);
    m[key] = new Vertex(v->row, v->col, v->weight);
}
string cat(const vector<string>& vec) {
    string result;
    for (const auto& s : vec) {
        result += s;
        result += "\n";
    }
    return result;
}
void findStartEnd(string& maze, Vertex* start, Vertex* end, int rows, int cols){

}
bool onEdge(int rows, int cols, Vertex* v){
 return (v->row == 0 || v->col == 0 || v->row == rows - 1 || v->col == cols - 1);
}
string solve(string maze){
    MinPriorityQueue<Vertex> q;
    unordered_map<string, Vertex*> m;
    vector<string> mazeVector;
    vector<Vertex*> portals;
    int numCols= findCols(maze);
    int numRows = findRows(maze);

    int pos = 0;
    while ((pos = maze.find('\n')) != string::npos)
    {
        mazeVector.push_back(maze.substr(0, pos));
        maze.erase(0, pos + 1);
    }

    string solution = maze;

    Vertex* start = nullptr;
    Vertex* end = nullptr;

    for (int i = 0; i < mazeVector.size(); ++i){
        for (int j = 0; j < mazeVector[i].size(); ++j){
            if (mazeVector[i][j] == ' '){
                Vertex* newv = new Vertex(i, j, 1);
                addVertex(newv, m);
                if(onEdge(numRows,numCols,newv) && start==nullptr){
                    start = newv;
                }
                else if(onEdge(numRows,numCols,newv) && end==nullptr){
                    end = newv;
                }
            }
            else if(mazeVector[i][j] != '\n' && mazeVector[i][j] != '#'){
                Vertex* newv = new Vertex(i, j, (int)mazeVector[i][j]);
                addVertex(newv, m);
                if(onEdge(numRows,numCols,newv) && start==nullptr){
                    start = newv;
                }
                else if(onEdge(numRows,numCols,newv) && end==nullptr){
                    end = newv;
                }
            }
        }
    }
    createEdges(maze, numRows, numCols, m);
    connectPortals(portals);
    BFS(maze, start, end, solution);
    shortestPath(solution, start, end, numCols);
    return solution;
}