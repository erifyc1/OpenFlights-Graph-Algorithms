#pragma once

#include "airport.h"
#include "utils.h"

struct WeightedAdjacency {
    WeightedAdjacency(): n(0), matrix(vector<vector<unsigned int>>()), keys(map<string, unsigned int>()) {};
    size_t n;
    vector<vector<unsigned int>> matrix;
    map<string, unsigned int> keys;
};

class DataHandler {
    public:
        // default constructor
        DataHandler();

        // constructor that either reads from csv or compressed flight data file
        DataHandler(const std::string& filename, bool from_csv=false);

        // destructor
        ~DataHandler();

        // helper function to read in flight data from given .csv
        void readInCSV(const std::string& filename);

        // helper function to read in flight data from given .txt
        void readInCompressed(const std::string& filename);

        // method to write existing map data into compressed .txt file
        void writeMapToFile(const string& filename);

        // getter for reference to airports map (for testing and Dijkstras)
        map<string, Airport*>& getAirports();

        //edges will be inputted as "departure arrival" and a 0 will mean unexplored
        // 1 will mean discovery edge and 2 will mean cross edge
        map<string,short> BFS();
        map<string, string> BFS(string start, map<string, short>& edges, map<string, bool>& vertices);
        vector<string> BFS_to_path(map<string, string> in, string end);

        // constructs and returns the weighted adjacency matrix (each position has value n, the number of flights from i to j)
        // needs to be manipulated for Dijkstra's and PageRank
        WeightedAdjacency getWeightedAdjacency();

        std::vector<double> centralityAlgorithm();
        pair<unsigned int, string> getCenter();
        pair<unsigned int, string> getLeastCenter();


    
    private:
        map<string, Airport*> airports;

};
    