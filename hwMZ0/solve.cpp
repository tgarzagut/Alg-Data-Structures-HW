#include "solve.h"
#include "vertex.h"
#include <queue>
#include <unordered_set>
#include <unordered_map>
#include <vector>
#include <iostream>

using namespace std;

class Vertex{
    public:
        Vertex(int r, int c){
            row = r;
            col = c;
        }
        Vertex() {
            row = 0;
            col = 0;
        }
        int row;
        int col;
                
};

bool isValid(Vertex& p, int numRows, int numCols){
    return (p.row >= 0 && p.row < numRows && p.col >= 0 && p.col < numCols);
}

void BFS(vector<string>& maze, Vertex start, Vertex end, vector<string>& solution){
    int numRows = maze.size();
    int numCols = maze[0].size();

    queue<Vertex> q;
    unordered_set<int> visited;
    unordered_map<int, Vertex> parent;

    q.push(start);
    visited.insert(start.row * numCols + start.col);
    while (!q.empty()){
        Vertex current = q.front();
        q.pop();
        if (current.row == end.row && current.col == end.col){
            Vertex path = end;
            while (path.row != start.row || path.col != start.col){
                solution[path.row][path.col] = 'o';
                path = parent[path.row * numCols + path.col];
            }
            solution[start.row][start.col] = 'o';
            return;
        }

        vector<Vertex> neighbors;
        if (current.row - 1 >= 0)
            neighbors.push_back(Vertex(current.row - 1, current.col));
        if (current.row + 1 < numRows)
            neighbors.push_back(Vertex(current.row + 1, current.col));
        if (current.col - 1 >= 0)
            neighbors.push_back(Vertex(current.row, current.col - 1));
        if (current.col + 1 < numCols)
            neighbors.push_back(Vertex(current.row, current.col + 1));

        for (auto& neighbor : neighbors){
            if (isValid(neighbor, numRows, numCols) && maze[neighbor.row][neighbor.col] == ' ' && visited.find(neighbor.row * numCols + neighbor.col) == visited.end()){
                q.push(neighbor);
                visited.insert(neighbor.row * numCols + neighbor.col);
                parent[neighbor.row * numCols + neighbor.col] = current;
            }
        }
    }
}
string solve(string maze){
    vector<string> mazeVector;
    auto pos = 0;
    while ((pos = maze.find('\n')) != string::npos)
    {
        mazeVector.push_back(maze.substr(0, pos));
        maze.erase(0, pos + 1);
    }

    vector<string> solution = mazeVector;

    Vertex start(-1, -1), end(-1, -1);
    for (int i = 0; i < mazeVector.size(); ++i){
        for (int j = 0; j < mazeVector[i].size(); ++j){
            if (mazeVector[i][j] == ' '){
                if (i == 0 || i == mazeVector.size() - 1 || j == 0 || j == mazeVector[i].size() - 1){
                    if (start.row == -1)
                        start = Vertex(i, j);
                    else
                        end = Vertex(i, j);
                }
            }
        }
    }
    BFS(mazeVector, start, end, solution);
    string result;
    for (size_t i = 0; i < solution.size(); ++i) {
        auto& row = solution[i];
        result += row + '\n';
    }
    return result;
}