#include "Graph.h"

Graph::Graph() {}

Station *Graph::findStation(std::string name) const {
    //TODO
}

bool Graph::addStation(Station station) {
    //TODO
}

bool Graph::addNetwork(std::string origStationName, std::string destStationName, int capacity, Service service) {
    //TODO
}

std::vector<Station *> Graph::getStationSet() const {
    return this->stationsSet;
}
