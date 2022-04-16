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

std::vector<std::pair<string,string>>Airport::getArrivals(map<string, Airport*> m){
    std::vector<std::pair<string,string>> arrivals; 

    map<string, Airport*> ::iterator it;
    for (it = m.begin(); it != m.end(); it++){
        std::vector<std::pair<string,string>>& destinations = it -> second -> getDestinations();
        for (int x = 0; x < (int)destinations.size(); x++ ){
            if ( destinations.at(x).first == getCode() && std::stoi(destinations.at(x).second) == getID()){
                arrivals.push_back(pair<string,string>(destinations.at(x).first, destinations.at(x).second));
            }
        }
    }

    return arrivals;
}

string Airport::getCode() { return code_; }
int Airport::getID() { return unique_id_; }