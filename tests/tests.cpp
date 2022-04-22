#include "../cs225/catch/catch.hpp"

// data_handler includes airport & utils
#include "../data_handler.h"

using namespace std;

TEST_CASE("readInCSV basecase", "[valgrind][weight=1]") {
    const string input = "basecase.csv";

    // read data from csv file
    DataHandler d(input, true);
    cout << "successfully read from " << input << endl;

    map<string, Airport*>& airports = d.getAirports();
    vector<string> ans = { "JFK" };
    
    for (pair<string, Airport*> p : airports) {
        REQUIRE(find(ans.begin(), ans.end(), p.first) != ans.end());
    }
}

TEST_CASE("readInCSV easy1", "[valgrind][weight=1]") {
    const string input = "easyroutes.csv";

    // read data from csv file
    DataHandler d(input, true);
    cout << "successfully read from " << input << endl;

    map<string, Airport*>& airports = d.getAirports();
    vector<string> ans = { "JFK", "STL", "LIL", "CMW" };
    cout << "test2" << endl;
    for (pair<string, Airport*> p : airports) {
        cout << "test3" << endl;
        REQUIRE(find(ans.begin(), ans.end(), p.first) != ans.end());
    }
}