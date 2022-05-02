#include "data_handler.h"
#include "airport.h"
#include "dijkstra.h"

using namespace std;
//Currently coding with the idea that this will only be ran on this data set with this formatting
int main(int argc, char** argv) {
    char bfs[] = {'-','b','f','s'};
    char pagerank[] = {'-','p','a','g','e','r','a','n','k'};
    DataHandler d;
    // case 1: read in data from routes.csv and save to compressed.txt
    if (argc == 2 && argv[1][0] == '-' && argv[1][1] == 'c' && argv[1][2] == 's' && argv[1][3] == 'v') {

        const string input = "./data/routes.csv";
        const string output = "./data/compressed.txt";

        // read data from csv file
        d.readInCSV(input);
        cout << "successfully read from " << input << endl;

        // write data to compressed file
        d.writeMapToFile(output);
        cout << "successfully written to " << output << endl;
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
            cout << "Dijkstra's Algorithm Selected" << endl;
            string start = argv[2];
            string dest = argv[3];
            cout << "Finding path between " << start << " and " << dest << endl;
            Dijkstra dk = Dijkstra(d);
            DijkstraResult result = dk.findPath(start, dest);
            cout << "Weighted path length: " << result.pathLength << endl;
            cout << "Path Trace: ";
            for (size_t i = 0; i < result.path.size(); i++) {
                cout << result.path[i] << (i != result.path.size() - 1 ? " -> " : "");
            }
            cout << endl;
        }
        else if (argc == 4/* <- change this*/ && argv[1][0] == '-' && argv[1][1] == 'b' && argv[1][2] == 'f' && argv[1][3] == 's') {
            cout << "BFS Selected" << endl;
            map<string, short> out = d.BFS();
            string source = argv[2];
            string dest = argv[3];
            source.append(" ").append(dest);

            if (out[source] == 0) {
                std::cout << source << " does not exist in the graph." << std::endl;
            } else if (out[source] == 1) {
                std::cout << source << " is a discovery edge." << std::endl;
            } else {
                std::cout << source << " is a cross edge." << std::endl;
            }
            map<string, short> edges;
            map<string, bool> vertices;
            vector<string> path = d.BFS_to_path(d.BFS(argv[2], edges, vertices), dest);
            std::cout << path[0];
            for (size_t i = 1; i < path.size(); i++) {
                std::cout << " -> " << path[i];
            }
            
        }
        else if (argc == 3 && argv[1][0] == '-' && argv[1][1] == 'p' && argv[1][2] == 'r') {
            cout << "PageRank Selected" << endl;
            if (argv[2][0] != 'T' && argv[2][0] != 'F') goto invalid;
            pair<unsigned int, string> res;
            res = argv[2][0] == 'T' ? d.getCenter() : d.getLeastCenter();
            cout << "The " << (argv[2][0] == 'T' ? "most" : "least") << " central airport in the dataset is " << res.second << endl;
        }
        else {
            invalid:
            cout << "Invalid Command Line Argument, Usage: " << endl << endl;
            cout << "Dijkstra's Algorithm: " << argv[0] << " -dk  <source airport> <destination airport>" << endl;
            cout << "Returns shortest weighted path between source and destination as well as the actual path." << endl;
            cout << "Ex: " << argv[0] << " -dk STL LIL" << endl << endl;

            cout << "BFS: " << argv[0] << " -bfs <source airport> <destination airport>" << endl;
            cout << "Desc: Returns shortest path between source and destination as well as the actual path." << endl;
            cout << "Ex: " << argv[0] << " -bfs STL LIL" << endl << endl;

            cout << "PageRank: " << argv[0] << " -pr  <T/F>" << endl;
            cout << "Returns most or least central/important airport. T = centralized. F = decentralized." << endl;
            cout << "Ex: " << argv[0] << " -pr T" << endl << endl;
        }
    }

    
    return 0;
}