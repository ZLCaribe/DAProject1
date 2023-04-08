#include "Graph.h"

#include <utility>
#include <iostream>
#include <queue>
#include <unordered_map>

#define INF std::numeric_limits<int>::max()

Graph::Graph() = default;

Vertex *Graph::findStation(const std::string& name) {
    if (this->stationsSet.find(name) != this->stationsSet.end())
        return this->stationsSet[name];
    return nullptr;
}

void Graph::addStation(const std::string& name, const std::string& district, const std::string& municipality,
                       const std::string& township, const std::string& line) {
    if(this->findStation(name) == nullptr) {
        this->stationsSet[name] = new Vertex(name, district, municipality, township, line);
    }else{
        //std::cout << std::endl << "###########REPETIDO" << ++cnt << "###########" << std::endl;
    }
}

void Graph::addNetwork(const std::string& orig, const std::string& dest, int capacity, const std::string& service) {
    if(this->findStation(orig) != nullptr && this->findStation(dest) != nullptr) {
        for(auto &a : this->stationsSet[orig]->getEdges()){
            if(a->getDest()->getName() == dest && a->getService() == service){
                //std::cout << "duplicate edge found: " << orig << " - " << dest << std::endl;
                return;
            }
        }
        Edge *edge1 = new Edge(this->stationsSet[orig],this->stationsSet[dest],capacity / 2, service);
        Edge *edge2 = new Edge(this->stationsSet[dest],this->stationsSet[orig],capacity / 2, service, edge1);
        edge1->setReverse(edge2);
        this->stationsSet[orig]->addEdge(edge1);
        this->stationsSet[dest]->addEdge(edge2);
    }
}

