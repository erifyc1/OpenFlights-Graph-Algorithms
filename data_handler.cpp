#include "data_handler.h"

using namespace std;

DataHandler::DataHandler() {
    airports = map<string, Airport*>();
}

DataHandler::DataHandler(const string& filename, bool from_csv) {
    airports = map<string, Airport*>();
    if (from_csv) {
        readInCSV(filename);
    }
    else {
        // not finished yet
        // readInCompressed(filename);
    }
}

// reads in raw csv flight data
void DataHandler::readInCSV(const std::string& filename) {
    ifstream ifs(filename);
    string line;
    // get rid of first entry
    getline(ifs, line);
    unsigned int count = 0;
    // read in the rest of the entries
    while (ifs.good()) {
        if (count % 677 == 0) {
            cout << static_cast<double>(count)/677 << "%" << endl;
        }
        count++;

        getline(ifs, line);
        vector<string> delimited = utils::delimitLine(line, ',');
        if (delimited.size() <= 1) {
            cout << "100%" << endl;
            return;
        }

        string source = delimited.at(2);
        pair<string,string> destination = {delimited.at(0), delimited.at(4)};

        // id may not be a valid integer (bad data)
        int id;
        try { id = stoi(delimited.at(3)); }
        catch(std::invalid_argument& e) { id = -1; }

        // if airport does not exist, add it
        // if airport does exist, append destination
        if (airports.find(source) == airports.end()) {
            airports.insert(pair<string, Airport*>(source, new Airport(source, id, destination)));
        }
        else {
            airports.at(source)->addDestination(destination);
        }
    }
}

// reads in compressed version of flight data WORK IN PROGRESS

// void readInCompressed(const std::string& filename) {
//     ifstream ifs(filename);
//     string line;

//     unsigned int count = 0;
//     // read in entries
//     while (ifs.good()) {
//         if (count % 34 == 0) {
//             cout << static_cast<double>(count)/34 << "%" << endl;
//         }
//         count++;

//         getline(ifs, line);
//         vector<string> initial = delimitLine(line, '>');
//         if (initial.size() <= 1) {
//             cout << "100%" << endl;
//             return;
//         }

//         string source = initial.at(0);
//         vector<string> destinations = delimitLine(initial.at(1), ',');


//         int id;
//         try { id = stoi(delimited.at(3)); }
//         catch(std::invalid_argument& e) { id = -1; }

//         if (airports.find(source) == airports.end()) {
//             airports.insert(pair<string, Airport*>(source, new Airport(source, id, destination)));
//         }
//         else {
//             airports.at(source)->addDestination(destination);
//         }
//     }
// }


// writes each airport and its destinations to a file
// format: ABL>OTZ,SHG,OTZ,SHG,
// means : ABL has flights to OTZ,SHG,OTZ,SHG (repeats are from multiple airlines or flights)
void DataHandler::writeMapToFile(const string& filename) {
    ofstream ofs(filename);

    for (pair<string, Airport*> p : airports) {
        ofs << p.first << ">";
        for (pair<string,string> dest : p.second->getDestinations()) {
            ofs << "("<< dest.first << "|" << dest.second << "),";
        }
        ofs << "\n";
    }
    ofs.close();
}

// destructor
DataHandler::~DataHandler() {
    // deletes dynamically allocated airport objects from the map
    for (pair<string, Airport*> p : airports) {
        if (p.second != NULL) {
            delete p.second;
            p.second = NULL;
        }
    }
}
