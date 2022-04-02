#include <vector>
#pragma once

class Airport {
    public:
        Airport(std::string code);
        Airport(int unique_id_);
        Airport(std::string code, int unique_id_);
        Airport(std::string code, Airport* destination);
    private:
        std::string code_;
        int unique_id_;
        std::vector<Airport*> destinations;



}