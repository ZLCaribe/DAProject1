#include "VertexEdge.h"

#include <utility>

Vertex::Vertex(std::string name, std::string district, std::string municipality,
               std::string township, std::string line):
               name(std::move(name)), district(std::move(district)), municipality(std::move(municipality)),
               township(std::move(township)), line(std::move(line)) {}

Edge::Edge(Vertex* orig, Vertex* dest, int capacity, const std::string& service):
        orig(orig), dest(dest), capacity(capacity), service(service), reverse(nullptr) {
    if(service == "ALFA PENDULAR") this->weight = 4;
    else this->weight = 2;
}

Edge::Edge(Vertex* orig, Vertex* dest, int capacity, const std::string& service, Edge *reverse):
        orig(orig), dest(dest), capacity(capacity), service(service), reverse(reverse) {
    if(service == "ALFA PENDULAR") this->weight = 4;
    else this->weight = 2;
}

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
    Vertex* vertex1 = edge->getDest();
    for(auto j = vertex1->getEdges().begin(); j != vertex1->getEdges().end(); j++) {
        if(*j == edge->getReverse()) {
            vertex1->getEdges().erase(j);
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

int Vertex::getDist() const {
    return this->dist;
}

void Vertex::setDist(int d) {
    this->dist = d;
}

bool Vertex::operator<(const Vertex *v) const {
    return this->dist > v->dist;
}

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

void Edge::setReverse(Edge *rev) {
    this->reverse = rev;
}

void Edge::reset() {
    this->occupied = 0;
}

int Edge::getWeight() const {
    return this->weight;
}
