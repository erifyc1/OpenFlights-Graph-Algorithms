#include "../cs225/catch/catch.hpp"

// data_handler includes airport & utils
#include "../data_handler.h"

using namespace std;

TEST_CASE("readInCSV basecase", "[valgrind][weight=1]") {
    const string input = "tests/basecase.csv";

    // read data from csv file
    DataHandler d(input, true);
    cout << "successfully read from " << input << endl;

    map<string, Airport*>& airports = d.getAirports();
    //vector<string> ans = { "JFK" };
    vector<string> ans = { "JFK" , "STL"};
    
    for (pair<string, Airport*> p : airports) {
        REQUIRE(find(ans.begin(), ans.end(), p.first) != ans.end());
    }
    for (string s : ans) {
        REQUIRE(airports[s]);
    }
}

TEST_CASE("readInCSV easy1", "[valgrind][weight=1]") {
    const string input = "tests/easyroutes.csv";

    // read data from csv file
    DataHandler d(input, true);
    cout << "successfully read from " << input << endl;

    map<string, Airport*>& airports = d.getAirports();
    //vector<string> ans = { "JFK", "STL", "LIL", "CMW" };
    vector<string> ans = { "JFK", "STL", "LIL", "CMW" , "DFW", "BRU", "FIA"};
    cout << airports.empty() << endl;
    for (pair<string, Airport*> p : airports) {
        //cout << "test3" << endl;
        REQUIRE(find(ans.begin(), ans.end(), p.first) != ans.end());
    }

    for (string s : ans) {
        REQUIRE(airports[s]);
    }
}

TEST_CASE("BFS base1", "[valgrind][weight=1]") {
    const string input = "tests/basecase.csv";

    // read data from csv file
    DataHandler d(input, true);
    cout << "successfully read from " << input << endl;
    map<string,short> out = d.BFS();

    REQUIRE(out["JFK STL"] == 1);


}

TEST_CASE("BFS easy1", "[valgrind][weight=1]") {
    const string input = "tests/easyroutes.csv";

    // read data from csv file
    DataHandler d(input, true);
    cout << "successfully read from " << input << endl;
    map<string,short> out = d.BFS();

    REQUIRE(out["CMW STL"] == 1);
    REQUIRE(out["STL DFW"] == 1);
    REQUIRE(out["STL FIA"] == 1);
    REQUIRE(out["JFK STL"] == 2);
    REQUIRE(out["LIL BRU"] == 1);
    REQUIRE(out["CMW JFK"] == 0);



}
//start node and end arent connected