#include "Graph.h"

Graph::Graph() {}

Station *Graph::findStation(std::string name) const {
    //TODO
}

bool Graph::addStation(Station station) {
    stationsSet[station.getName()] = &station;
}

bool Graph::addNetwork(std::string origStationName, std::string destStationName, int capacity, Service service) {
    stationsSet[origStationName]->addAdj(&Network(stationsSet[origStationName], stationsSet[destStationName], service, capacity));
    stationsSet[destStationName]->addIncoming(&Network(stationsSet[destStationName], stationsSet[origStationName], service, capacity));
}

std::unordered_map<std::string, Station *> Graph::getStationSet() const {
    return this->stationsSet;
}
