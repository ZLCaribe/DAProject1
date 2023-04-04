#include "VertexEdge.h"

Vertex::Vertex(std::string name, std::string district, std::string municipality,
               std::string township, std::string line): 
               name(name), district(district), municipality(municipality), township(township), line(line) {}

std::string Vertex::getName() {
    return name;
}

std::string Vertex::getDistrict() {
    return district;
}

std::string Vertex::getMunicipality() {
    return municipality;
}

std::string Vertex::getTownship() {
    return township;
}

std::string Vertex::getLine() {
    return line;
}

bool Vertex::isVisited() { 
    return visited; 
}

Edge* Vertex::getPath() { 
    return path; 
}

std::vector<Edge*> Vertex::getEdges() { 
    return edges; 
}

void Vertex::setVisited(bool visited) {
    this->visited = visited;
}

void Vertex::setPath(Edge* path) {
    this->path = path;
}

void Vertex::addEdge(Vertex* dest, int capacity, const std::string& service) {
    edges.push_back(new Edge(this,dest,capacity,service));
}

void Vertex::deleteEdge(Edge* edge) {
    for(auto i = edges.begin(); i != edges.end(); i++) {
        if(*i == edge) {
            edges.erase(i);
            break;
        }
    }
}

Edge::Edge(Vertex* orig, Vertex* dest, int capacity, std::string service): 
            orig(orig), dest(dest), capacity(capacity), service(service) {}

Vertex* Edge::getDest() const { 
    return dest; 
}

Vertex* Edge::getOrig() const { 
    return orig; 
}

int Edge::getCapacity() const {
    return capacity;
}

int Edge::getOccupied() const {
    return occupied;
}

std::string Edge::getService() { 
    return service;
}

void Edge::setOccupied(int occupied) {
    this->occupied = occupied;
}
