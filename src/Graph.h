#ifndef PROJECT1_GRAPH_H
#define PROJECT1_GRAPH_H

#include <iostream>
#include <string>
#include <unordered_map>

#include "Station.h"

class Graph {
private:
    std::unordered_map<std::string, Station *> stationsSet;
public:
    Graph();
    Station *findStation(std::string name) const;
    bool addStation(Station station);
    bool addNetwork(std::string origStationName, std::string destStationName, int capacity, Service service);
    std::unordered_map<std::string, Station *> getStationSet() const;
};


#endif //PROJECT1_GRAPH_H
