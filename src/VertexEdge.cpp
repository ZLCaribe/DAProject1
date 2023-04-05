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

void Vertex::deleteEdge(Edge* edge) {
    for(auto i = edges.begin(); i != edges.end(); i++) {
        if(*i == edge) {
            edges.erase(i);
            break;
        }
    }
}

void Vertex::addEdge(Edge *edge) {
    this->edges.push_back(edge);
}

void Vertex::reset() {
    this->visited = false;
    for(Edge *e : this->edges) e->reset();
}

Edge::Edge(Vertex* orig, Vertex* dest, int capacity, std::string service):
            orig(orig), dest(dest), capacity(capacity), service(std::move(service)), reverse(nullptr) {}

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

void Edge::setOccupied(int occup) {
    this->occupied = occup;
}

Edge *Edge::getReverse() const {
    return this->reverse;
}

Edge::Edge(Vertex* orig, Vertex* dest, int capacity, std::string service, Edge *reverse):
        orig(orig), dest(dest), capacity(capacity), service(std::move(service)), reverse(reverse) {}

void Edge::setReverse(Edge *rev) {
    this->reverse = rev;
}

void Edge::reset() {
    this->occupied = 0;
}
