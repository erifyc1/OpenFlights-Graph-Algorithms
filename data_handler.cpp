#include "data_handler.h"
#include <queue>
#include "Eigen/Core"
#include "Eigen/Eigenvalues"

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
        readInCompressed(filename);
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
        if (count % 3380 == 0) {
            cout << static_cast<double>(count)/676 << "%" << endl;
        }
        count++;

        getline(ifs, line);
        vector<string> delimited = utils::delimitLine(line, ',');
        if (delimited.size() <= 1) { return; }


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
            //temp adding this line might delete later
            if (airports.find(destination.second) == airports.end()) {
                airports[destination.second] = new Airport(destination.second);
            }
        }
        else {
            airports.at(source)->addDestination(destination);
            if (airports.find(destination.second) == airports.end()) {
                airports[destination.second] = new Airport(destination.second);
            }
        }
    }
}

// reads in compressed version of flight data

void DataHandler::readInCompressed(const std::string& filename) {
    ifstream ifs(filename);
    string line;

    unsigned int count = 0;
    // read in entries
    while (ifs.good()) {
        if (count % 170 == 0) {
            cout << static_cast<double>(count)/34 << "%" << endl;
        }
        count++;

        getline(ifs, line);
        vector<string> initial = utils::delimitLine(line, '>');
        if (initial.size() <= 1) { return; }

        string source = initial.at(0);
        Airport* ap = new Airport(source, -1);
        airports.insert(pair<string, Airport*>(source, ap));

        vector<string> destinations = utils::delimitLine(initial.at(1), ',');
        for (string dest : destinations) {
            if (dest.size() == 0) continue;
            vector<string> sep = utils::delimitLine(dest, '|');
            if (sep.size() == 2) {
                const vector<char> rem = { '(', ')' };
                ap->addDestination(pair<string,string>(utils::removeChar(sep[0], rem), utils::removeChar(sep[1], rem)));
            }
            else {
                cout << "invalid format of compressed file"  << endl;
            }
        }
    }
}


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

// BFS main function
map<string,short> DataHandler::BFS() {
    map<string, bool> vertex;
    map<string, short> edges;
    for (auto v : airports) {
        if (!vertex[v.first]) {
            BFS(v.first, edges, vertex);
        }
    }
    return edges;
}

map<string, Airport*>& DataHandler::getAirports() {
    return airports;
}

// BFS recursive helper function
void DataHandler::BFS(string start, map<string, short>& edges, map<string, bool>& vertices) {
    vertices[start] = true;
    queue<string> q;
    q.push(start);
    //cout << "check for seg" << endl;
    while (!q.empty()) {
        string curr = q.front();
        cout << curr << endl;
        q.pop();
        for (auto x : airports[curr]->getDestinations()) {
            string dest = x.second;
            if (vertices[dest] == false) {
                vertices[dest] = true;
                string temp = curr;
                edges[temp.append(" ").append(dest)] = 1;
                q.push(dest);
            } else {
                string temp = curr;
                edges[temp.append(" ").append(dest)] = 2;
            }
            
        }
    }
}

// gets the weighted adjacency matrix (each position has value n, the number of flights from i to j)
// needs to be manipulated for Dijkstra's and PageRank
WeightedAdjacency DataHandler::getWeightedAdjacency() {
    WeightedAdjacency w;
    w.n = airports.size();
    w.matrix.resize(w.n);
    for (size_t i = 0; i < w.n; i++) {
        w.matrix[i].resize(w.n);
    }
    // to save on runtime, airport lookup will be in map
    unsigned int count = 0;
    // initialize keys
    for (pair<string, Airport*> airport : airports) {
        w.keys.insert(pair<string, unsigned int>(airport.first, count++));
    }
    // for each source airport, add a flight for each destination
    for (pair<string, Airport*> airport : airports) {
        if (airport.second == NULL) continue;
        vector<pair<string,string>>& destinations = airport.second->getDestinations();
        for (pair<string,string> dest : destinations) {
            if (w.keys.find(dest.second) == w.keys.end()) continue;
            w.matrix[w.keys.at(airport.first)][w.keys.at(dest.second)]++;
        }
    }
    return w;
}



std::vector<double> DataHandler::centralityAlgorithm(){
    WeightedAdjacency w = getWeightedAdjacency();
    Eigen::MatrixXd m(w.n, w.n);

    for (int i = 0; i < (int)w.n; i++){
        double colSum = 0;
        for (int j = 0; j < (int)w.n; j++){
            colSum += w.matrix.at(j).at(i);
        }
        for (int j = 0; j < (int)w.n; j++){
            if (colSum != 0){
                m(j,i) = (double)w.matrix.at(j).at(i)/colSum;
            }
            else{
                m(j,i) = (1.00)/((double)(w.n));
            }
        }
    }


    std::cout << m.col(2117) << std::endl;

    Eigen::VectorXd start = Eigen::VectorXd::Zero(w.n);

    for (int i = 0; i < (int)w.n; i++){
        start(i) = (1.00)/((double)(w.n));
    }

    start = m * start;


    for (int i = 0; i < 100; i++){
        start = m * start;
        std::cout << std::endl;
        std::cout << "ORD " << start(2117) << std::endl;
        std::cout << "ATL " << start(165) << std::endl;
        std::cout << "Random " << start(10) << std::endl;
        std::cout << "Random2 " << start(1000) << std::endl;
        std::cout << std::endl;

    }

  
    std::vector<double> steady_state;

    for (int j = 0; j < (int)w.n; j++){
        steady_state.push_back(start(j));
        
    }

    return steady_state;
}

// returns integer corresponding to the index of the most central airport

int DataHandler::getCenter(){
    std::vector<double> steady_state = centralityAlgorithm();
    double max = 0;
    double maxIndex = 0; 
    WeightedAdjacency w = getWeightedAdjacency();

    for (int i = 0; i < (int)steady_state.size(); i++){
        if (steady_state.at(i) > max){
            max = steady_state.at(i);
            maxIndex = i;
            std::map<std::string, unsigned int>::iterator it;
            for (it = w.keys.begin(); it != w.keys.end(); it++){
                if ( (int)(*it).second == maxIndex){
                    std::cout << (*it).first << std::endl;
                }
            }
        }
    }


    // for (it = w.keys.begin(); it != w.keys.end(); it++)
    // {
    //     if ( (int)(*it).second == maxIndex){
    //         std::cout << (*it).first << std::endl;
    //     }
    // }


    return maxIndex;
}

