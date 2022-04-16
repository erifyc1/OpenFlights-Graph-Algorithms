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

<<<<<<< HEAD
vector<pair<string,string>>& Airport::getDestinations() { return destinations; }
=======
vector<parir<string,string>>& Airport::getDestinations() { return destinations; }

vector<string>& AirPort::getArrivals(map<string, Airport*> m){
    std::vector<std::pair<string,string>>& arrivals; 

    map<string, Airport*> ::iterator it;
    for (it = m.begin(); it != m.end(); it++){
        std::vector<std::pair<string,string>>& destinations = it -> getDestinations();
        for (int x = 0; x < destinations.size(); x++ ){
            if (destinations.at(i).first() == getCode() && destinations.at(i).second() == getID()){
                arrivals.push_back(pair(destinations -> getCode(), destinations -> getID()));
            }
        }
    }
}

>>>>>>> 6065990ba285bd4101262ee752b7ad05c52d2b33
string Airport::getCode() { return code_; }
int Airport::getID() { return unique_id_; }