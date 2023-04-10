#include "Graph.h"

#include <utility>
#include <algorithm>
#include <iostream>
#include <queue>
#include <unordered_map>

#define INF std::numeric_limits<int>::max()

Graph::Graph() = default;

/**
 * Return a pointer to a Vertex, being given it's name. 
 * Complexity: O(1) in average but O(n) in the worst case
 * @param name station's name
 * @return pointer to a vertex
 */
Vertex *Graph::findStation(const std::string& name) {
    if (this->stationsSet.find(name) != this->stationsSet.end())
        return this->stationsSet[name];
    return nullptr;
}

/**
 * Adds a station to the graph. 
 * Complexity: O(1) in average but O(n) in the worst case
 * @param name station's name
 * @param district station's district
 * @param municipality station's municipality
 * @param township station's township
 * @param line station's line
 */
void Graph::addStation(const std::string& name, const std::string& district, const std::string& municipality,
                       const std::string& township, const std::string& line) {
    if(this->findStation(name) == nullptr) {
        this->stationsSet[name] = new Vertex(name, district, municipality, township, line);
    }
}

/**
 * Adds a edge to the graph
 * Complexity: O(n)
 * @param orig edge's origin
 * @param dest edge's destination
 * @param capacity edge's capacity
 * @param service edge's service
 */
