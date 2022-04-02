#include <fstream>
#include <map>
#include <string>

#pragma once

class DataHandler {
    public:
        DataHandler(const std::string& filename);
    private:
        std::map<std::string airport, Airport*> airports;

}
    
