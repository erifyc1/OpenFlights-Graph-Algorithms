#include "airport.h"

using namespace std;
Airport::Airport(string codeName): code_(codeName), unique_id_(-1), destinations(vector<string>()) {}

Airport::Airport(int uniqueID): code_("unknown"), unique_id_(uniqueID), destinations(vector<string>()) {}

Airport::Airport(string codeName, int uniqueID): code_(codeName), unique_id_(uniqueID), destinations(vector<string>()) {}

Airport::Airport(string codeName, int uniqueID, string destination): code_(codeName), unique_id_(uniqueID), destinations(vector<string>()) {
    addDestination(destination);
}

void Airport::addDestination(string dest) {
    destinations.push_back(dest);
}

vector<string>& Airport::getDestinations() { return destinations; }
string Airport::getCode() { return code_; }
int Airport::getID() { return unique_id_; }