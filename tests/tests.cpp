#include "../cs225/catch/catch.hpp"

// data_handler includes airport & utils
#include "../data_handler.h"
#include "../dijkstra.h"
#include <cmath>


using namespace std;

TEST_CASE("readInCSV basecase", "[valgrind][weight=1]") {
    cout << "readInCSV basecase" << endl;
    const string input = "tests/basecase.csv";

    // read data from csv file
    DataHandler d(input, true);

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
    cout << "readInCSV easy1" << endl;
    const string input = "tests/easyroutes.csv";

    // read data from csv file
    DataHandler d(input, true);

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
    cout << "BFS base1" << endl;
    const string input = "tests/basecase.csv";

    // read data from csv file
    DataHandler d(input, true);
    map<string,short> out = d.BFS();

    REQUIRE(out["JFK STL"] == 1);


}

TEST_CASE("BFS easy1", "[valgrind][weight=1]") {
    //cout << "BFS easy1" << endl;
    const string input = "tests/easyroutes.csv";

    // read data from csv file
    DataHandler d(input, true);
    map<string,short> out = d.BFS();

    REQUIRE(out["CMW STL"] == 1);
    REQUIRE(out["STL DFW"] == 1);
    REQUIRE(out["STL FIA"] == 1);
    REQUIRE(out["JFK STL"] == 2);
    REQUIRE(out["LIL BRU"] == 2);
    REQUIRE(out["CMW JFK"] == 0);
    map<string, short> edges;
    map<string, bool> vertices;
    vector<string> path = d.BFS_to_path(d.BFS("CMW", edges, vertices), "FIA");
    vector<string> dk = {"CMW", "STL", "FIA"};
    for (int i = 0; i < 3; i++) {
        REQUIRE(path[i]==dk[i]);
    }


}

TEST_CASE("BFS medium2", "[valgrind][weight=1]") {
    //cout << "BFS easy1" << endl;
    const string input = "tests/easyroutes2.csv";

    // read data from csv file
    DataHandler d(input, true);
    map<string,short> out = d.BFS();

    REQUIRE(out["BRU CNY"] == 1);
    REQUIRE(out["MOT CNY"] == 2);
    REQUIRE(out["CAT MUE"] == 1);
    REQUIRE(out["JAC MUE"] == 2);
    REQUIRE(out["LIL BRU"] == 2);
    REQUIRE(out["CMW STL"] == 1);
    REQUIRE(out["STL DFW"] == 1);
    REQUIRE(out["STL FIA"] == 1);
    REQUIRE(out["JFK STL"] == 2);
    REQUIRE(out["JFK LIL"] == 1);

    map<string, short> edges;
    map<string, bool> vertices;
    vector<string> path = d.BFS_to_path(d.BFS("JFK", edges, vertices), "DFW");
    vector<string> dk = {"JFK", "STL", "DFW"};
    for (int i = 0; i < 3; i++) {
        REQUIRE(path[i]==dk[i]);
    }
    edges.clear();
    vertices.clear();
    path = d.BFS_to_path(d.BFS("JFK", edges, vertices), "MUE");
    dk = {"MUE"};
    for (int i = 0; i < 1; i++) {
        REQUIRE(path[i]==dk[i]);
    }


}
TEST_CASE("BFS hard", "[valgrind][weight=1]") {
    cout << "Dijkstra hard" << endl;
    const string input = "data/compressed.txt";

    // read data from csv file
    DataHandler d(input);

    map<string, short> edges;
    map<string, bool> vertices;
    vector<string> path = d.BFS_to_path(d.BFS("CMI", edges, vertices), "LHR");
    vector<string> dk = {"CMI", "DFW", "LHR"};
    for (int i = 0; i < 3; i++) {
        REQUIRE(path[i]==dk[i]);
    }
}

TEST_CASE("Weighted Adjacency Matrix small", "[valgrind][weight=1]") {
    cout << "Weighted Adjacency Matrix small" << endl;
    const string input = "tests/basecase.csv";

    // read data from csv file
    DataHandler d(input, true);

    vector<vector<int>> ans = { {0, 1},
                                {0, 0} };
    vector<string> ans_keys = {"JFK", "STL" };
    WeightedAdjacency w = d.getWeightedAdjacency();
    for (size_t i = 0; i < w.n; i++) {
        for (size_t j = 0; j < w.n; j++) {
            REQUIRE(w.matrix[i][j] == ans[i][j]);
        }
    }

    for (pair<string, unsigned int> key : w.keys) {
        bool found_key = false;
        for (string s : ans_keys) {
            if (key.first == s) {
                found_key = true;
                break;
            }
        }
        REQUIRE(found_key);
    }
    // REQUIRE(true);
}

TEST_CASE("Weighted Adjacency Matrix medium", "[valgrind][weight=1]") {
    cout << "Weighted Adjacency Matrix medium" << endl;
    const string input = "tests/easyroutes.csv";

    // read data from csv file
    DataHandler d(input, true);

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

    for (pair<string, unsigned int> key : w.keys) {
        bool found_key = false;
        for (string s : ans_keys) {
            if (key.first == s) {
                found_key = true;
                break;
            }
        }
        REQUIRE(found_key);
    }

}



