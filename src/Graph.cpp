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

/**
 * Calculate the maximum number of trains that can simultaneously travel between
 * two specific stations. Note that your implementation should take any valid source and destination
 * stations as input.
 * @param s source station
 * @param t target station
 * @return maximum number of trains
 */
double Graph::maxFlowPair(Station *s, Station *t) {
    //TODO
    return 0;
}

/**
 * Determine, from all pairs of stations, which ones (if more than one) require the
 * most amount of trains when taking full advantage of the existing network capacity
 * @return Stations with biggest flow capacity being the odd indexes stations the
 * source and the even indexes the target
 */
std::vector<Station *> Graph::getPairsWithMaxFlow() {
    return {};
}

/**
 * Report the maximum number of trains that can simultaneously arrive at a given station,
 * taking into consideration the entire railway grid.
 * @param station
 * @return maximum number of trains
 */
double Graph::maxStationFlow(Station *station) {
    //TODO
    //Adicionar nós temporários com arestas de capacidade infinita para os nós que só tem uma aresta
    //depois usar maxFlowPair para calcular resultado
    return 0;
}

/**
 * Calculate the maximum amount of trains that can simultaneously travel between
 * two specific stations with minimum cost for the company
 * @param s source station
 * @param t target station
 * @return Minimum cost of the route
 */
double Graph::costOptmizationMaxFlowPair(Station *s, Station *t) {
    //TODO
    //Ainda não sei o algoritmo que vou usar para calcular o caminho e flow com custo mínimo
    return 0;
}

/**
 * Creates a new graph that is a subgraph of the original one
 * @return subgraph
 */
Graph Graph::generateSubGraph() {
    //TODO
    //Precisamos decidir o que vamos mudar no grafo original
    return {};
}

/**
 * Provide a report on the stations that are the most affected by each segment failure,
 * i.e., the top-k most affected stations for each segment to be considered.
 * @param subgraph original with reduced connectivity
 * @param k number of station to return
 * @return vector of pairs(TODO maybe a heap, or anything that sort automatically could be a better idea)
 * where the first component is the name of the station and the second is how much the flow
 * of the station was reduced
 */
std::vector<std::pair<Station, int>> Graph::mostAffectedStations(const Graph& subgraph, int k) {
    //Comparar a utilização da função maxFlowPair no grafo original com a utilização dela no subgrafo
    //para todos os pares, a redução a ser colocada no vetor de retorno deve ser a soma de
    //todas as diminuições quando a estação está como destino ou origem, ordenar o vetor pelo int,
    //depois remover do vetor as que passarem do top-k

    //OPÇÃO 2
    //Podemos usar a função maxStationFlow para comparar, deve ser BEM mais fácil e faz sentido tb
    return {};
}
