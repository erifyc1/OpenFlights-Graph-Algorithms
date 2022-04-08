#include "data_handler.h"
#include "airport.h"

using namespace std;
//Currently coding with the idea that this will only be ran on this data set with this formatting
int main(int argc, char** argv) {
    // import data
    if (argc == 2 && argv[1][0] == 'c' && argv[1][1] == 's' && argv[1][2] == 'v') {
        const string s = "routes.csv";
        DataHandler d(s, true);
        cout << "constructed map" << endl;
        d.writeMapToFile("compressed.txt");
        cout << "done" << endl;
    }
    else {
        cout << "usage: " << argv[0] << " csv" << endl;
        cout << "compressed file read is not implemented yet" << endl;
        // will add read in compressed file here
        // not ready yet
    }
    // more code testing here
    // VVVVVVVVVVVVVVVVVVVVVV


    return 0;
}