void Graph::addNetwork(const std::string& orig, const std::string& dest, int capacity, const std::string& service) {
    if(this->findStation(orig) != nullptr && this->findStation(dest) != nullptr) {
        for(auto &a : this->stationsSet[orig]->getEdges()){
            if(a->getDest()->getName() == dest && a->getService() == service){
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

/**
 * StationSet's getter
 * @return StationSet
 */
std::unordered_map<std::string, Vertex *> Graph::getStationSet() const {
    return this->stationsSet;
}

/**
 * Calculate the maximum number of trains that can simultaneously travel between
 * two specific stations.
 * stations as input.
 * Complexity: O(|V|*|E|^2)
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
 * Calculate the maximum number of trains that can simultaneously travel between
 * two specific stations in a network of reduced connectivity.
 * Complexity: O(|V|*|E|^2)
 * @param s source station
 * @param t target station
 * @return maximum number of trains
 */
int Graph::subMaxFlowPair(Vertex *s, Vertex *t) {
    int maxFlow = 0;
    //reset all vertexes and edges
    for(auto & it : this->stationsSet){
        Vertex *v = it.second;
        v->reset();
    }
    // repeat until there is no more augmenting path from s to t
    while (subFindAugmentingPath(s, t)){
        int f = findMinResidualAlongPath(s,t);
        augmentFlowAlongPath(s,t,f);
        maxFlow += f;
    }
    return maxFlow;
}

/**
 * Determine, from all pairs of stations, which ones (if more than one) require the
 * most amount of trains when taking full advantage of the existing network capacity
 * Complexity: O(|V|^2 * (|V| * |E|^2))
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
 * Complexity: O(|V| * |E|^2)
 * @param station
 * @return maximum number of trains
 */
int Graph::maxStationFlow(Vertex *station) {
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
 * Report the maximum number of trains that can simultaneously arrive at a given station,
 * taking into consideration the entire railway grid in a network of reduced connectivity.
 * Complexity: O(|V| * |E|^2)
 * @param station
 * @return maximum number of trains
 */
int Graph::submaxStationFlow(Vertex *station) {
    this->addStation("Infinite sink","nowhere", "anywhere", "I don't know", "none");
    for(auto v : this->stationsSet) if(v.second->getEdges().size() == 1 && v.second != station) {
        this->addNetwork("Infinite sink",v.first,INT32_MAX,"STANDARD");
    }
    int r = this->subMaxFlowPair(this->stationsSet["Infinite sink"],station);
    auto i  = this->stationsSet["Infinite sink"];
    while(!i->getEdges().empty()) removeNetwork(i,i->getEdges().begin().operator*()->getDest());
    this->removeStation(this->stationsSet["Infinite sink"]);
    return r;
}

/**
 * Calculate the maximum amount of trains that can simultaneously travel between
 * two specific stations with minimum cost for the company. 
 * Complexity: O(|E|+|V|)
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
 * Complexity: O(n)
 * @return subgraph
 */
void Graph::generateSubGraph(std::vector<Vertex*> edges) {
	for(auto i = 0; i < edges.size(); i += 2){
		edges[i]->disconnectEdge(edges[i+1]);
	}
}

bool sortHelper(std::pair<Vertex*, int> a, std::pair<Vertex*, int> b){
    return a.second > b.second;
}

/**
 * Provide a report on the stations that are the most affected by each segment failure,
 * i.e., the top-k most affected stations for each segment to be considered.
 * Complexity: O( |V| * (|V| * |E|^2))
 * @param k number of station to return
 * @return vector of pairs where the first component is the name of the station and the
 * second is how much the flow of the station was reduced
 */
std::vector<std::pair<Vertex*, int>> Graph::mostAffectedStations(int k) {
    int a, b;
    std::vector<std::pair<Vertex*, int>> temp, result;
   	for(auto i : this->stationsSet){
		a= maxStationFlow(i.second);
		b= submaxStationFlow(i.second);
		temp.push_back({i.second,a-b});
	}
   	
	std::sort(temp.begin(), temp.end(), sortHelper);

    for(int j=0; j<k; j++){
        result.push_back(temp[j]);
    }

	return result;
}

/**
 * Finds a path with available flow starting at vertex s and ending at vertex t
 * @param s starting point
 * @param t ending point
 * @return wheter or not there is an available path
 */
bool Graph::findAugmentingPath(Vertex *s, Vertex *t) {
    for(auto v : this->stationsSet) v.second->setVisited(false);
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

/**
 * Finds a path with available flow in a network of reduced connectivity
 * starting at vertex s and ending at vertex t
 * @param s starting point
 * @param t ending point
 * @return wheter or not there is an available path
 */
bool Graph::subFindAugmentingPath(Vertex *s, Vertex *t) {
    for(auto v : this->stationsSet) v.second->setVisited(false);
    s->setVisited(true);
    std::queue<Vertex *> q;
    q.push(s);
    while(!q.empty() && !t->isVisited()){
        Vertex *v = q.front();
        q.pop();
        for(auto e : v->getEdges()){
            if(e->getSwitch()) {
                testAndVisit(q, e, e->getDest(), e->getCapacity() - e->getOccupied());
            }
        }
        for(auto e : v->getEdges()){
            if(e->getSwitch()) {
                testAndVisit(q, e->getReverse(), e->getOrig(), e->getOccupied());
            }
        }
    }
    return t->isVisited();
}

/**
 * Test if a vertex was visited and has available flow capacity then visit it
 */
void Graph::testAndVisit(std::queue<Vertex *>& q, Edge *e, Vertex *w, int residual) {
    if(!w->isVisited() && residual > 0){
        w->setVisited(true);
        w->setPath(e);
        q.push(w);
    }
}

/**
 * Finds the minimal residual flow along path between vertex s and t
 * @param s start of the path
 * @param t end of the path
 * @return minimal residual flow along path
 */
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

/**
 * Updates vertexes flow values along path
 * @param s start of the path
 * @param t end of the path
 * @param f new flow
 */
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

/**
 * Removes a station from the set. 
 * Complexity: O(1) in average but O(n) in the worst case
 * @param v Vertex to be removed
 */
void Graph::removeStation(Vertex *v) {
    this->stationsSet.erase(v->getName());
}

/**
 * Removes a edge from the set
 * Complexity: O(n)
 * @param v origin Vertex to be removed
 * @param t origin Vertex to be removed
 */
void Graph::removeNetwork(Vertex *s, Vertex *t) {
    s->deleteEdge(t);
    t->deleteEdge(s);
}

bool compPair(const std::pair<std::string, int>& p1, const std::pair<std::string, int>& p2){
    return p1.second > p2.second;
}

/**
 * Report the top-k municipalities and districts, regarding their transportation needs
 * Complexity: O(|V| * (|V| * |E|^2))
 * @param MorD if true it will calculate municipalities if false it will calculate districts
 * @param k top-k municipalities/districts
 * @return vector of pairs in descending order by the second  attribute
 * the first atribute is the municipality/disctrict the second is the sum the maxStationFlow
 * of it's stations
 */
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
