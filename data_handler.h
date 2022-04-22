#pragma once

#include "airport.h"
#include "utils.h"


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

        // getter for reference to airports map (for testing)
        map<string, Airport*>& getAirports();

        //edges will be inputted as "departure arrival" and a 0 will mean unexplored
        // 1 will mean discovery edge and 2 will mean cross edge
        map<string,short> BFS();
        void BFS(string start, map<string, short>& edges, map<string, bool>& vertices);
    private:
        map<string, Airport*> airports;

};
    
