#include "dijkstra.h"

using namespace std;

// default constructor
Dijkstra::Dijkstra(): generated(false), djWeightedAdj(vector<vector<double>>()) {
    keys_ = map<string, unsigned int>();
}
// parameterized constructor, calls generateAdjacency
Dijkstra::Dijkstra(DataHandler dh): generated(false), djWeightedAdj(vector<vector<double>>()) {
    keys_ = map<string, unsigned int>();
    generateAdjacency(dh);
}
// generates weighted adjacency matrix using function in data_handler
void Dijkstra::generateAdjacency(DataHandler dh) {
    generated = true;
    djWeightedAdjacency w = dh.getdjWeightedAdjacency();
    djWeightedAdj.resize(w.n);
    for (size_t i = 0; i < w.n; i++) {
        djWeightedAdj[i].resize(w.n);
        for (size_t j = 0; j < w.n; j++) {
            djWeightedAdj[i][j] = w.matrix[i][j] == 0 ? 0 : 1 / static_cast<double>(w.matrix[i][j]);
        }
    }
    keys_ = w.keys;
}
// finds path between two points
DijkstraResult Dijkstra::findPath(string start, string dest) {
    if (!generated) throw runtime_error("adjacency matrix not generated");
    DijkstraResult dr;
    vector<GraphVertex> vertices;
    vector<bool> explored;
    explored.resize(djWeightedAdj.size());
    for (size_t i = 0; i < djWeightedAdj.size(); i++) {
        explored[i] = false;
    }
    /**
        @todo figure out how to use heap with custom less than Compare class
        heap<GraphVertex, Compare> h;
    **/
    if (keys_.find(start) == keys_.end() || keys_.find(dest) == keys_.end()) {
        cout << "no solution, missing start or dest" << endl;
        return DijkstraResult();
    }

    explored[keys_[start]] = true;
    vertices[keys_[start]].distance = 0;

    /**
        @todo make recursive call to dijkstraSearch
    **/
    return dr;
}


void Dijkstra::dijkstraSearch(vector<GraphVertex>& vertices, vector<bool>& visited, unsigned int vert) {
    
    // ending case, needs to be fixed
    bool possibleTravel = false;

    for (size_t i = 0; i < djWeightedAdj[vert].size(); i++) {
        if (visited[i]) continue;
        if (djWeightedAdj[vert][i] != 0) {
            if (vertices[i].distance == -1 || vertices[i].distance > (vertices[vert].distance + djWeightedAdj[vert][i])) {
                vertices[i].distance = vertices[vert].distance + djWeightedAdj[vert][i];
                vertices[i].prevDirection = vert;
            }
        }
    }
    /**
        @todo use priorityqueue to select next node (add as @param)
    **/
 
}
// reference solvemaze code 

// vector<int> SquareMaze::solveMaze() {
//     GraphVertex** bfsPath = new GraphVertex*[width_];
//     for (int i = 0; i < width_; i++) {
//         bfsPath[i] = new GraphVertex[height_];
//     }

//     bfsPath[0][0].distance = 0;
//     solveMazeBFS(bfsPath, 0, 0);
//     int bestDistance = bfsPath[0][height_ - 1].distance;
//     int bestPosition = 0;
//     for (int x = 1; x < width_; x++) {
//         int dist = bfsPath[x][height_ - 1].distance;
//         if (dist > bestDistance) {
//             bestDistance = dist;
//             bestPosition = x;
//         }
//     }
//     vector<int> finalPath;
//     int xPos = bestPosition;
//     int yPos = height_ - 1;
//     // only negative prev direction should be at (0,0)
//     while (bfsPath[xPos][yPos].prevDirection >= 0) {
//         // add inverse direction of prev to path
//         int prev = bfsPath[xPos][yPos].prevDirection;
//         int prevInv = -1;
//         switch (prev) {
//             case 0:
//             xPos += 1;
//             prevInv = 2;
//             break;
//             case 1:
//             yPos += 1;
//             prevInv = 3;
//             break;
//             case 2:
//             xPos -= 1;
//             prevInv = 0;
//             break;
//             case 3:
//             yPos -= 1;
//             prevInv = 1;
//             break;
//         };
//         finalPath.push_back(prevInv);
//     }
//     // clean up
//     for (int i = 0; i < width_; i++) {
//         delete[] bfsPath[i];
//     }
//     delete[] bfsPath;
//     // reverse so it starts at origin
//     reverse(finalPath.begin(), finalPath.end());
//     return finalPath;
// }