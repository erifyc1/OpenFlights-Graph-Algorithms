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
<<<<<<< HEAD
        Airport(string codeName, int uniqueID, pair<string,string> destination);
        Airport(string codeName, vector<pair<string,string>> destinations);
        void addDestination(pair<string,string> dest);
        vector<pair<string,string>>& getDestinations();
=======
        Airport(string codeName, int uniqueID, string destination);
        void addDestination(string dest);
        vector<string>& getDestinations();
        vector<string>& getArrivals(map<string, Airport*> m);
>>>>>>> 6065990ba285bd4101262ee752b7ad05c52d2b33
        string getCode();
        int getID();
    private:
        string code_;
        int unique_id_;
        vector<pair<string,string>> destinations;



};