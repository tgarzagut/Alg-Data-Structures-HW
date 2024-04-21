#include "solve.h"
#include <vector>
#include <unordered_map>
#include <utility>

#include <string>

using namespace std;
#include <iostream>

class Vertex {
public:
    int row, col;
    Vertex(int r = 0, int c = 0) : row(r), col(c) {}
    bool operator==(const Vertex& other) const {
        return row == other.row && col == other.col;
    }
};

namespace std {
    template <>
    struct hash<Vertex> {
        size_t operator()(const Vertex& v) const {
            return hash<int>()(v.row) ^ hash<int>()(v.col << 1); // Shift and XOR for simple hashing
        }
    };
}

class VertexHash {
public:
    size_t operator()(const Vertex& v) const {
        return std::hash<Vertex>()(v);
    }
};

bool isValid(const Vertex& p, int numRows, int numCols) {
    return p.row >= 0 && p.row < numRows && p.col >= 0 && p.col < numCols;
}

string solve(const string& inputMaze) {
    stringstream ss(inputMaze);
    string line;
    vector<string> maze;
    while (getline(ss, line)) {
        maze.push_back(line);
    }
    int numRows = maze.size();
    int numCols = maze[0].size();

    unordered_map<Vertex, vector<pair<Vertex, int> >, VertexHash> adjList;
    MinPriorityQueue<Vertex> pq;
    unordered_map<Vertex, int, VertexHash> dist;
    unordered_map<int, Vertex> portalMap;

    for (int r = 0; r < numRows; r++) {
        for (int c = 0; c < numCols; c++) {
            Vertex current(r, c);
            if (maze[r][c] != '#') {
                if (isdigit(maze[r][c])) {
                    int weight = maze[r][c] - '0';
                    if (portalMap.find(weight) != portalMap.end()) {
                        Vertex portal = portalMap[weight];
                        adjList[current].push_back(make_pair(portal, weight));
                        adjList[portal].push_back(make_pair(current, weight));
                    } else {
                        portalMap[weight] = current;
                    }
                }
                vector<Vertex> possibleMoves;  // Removed initializer list usage
                possibleMoves.push_back(Vertex(r+1, c));
                possibleMoves.push_back(Vertex(r, c+1));
                possibleMoves.push_back(Vertex(r-1, c));
                possibleMoves.push_back(Vertex(r, c-1));
                for (const Vertex& move : possibleMoves) {
                    if (isValid(move, numRows, numCols) && maze[move.row][move.col] != '#') {
                        adjList[current].push_back(make_pair(move, 1));
                    }
                }
            }
        }
    }

    Vertex start(0, 0);  // Assuming the start is always top-left corner
    pq.push(start, 0);  // Initialize PQ with the start vertex
    dist[start] = 0;

    while (!pq.isEmpty()) {
        Vertex u = pq.front();
        pq.pop();
        int currentDist = dist[u];

        for (const auto& edge : adjList[u]) {
            Vertex v = edge.first;
            int weight = edge.second;
            if (currentDist + weight < dist[v]) {
                dist[v] = currentDist + weight;
                pq.push(v, dist[v]); // Update priority queue
            }
        }
    }

    // Generating output maze with path marked
    vector<vector<char> > outputMaze(numRows, vector<char>(numCols, '#'));
    for (int r = 0; r < numRows; r++) {
        for (int c = 0; c < numCols; c++) {
            outputMaze[r][c] = maze[r][c];
            if (maze[r][c] != '#' && dist[Vertex(r, c)] != numeric_limits<int>::max()) {
                outputMaze[r][c] = 'o';  // Marking path
            }
        }
    }

    stringstream result;
    for (const auto& row : outputMaze) {
        for (char ch : row) {
            result << ch;
        }
        result << '\n';
    }
    for(int i=0;i<result.str().size(); i++){
        cout << result.str()[i];
    }
    cout << endl;
    return result.str();
}