#pragma once

#include <vector>
#include <string>
#include <fstream>
#include <map>
#include <istream>
#include <iostream>
#include <ostream>
#include <stdexcept>

using namespace std;
class Airport {
    public:
        Airport(string codeName);
        Airport(int uniqueID);
        Airport(string codeName, int uniqueID);
        Airport(string codeName, int uniqueID, string destination);
        void addDestination(string dest);
        vector<string>& getDestinations();
        string getCode();
        int getID();
    private:
        string code_;
        int unique_id_;
        vector<string> destinations;



};