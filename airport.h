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
        Airport(string codeName, int uniqueID, pair<string,string> destination);
        Airport(string codeName, vector<pair<string,string>> destinations);
        void addDestination(pair<string,string> dest);
        vector<pair<string,string>>& getDestinations();
        vector<pair<string,string>> getArrivals(map<string, Airport*> m);
        string getCode();
        int getID();
    private:
        string code_;
        int unique_id_;
        vector<pair<string,string>> destinations;



};