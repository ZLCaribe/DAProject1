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

    //Basic Service Metrics
    double maxFlowPair(Station *s, Station *t);
    std::vector<Station *> getPairsWithMaxFlow();
    //TODO - 2.3. Municipios/Distritos com maior flow?
    double maxStationFlow(Station *station);

    //Operation Cost Optmization
    double costOptmizationMaxFlowPair(Station *s, Station *t);

    //Reliability and Sensitivity to Line Failures
    Graph generateSubGraph();
    std::vector<std::pair<Station,int>> mostAffectedStations(const Graph& subgraph, int k);
};


#endif //PROJECT1_GRAPH_H

