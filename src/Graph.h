#ifndef PROJECT1_GRAPH_H
#define PROJECT1_GRAPH_H

#include <iostream>
#include <string>
#include <unordered_map>

#include "VertexEdge.h"

class Graph {
private:
    std::unordered_map<std::string, Vertex *> stationsSet;
public:
    Graph();
    Vertex *findStation(std::string name) const;
    void addStation(std::string name, std::string district, std::string municipality, std::string township, std::string line);
    void addNetwork(std::string orig, std::string dest, int capacity, std::string service);
    std::unordered_map<std::string, Vertex *> getStationSet() const;

    //Basic Service Metrics
    double maxFlowPair(Vertex *s, Vertex *t);
    std::vector<Vertex *> getPairsWithMaxFlow();
    //TODO - 2.3. Municipios/Distritos com maior flow?
    double maxStationFlow(Vertex *Vertex);

    //Operation Cost Optmization
    double costOptmizationMaxFlowPair(Vertex *s, Vertex *t);

    //Reliability and Sensitivity to Line Failures
    Graph generateSubGraph();
    std::vector<std::pair<Vertex,int>> mostAffectedStations(const Graph& subgraph, int k);
};


#endif //PROJECT1_GRAPH_H

