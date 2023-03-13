#ifndef PROJECT1_STATION_H
#define PROJECT1_STATION_H

#include <string>
#include <vector>
#include "Network.h"

class Station {
private:
    std::string name;
    std::string district;
    std::string municipality;
    std::string township;
    std::string line;

    std::vector<Network *> adj;

    double dist = 0;
    bool visited = false;
    Network *path = nullptr;

    std::vector<Network *> incoming;

public:
    Station(std::string name, std::string district, std::string municipality, std::string townships,std::string line);
};


#endif //PROJECT1_STATION_H