TEST_CASE("Dijkstra self travel", "[valgrind][weight=1]") {
    cout << "Dijkstra self travel" << endl;
    const string input = "tests/easyroutes.csv";

    // read data from csv file
    DataHandler d(input, true);

    Dijkstra dk = Dijkstra(d);
    DijkstraResult result = dk.findPath("STL", "STL");
    vector<string> pathAns = { "STL" };
    for (size_t i = 0; i <= result.pathLength; i++) {
        REQUIRE(result.path[i] == pathAns[i]);
        cout << result.path[i] << (i != result.pathLength ? " -> " : "");
    }
    cout << endl;

    cout << result.pathLength << endl;
    REQUIRE((result.pathLength == 0));
    REQUIRE(result.path.size() == pathAns.size());

}

TEST_CASE("Dijkstra invalid travel", "[valgrind][weight=1]") {
    cout << "Dijkstra invalid travel" << endl;
    const string input = "tests/easyroutes.csv";

    // read data from csv file
    DataHandler d(input, true);


    Dijkstra dk = Dijkstra(d);
    DijkstraResult result = dk.findPath("STL", "LIL");
    REQUIRE(result.path.size() == 0);
    REQUIRE(result.pathLength == 0);
}


TEST_CASE("Dijkstra easy", "[valgrind][weight=1]") {
    cout << "Dijkstra easy" << endl;
    const string input = "tests/easyroutes.csv";

    // read data from csv file
    DataHandler d(input, true);


    Dijkstra dk = Dijkstra(d);
    DijkstraResult result = dk.findPath("CMW", "DFW");
    vector<string> pathAns = { "CMW", "STL", "DFW" };
    cout << "route: ";
    for (size_t i = 0; i <= result.pathLength; i++) {
        REQUIRE(result.path[i] == pathAns[i]);
        cout << result.path[i] << (i != result.pathLength ? " -> " : "");
    }
    cout << endl;

    cout << "path length: " << result.pathLength << endl;
    REQUIRE((result.pathLength == 2));
    REQUIRE(result.path.size() == pathAns.size());

}


TEST_CASE("Dijkstra hard", "[valgrind][weight=1]") {
    cout << "Dijkstra hard" << endl;
    const string input = "data/compressed.txt";

    // read data from csv file
    DataHandler d(input);


    Dijkstra dk = Dijkstra(d);
    DijkstraResult result = dk.findPath("STL", "BNB");
    vector<string> pathAns = { "STL", "ATL", "JFK", "BRU", "DLA", "FIH", "BNB" };
    cout << "route: ";
    for (size_t i = 0; i < result.path.size(); i++) {
        REQUIRE(result.path[i] == pathAns[i]);
        cout << result.path[i] << (i != result.path.size() - 1 ? " -> " : "");
    }
    cout << endl;

    cout << "path length: " << result.pathLength << endl;
    // relaxed pathlength test to avoid rounding errors
    REQUIRE((result.pathLength >= 1.83 && result.pathLength <= 1.85));
    REQUIRE(result.path.size() == pathAns.size());
}

TEST_CASE("PageRank Steady State Vector Properties", "[valgrind][weight=1]") {
    cout << "PageRank Steady State Vector Properties" << endl;
    const string input = "data/compressed.txt";

    // read data from csv file
    DataHandler d(input);
    // cout << "successfully read from " << input << endl;
    std::vector<double> v = d.centralityAlgorithm();

    double sum = 0; 

    for (int i = 0; i < (int)v.size(); i++){
        sum+= v.at(i);
    }

    // 1.0001 used due to sum rounding errors
    REQUIRE( sum <= 1.0001 );

}

TEST_CASE("PageRank Convergence of Steady State Vector", "[valgrind][weight=1]") {
    cout << "PageRank Convergence of Steady State Vector" << endl;
    const string input = "data/compressed.txt";

    // read data from csv file
    DataHandler d(input);
    std::vector<double> v = d.centralityAlgorithm();
    std::vector<double> v2 = d.centralityAlgorithmTest();
    std::cout << abs(v.at(165) - v2.at(165)) << std::endl;

    REQUIRE( abs(v.at(165) - v2.at(165)) <= 0.001 );

}

TEST_CASE("Most Central Airport", "[valgrind][weight=1]") {
    cout << "Most Central Airport" << endl;
    const string input = "data/compressed.txt";

    // read data from csv file
    DataHandler d(input);

    pair<unsigned int, string> res = d.getCenter();

    REQUIRE( res.first == 165);
    REQUIRE( res.second == "ATL" );

}

TEST_CASE("Least Central Airport", "[valgrind][weight=1]") {
    cout << "Least Central Airport" << endl;
    const string input = "data/compressed.txt";

    // read data from csv file
    DataHandler d(input);

    pair<unsigned int, string> res = d.getLeastCenter();

    REQUIRE( res.first == 381);
    REQUIRE( res.second == "BSS" );

}


