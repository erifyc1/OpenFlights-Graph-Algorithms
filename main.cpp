#include "data_handler.h"
#include "airport.h"
#include "dijkstra.h"

using namespace std;
//Currently coding with the idea that this will only be ran on this data set with this formatting
int main(int argc, char** argv) {
    DataHandler d;

    // import data
    if (argc == 2 && argv[1][0] == 'c' && argv[1][1] == 's' && argv[1][2] == 'v') {

        const string input = "./data/routes.csv";
        const string output = "./data/compressed.txt";

        // read data from csv file
        d.readInCSV(input);
        cout << "successfully read from " << input << endl;

        // write data to compressed file
        d.writeMapToFile(output);
        cout << "successfully written to " << output << endl;
    }
    else {

        const string input = "./data/compressed.txt";
        const string output = "./data/compressed_twice.txt";

        // read data from compressed file
        d.readInCompressed(input);
        cout << "successfully read from " << input << endl;

        // write data to another compressed file
        // to test if this works, run "diff ./data/compressed.txt ./data/compressed_twice.txt"
        // if there is no output, the files match (and they should)
        d.writeMapToFile(output);
        cout << "successfully written to " << output << endl;
    }
    /**
        @todo test further functions below
    **/

    WeightedAdjacency w = d.getWeightedAdjacency();
    cout << w.n << endl;
    std::cout << d.getCenter() << std::endl;





    
    return 0;
}