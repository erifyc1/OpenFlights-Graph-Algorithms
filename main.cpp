#include "data_handler.h"
#include "airport.h"
#include "dijkstra.h"

using namespace std;
//Currently coding with the idea that this will only be ran on this data set with this formatting
int main(int argc, char** argv) {
    cout << "\n\nData Processing: " << endl;
    DataHandler d;
    // case 1: read in data from routes.csv and save to compressed.txt
    if (argc == 2 && argv[1][0] == '-' && argv[1][1] == 'c' && argv[1][2] == 's' && argv[1][3] == 'v') {

        const string input = "./data/routes.csv";
        const string output = "./data/compressed.txt";

        // read data from csv file
        d.readInCSV(input);
        cout << "Successfully read flight data from " << input << endl;

        // write data to compressed file
        d.writeMapToFile(output);
        cout << "successfully wrote flight data to " << output << endl;
    }
    // case 2: read in data from compressed.txt and save to compressed_twice.txt
    else {
        cout << "Reading from compressed flight data." << endl;
        const string input = "./data/compressed.txt";
        const string output = "./data/compressed_twice.txt";

        // read data from compressed file
        d.readInCompressed(input);
        cout << "Successfully read flight data from " << input << endl;

        // write data to another compressed file
        // to test if this works, run "diff ./data/compressed.txt ./data/compressed_twice.txt"
        // if there is no output, the files match (and they should)
        d.writeMapToFile(output);


        if (argc == 4 && argv[1][0] == '-' && argv[1][1] == 'd' && argv[1][2] == 'k') {
            cout << "\n\nDijkstra's Algorithm Selected" << endl;
            string start = argv[2];
            string dest = argv[3];
            cout << "Finding path between " << start << " and " << dest << endl;
            Dijkstra dk = Dijkstra(d);
            DijkstraResult result = dk.findPath(start, dest);
            if (result.path.size() == 0) {
                cout << "No path found.";
            }
            else {
                cout << "Weighted path length: " << result.pathLength << endl;
                cout << "Path Trace: ";
                for (size_t i = 0; i < result.path.size(); i++) {
                    cout << result.path[i] << (i != result.path.size() - 1 ? " -> " : "");
                }
            }
            cout << endl;
        }
        else if (argc == 4 && argv[1][0] == '-' && argv[1][1] == 'b' && argv[1][2] == 'f' && argv[1][3] == 's') {
            cout << "\n\nBFS Selected" << endl;
            map<string, short> out = d.BFS();
            string source = argv[2];
            string dest = argv[3];
            string query = source + " " + dest;

            if (out[query] == 0) {
                cout << source << "-" << dest << " is not an edge in the graph." << endl;
            } else if (out[query] == 1) {
                cout << source << "-" << dest << " is a discovery edge." << endl;
            } else {
                cout << source << "-" << dest << " is a cross edge." << endl;
            }
            map<string, short> edges;
            map<string, bool> vertices;
            vector<string> path = d.BFS_to_path(d.BFS(source, edges, vertices), dest);
            if (path.size() == 1 && source != dest) { 
                cout << "No path found."; 
            }
            else {
                cout << "Path length: " << path.size() << endl;
                cout << "Path Trace: ";
                for (size_t i = 0; i < path.size(); i++) {
                    cout << path[i] << (i != path.size() - 1 ? " -> " : "");
                }
            }
            cout << endl;
        }
        else if (argc == 3 && argv[1][0] == '-' && argv[1][1] == 'p' && argv[1][2] == 'r') {
            cout << "\n\nPageRank Selected" << endl;
            if (argv[2][0] != 'T' && argv[2][0] != 'F') goto invalid;
            pair<unsigned int, string> res;
            res = argv[2][0] == 'T' ? d.getCenter() : d.getLeastCenter();
            cout << "The " << (argv[2][0] == 'T' ? "most" : "least") << " central airport in the dataset is " << res.second << endl;
        }
        else {
            invalid:
            cout << "Invalid Command Line Argument, Usage: " << endl << endl;
            cout << "Dijkstra's Algorithm: " << argv[0] << " -dk  <source airport> <destination airport>" << endl;
            cout << "Returns shortest weighted path between source and destination and weighted path length." << endl;
            cout << "Ex: " << argv[0] << " -dk STL LIL" << endl << endl;

            cout << "BFS: " << argv[0] << " -bfs <source airport> <destination airport>" << endl;
            cout << "Desc: Returns the length of the shortest path between source and destination." << endl;
            cout << "Ex: " << argv[0] << " -bfs STL LIL" << endl << endl;

            cout << "PageRank: " << argv[0] << " -pr  <T/F>" << endl;
            cout << "Returns most or least central/important airport. T = centralized. F = decentralized." << endl;
            cout << "Ex: " << argv[0] << " -pr T" << endl << endl;
        }
    }
    cout << "\n\n";
    
    return 0;
}