std::unordered_map<std::string, Vertex *> Graph::getStationSet() const {
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
int Graph::maxFlowPair(Vertex *s, Vertex *t) {
    int maxFlow = 0;
    //reset all vertexes and edges
    for(auto & it : this->stationsSet){
        Vertex *v = it.second;
        v->reset();
    }
    // repeat until there is no more augmenting path from s to t
    while (findAugmentingPath(s, t)){
        int f = findMinResidualAlongPath(s,t);
        augmentFlowAlongPath(s,t,f);
        maxFlow += f;
    }
    return maxFlow;
}

/**
 * Determine, from all pairs of stations, which ones (if more than one) require the
 * most amount of trains when taking full advantage of the existing network capacity
 * @return Stations with biggest flow capacity being the odd indexes stations the
 * source and the even indexes the target
 */
std::pair<int,std::vector<Vertex *>> Graph::getPairsWithMaxFlow() {
    std::vector<Vertex *> r;
    int f = 0;
    for(auto it1 = this->stationsSet.begin(); it1 != this->stationsSet.end(); it1++){
        if(it1 != this->stationsSet.end()) {
            auto it2 = it1;
            it2++;
            for (; it2 != this->stationsSet.end(); it2++) {
                int n = maxFlowPair(it1->second, it2->second);
                if (n > f) {
                    r.erase(r.begin(),r.end());
                    r.push_back(it1->second);
                    r.push_back(it2->second);
                    f = n;
                } else if (n == f) {
                    r.push_back(it1->second);
                    r.push_back(it2->second);
                } else continue;
            }
        }
    }
    return {f,r};
}

/**
 * Report the maximum number of trains that can simultaneously arrive at a given station,
 * taking into consideration the entire railway grid.
 * @param station
 * @return maximum number of trains
 */
int Graph::maxStationFlow(Vertex *station) {
    //Adicionar nós temporários com arestas de capacidade infinita para os nós que só tem uma aresta
    //depois usar maxFlowPair para calcular resultado (to be discussed)
    this->addStation("Infinite sink","nowhere", "anywhere", "I don't know", "none");
    for(auto v : this->stationsSet) if(v.second->getEdges().size() == 1 && v.second != station) {
        this->addNetwork("Infinite sink",v.first,INT32_MAX,"STANDARD");
    }
    int r = this->maxFlowPair(this->stationsSet["Infinite sink"],station);
    auto i  = this->stationsSet["Infinite sink"];
    while(!i->getEdges().empty()) removeNetwork(i,i->getEdges().begin().operator*()->getDest());
    this->removeStation(this->stationsSet["Infinite sink"]);
    return r;
}

/**
 * Calculate the maximum amount of trains that can simultaneously travel between
 * two specific stations with minimum cost for the company
 * @param s source station
 * @param t target station
 * @return Minimum cost of the route
 */
std::pair<int,int> Graph::costOptmizationMaxFlowPair(Vertex *s, Vertex *t) {
    std::unordered_map<Vertex* ,std::pair<int, std::vector<Edge*>>> travelPaths;

	for(auto a : this->stationsSet){
		a.second->setVisited(false);
	}

	std::queue<Vertex*> q;
	q.push(s);
	s->setVisited(true);

	if(s==t) return {};

	while(!q.empty()){
		for(auto e : q.front()->getEdges()){
			Vertex* target = e->getDest();
			if(!target->isVisited() || travelPaths[q.front()].first + e->getWeight() < travelPaths[target].first){
				travelPaths[target] = {travelPaths[q.front()].first + e->getWeight(), travelPaths[q.front()].second};
				travelPaths[target].second.push_back(e);
				q.push(target);
				target->setVisited(true);
			}
		}
		q.pop();
	}

	std::vector<Edge*> path;
	//path.push_back(s);
	for(auto a : travelPaths[t].second){
		path.push_back(a);
	}

	int min=INT32_MAX;
	for(auto b : path){
		std::cout << b->getOrig()->getName() << " - " << b->getDest()->getName() << std::endl;
		if(b->getCapacity()<min) min = b->getCapacity();
	}
    return {travelPaths[t].first * min,min};
}

/**
 * Creates a new graph that is a subgraph of the original one
 * @return subgraph
 */
Graph Graph::generateSubGraph(std::vector<Vertex*> toRemove) {
    Graph subGraph = *this;
    for(auto i = toRemove.begin(); i != toRemove.end(); i += 2) {
        subGraph.removeNetwork(*i, *i + 1);
    }
    return subGraph;
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
std::vector<std::pair<Vertex, int>> Graph::mostAffectedStations(const Graph& subgraph, int k) {
    //Comparar a utilização da função maxFlowPair no grafo original com a utilização dela no subgrafo
    //para todos os pares, a redução a ser colocada no vetor de retorno deve ser a soma de
    //todas as diminuições quando a estação está como destino ou origem, ordenar o vetor pelo inteiro,
    //depois remover dele as que passarem do ‘top-k’

    //OPÇÃO 2
    //Podemos usar a função maxStationFlow para comparar, deve ser BEM mais fácil e faz sentido também
    //Essa opção ficou um pouco menos viável quando parei para pensar que não sem muito bem como fazer maxStationFlow
    return {};
}

bool Graph::findAugmentingPath(Vertex *s, Vertex *t) {
    for(auto v : this->stationsSet) v.second->setVisited(false);
    //BFS
    s->setVisited(true);
    std::queue<Vertex *> q;
    q.push(s);
    while(!q.empty() && !t->isVisited()){
        Vertex *v = q.front();
        q.pop();
        for(auto e : v->getEdges()){
            testAndVisit(q, e, e->getDest(), e->getCapacity() - e->getOccupied());
        }
        for(auto e : v->getEdges()){
            testAndVisit(q, e->getReverse(), e->getOrig(), e->getOccupied());
        }
    }
    return t->isVisited();
}

void Graph::testAndVisit(std::queue<Vertex *>& q, Edge *e, Vertex *w, int residual) {
    if(!w->isVisited() && residual > 0){
        w->setVisited(true);
        w->setPath(e);
        q.push(w);
    }
}

int Graph::findMinResidualAlongPath(Vertex *s, Vertex *t) {
    int f = INT32_MAX;
    for (auto v = t; v != s; ) {
        auto e = v->getPath();
        if (e->getDest() == v) {
            f = std::min(f, e->getCapacity() - e->getOccupied());
            v = e->getOrig();
        }
        else {
            f = std::min(f, e->getOccupied());
            v = e->getDest();
        }
    }
    return f;
}

void Graph::augmentFlowAlongPath(Vertex *s, Vertex *t, int f) {
    for(auto v = t; v != s;){
        auto e = v->getPath();
        auto flow = e->getOccupied();
        if(e->getDest() == v){
            e->setOccupied(flow + f);
            v = e->getOrig();
        }else{
            e->setOccupied(flow - f);
            v = e->getDest();
        }
    }
}

void Graph::removeStation(Vertex *v) {
    this->stationsSet.erase(v->getName());
}

void Graph::removeNetwork(Vertex *s, Vertex *t) {
    s->deleteEdge(t);
    t->deleteEdge(s);
}

bool compPair(const std::pair<std::string, int>& p1, const std::pair<std::string, int>& p2){
    return p1.second > p2.second;
}

std::vector<std::pair<std::string, int>> Graph::getBudgetPriorities(bool MorD, int k) {
    std::unordered_map<std::string ,int> r;
    for(const auto& it : this->stationsSet){
        Vertex *station = it.second;
        std::string pos =  MorD?station->getDistrict():station->getMunicipality();
        if(r.find(pos) == r.end()) r[pos] = this->maxStationFlow(station);
        else r[pos] = r[pos] + this->maxStationFlow(station);
    }
    std::vector<std::pair<std::string ,int>> v = {};
    for(const auto& it : r){
        v.emplace_back(it);
    }
    std::sort(v.begin(), v.end(), compPair);
    if(k < v.size()) v.erase(v.begin() + k,v.end());
    return v;
}
