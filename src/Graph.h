#ifndef PROJECT1_GRAPH_H
#define PROJECT1_GRAPH_H

#include "Station.h"

class Graph {
private:
    std::vector<Station *> stationsSet;
public:
    Graph();
    Station *findStation(std::string name) const;
    bool addStation(Station station);
    bool addNetwork(std::string origStationName, std::string destStationName, int capacity, Service service);
    std::vector<Station *> getStationSet() const;
};


#endif //PROJECT1_GRAPH_H
