#pragma once
#include "data_handler.h"
#include "heap.h"

using namespace std;

struct DijkstraResult {
    DijkstraResult(): pathLength(0), path(vector<string>()) {}
    unsigned int pathLength;
    vector<string> path;
};

struct GraphVertex {
    int distance;
    int prevDirection;
    GraphVertex(): distance(-1), prevDirection(-1) {}

    GraphVertex(int dist, int prevDir) {
        distance = dist;
        prevDirection = prevDir;
    }
    constexpr bool operator()( const GraphVertex& lhs, const GraphVertex& rhs ) const {
        return lhs.distance < rhs.distance;
    }
};

class Dijkstra {
    public:
    // default constructor
    Dijkstra();
    // parameterized constructor, calls generateAdjacency
    Dijkstra(DataHandler dh);
    // generates weighted adjacency matrix using function in data_handler
    void generateAdjacency(DataHandler dh);
    // finds path between two points
    DijkstraResult findPath(string start, string dest);
    // helper for findpath
    void dijkstraSearch(vector<GraphVertex>& vertices, vector<bool>& visited, unsigned int vert);

    private:
    bool generated;
    vector<vector<double>> weightedAdj;
    map<string, unsigned int> keys_;
};