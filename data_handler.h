#pragma once

#include <fstream>
#include <map>
#include <string>
#include "airport.h"


class DataHandler {
    public:
        DataHandler(const std::string& filename);
    private:
        std::map<std::string, Airport*> airports;

};
    
