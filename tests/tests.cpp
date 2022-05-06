#include "../cs225/catch/catch.hpp"

// data_handler includes airport & utils
#include "../data_handler.h"
#include "../dijkstra.h"

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
    REQUIRE(out["LIL BRU"] == 2);
    REQUIRE(out["CMW JFK"] == 0);



}
//start node and end arent connected

TEST_CASE("Weighted Adjacency Matrix medium", "[valgrind][weight=1]") {
    const string input = "tests/easyroutes.csv";

    // read data from csv file
    DataHandler d(input, true);
    cout << "successfully read from " << input << endl;

    vector<vector<int>> ans = { {0, 0, 0, 0, 0, 0, 0,},
                                {0, 0, 0, 0, 0, 0, 1,},
                                {0, 0, 0, 0, 0, 0, 0,},
                                {0, 0, 0, 0, 0, 0, 0,},
                                {0, 0, 0, 0, 0, 0, 1,},
                                {1, 0, 0, 0, 0, 0, 0,},
                                {0, 0, 1, 1, 0, 0, 0 } };
    vector<string> ans_keys = {"BRU","CMW","DFW","FIA","JFK","LIL","STL"};
    WeightedAdjacency w = d.getWeightedAdjacency();
    for (size_t i = 0; i < w.n; i++) {
        for (size_t j = 0; j < w.n; j++) {
            REQUIRE(w.matrix[i][j] == ans[i][j]);
        }
    }

    // for (size_t k = 0; k < w.keys.size(); k++) {
    //     REQUIRE(w.keys[k] == ans_keys[k]);
    // }

}


TEST_CASE("Dijkstra easy", "[valgrind][weight=1]") {
    const string input = "tests/easyroutes.csv";

    // read data from csv file
    DataHandler d(input, true);
    cout << "successfully read from " << input << endl;


    Dijkstra dk = Dijkstra(d);
    cout << "generated" << endl;
    DijkstraResult result = dk.findPath("CMW", "DFW");

    cout << result.pathLength << endl;
    for (size_t i = 0; i <= result.pathLength; i++) {
        cout << result.path[i] << (i != result.pathLength ? " -> " : "");
    }
    cout << endl;

    REQUIRE(true);

}


TEST_CASE("Dijkstra hard", "[valgrind][weight=1]") {
    const string input = "data/compressed.txt";

    // read data from csv file
    DataHandler d(input);
    cout << "successfully read from " << input << endl;


    Dijkstra dk = Dijkstra(d);
    cout << "generated" << endl;
    DijkstraResult result = dk.findPath("STL", "ATL");

    cout << result.pathLength << endl;
    for (size_t i = 0; i < result.path.size(); i++) {
        cout << result.path[i] << (i != result.path.size() - 1 ? " -> " : "");
    }
    cout << endl;

    REQUIRE(true);

}

TEST_CASE("Steady State Vector Properties", "[valgrind][weight=1]") {
    const string input = "data/compressed.txt";

    // read data from csv file
    DataHandler d(input);
    // cout << "successfully read from " << input << endl;
    std::vector<double> v = d.centralityAlgorithm();

    double sum = 0; 

    for (int i = 0; i < (int)v.size(); i++){
        sum+= v.at(i);
    }

    
    REQUIRE( sum <= 1 );

}

TEST_CASE("Convergence of Steady State Vector", "[valgrind][weight=1]") {
    const string input = "data/compressed.txt";

    // read data from csv file
    DataHandler d(input);
    // cout << "successfully read from " << input << endl;
    std::vector<double> v = d.centralityAlgorithm();
    std::vector<double> v2 = d.centralityAlgorithmTest();
    std::cout << abs(v.at(165) - v2.at(165)) << std::endl;

    REQUIRE( abs(v.at(165) - v2.at(165)) <= 0.001 );

}

TEST_CASE("Most Central Airport", "[valgrind][weight=1]") {
    const string input = "data/compressed.txt";

    // read data from csv file
    DataHandler d(input);
    // cout << "successfully read from " << input << endl;

    REQUIRE( d.getCenter() == 165);

}


