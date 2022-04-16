#include "airport.h"

using namespace std;
Airport::Airport(string codeName): code_(codeName), unique_id_(-1), destinations(vector<pair<string,string>>()) {}

Airport::Airport(int uniqueID): code_("unknown"), unique_id_(uniqueID), destinations(vector<pair<string,string>>()) {}

Airport::Airport(string codeName, int uniqueID): code_(codeName), unique_id_(uniqueID), destinations(vector<pair<string,string>>()) {}

Airport::Airport(string codeName, int uniqueID, pair<string,string> destination): code_(codeName), unique_id_(uniqueID), destinations(vector<pair<string,string>>()) {
    addDestination(destination);
}

void Airport::addDestination(pair<string,string> dest) {
    destinations.push_back(dest);
}

vector<pair<string,string>>& Airport::getDestinations() { return destinations; }

vector<pair<string,string>> Airport::getArrivals(map<string, Airport*> m){
    std::vector<std::pair<string,string>> arrivals; 

    map<string, Airport*> ::iterator it;
    for (it = m.begin(); it != m.end(); it++){
        std::vector<std::pair<string,string>>& destinations = it->second->getDestinations();
        for (size_t x = 0; x < destinations.size(); x++ ){
            int id;
            try { id = stoi(destinations.at(x).second); }
            catch(std::invalid_argument& e) { id = -1; }
            if (destinations.at(x).first == getCode() && id == getID()){
                arrivals.push_back(pair<string,string>(destinations.at(x).first, to_string(id)));
            }
        }
    }
    return arrivals;
}

string Airport::getCode() { return code_; }
int Airport::getID() { return unique_id_; }