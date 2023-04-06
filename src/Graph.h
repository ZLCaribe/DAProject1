#ifndef PROJECT1_GRAPH_H
#define PROJECT1_GRAPH_H

#include <iostream>
#include <string>
#include <unordered_map>
#include <queue>

#include "VertexEdge.h"

class Graph {
private:
    std::unordered_map<std::string, Vertex *> stationsSet;
public:
    Graph();
    Vertex *findStation(const std::string& name);
    void addStation(const std::string& name, const std::string& district, const std::string& municipality,
                    const std::string& township, const std::string& line);
    void removeStation(Vertex *v);
    void addNetwork(const std::string& orig, const std::string& dest, int capacity, const std::string& service);
    static void removeNetwork(Vertex * v, Vertex *t);
    std::unordered_map<std::string, Vertex *> getStationSet() const;

    bool findAugmentingPath(Vertex *s, Vertex *t);
    static int findMinResidualAlongPath(Vertex *s, Vertex *t);
    static void testAndVisit(std::queue<Vertex *>& q, Edge *e, Vertex *w, int residual);
    static void augmentFlowAlongPath(Vertex *s, Vertex *t, int f);

    //Operation Cost Optmization
    int costOptmizationMaxFlowPair(Vertex *s, Vertex *t);

    //Reliability and Sensitivity to Line Failures
    Graph generateSubGraph(std::vector<Vertex*> toRemove);
    std::vector<std::pair<Vertex,int>> mostAffectedStations(const Graph& subgraph, int k);

    //Basic Service Metrics
    int maxFlowPair(Vertex *s, Vertex *t);
    std::pair<int, std::vector<Vertex *>> getPairsWithMaxFlow();
    //TODO - 2.3. Municipios/Distritos com maior flow?
    int maxStationFlow(Vertex *station);
};


#endif //PROJECT1_GRAPH_H

