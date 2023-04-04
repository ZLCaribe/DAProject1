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
    Vertex *findStation(const std::string& name);
    void addStation(const std::string& name, const std::string& district, const std::string& municipality,
                    const std::string& township, const std::string& line);
    void addNetwork(const std::string& orig, const std::string& dest, int capacity, const std::string& service);
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

