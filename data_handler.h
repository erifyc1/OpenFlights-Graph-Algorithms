#pragma once

#include "airport.h"


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
        // not finished yet
        void readInCompressed(const std::string& filename);

        // helper function to separate a line into a vector by delim
        vector<string> delimitLine(const string line, const char delim);

        // method to write existing map data into compressed .txt file
        void writeMapToFile(const string& filename);
    private:
        map<string, Airport*> airports;

};
    
