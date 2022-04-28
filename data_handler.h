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
        void BFS(string start, map<string, short>& edges, map<string, bool>& vertices);

        // constructs weighted adjacency matrix
        // used for Dijkstras (requires 1/entry) and Pagerank (needs to be divided by sum of column)
        WeightedAdjacency getWeightedAdjacency();
    private:
        map<string, Airport*> airports;

};
    