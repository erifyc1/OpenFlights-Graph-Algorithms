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

        // BFS main function
        // Takes in nothing runs BFS in alphabetical order
        // outputs a map of all the edges marked as discovery(1), cross(2), or nonexistent(0) with key format "departure arrival"
        // so if I wanted to check the edge from JFK to STL the key would be "JFK STL"

        map<string,short> BFS();

        // BFS recursive helper function
        // Takes in the starting node, a reference to a map for the edges and vertices
        // output is a map in which keys are destination and and values are origins
        // the output is used exclusively by the BFS_to_path function.

        map<string, string> BFS(string start, map<string, short>& edges, map<string, bool>& vertices);

        // takes in the BFS helper output map and the destination
        // returns a vector in order of airports taken to reach destination
        // if no path exists the output is a vector with only the destination as its element

        vector<string> BFS_to_path(map<string, string> in, string end);

        // constructs and returns the weighted adjacency matrix (each position has value n, the number of flights from i to j)
        // needs to be manipulated for Dijkstra's and PageRank
        WeightedAdjacency getWeightedAdjacency();

        std::vector<double> centralityAlgorithm();
        std::vector<double> centralityAlgorithmTest();

        pair<unsigned int, string> getCenter();
        pair<unsigned int, string> getLeastCenter();


    
    private:
        map<string, Airport*> airports;

};
    
