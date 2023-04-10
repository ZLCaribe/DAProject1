#include "VertexEdge.h"

#include <utility>

/**
 * Vertex constructor 
 * @param name station's name
 * @param district station's district
 * @param municipality station's municipality
 * @param township station's township
 * @param line station's line
 */
Vertex::Vertex(std::string name, std::string district, std::string municipality,
               std::string township, std::string line):
               name(std::move(name)), district(std::move(district)), municipality(std::move(municipality)),
               township(std::move(township)), line(std::move(line)) {}

/**
 * Edge constructor
 * @param orig edge's origin
 * @param dest edge's destination
 * @param capacity edge's capacity
 * @param service edge's service
 */
Edge::Edge(Vertex* orig, Vertex* dest, int capacity, const std::string& service):
        orig(orig), dest(dest), capacity(capacity), service(service), reverse(nullptr) {
    if(service == "ALFA PENDULAR") this->weight = 4;
    else this->weight = 2;
}

/**
 * Edge constructor
 * @param orig edge's origin
 * @param dest edge's destination
 * @param capacity edge's capacity
 * @param service edge's service
 */
Edge::Edge(Vertex* orig, Vertex* dest, int capacity, const std::string& service, Edge *reverse):
        orig(orig), dest(dest), capacity(capacity), service(service), reverse(reverse) {
    if(service == "ALFA PENDULAR") this->weight = 4;
    else this->weight = 2;
}

/**
 * returns the Vertex's name
 * @return name
 */
std::string Vertex::getName() {
    return name;
}

/**
 * returns the Vertex's District
 * @return District
 */
std::string Vertex::getDistrict() {
    return district;
}

/**
 * returns the Vertex's Municipality
 * @return Municipality
 */
std::string Vertex::getMunicipality() {
    return municipality;
}

/**
 * returns the Vertex's Township
 * @return Township
 */
std::string Vertex::getTownship() {
    return township;
}

/**
 * returns the Vertex's Line
 * @return Line
 */
std::string Vertex::getLine() {
    return line;
}

/**
 * returns wether or not the Vertex is visited
 * @return visited
 */
bool Vertex::isVisited() {
    return visited;
}

/**
 * returns the Vertex's Path
 * @return Path
 */
Edge* Vertex::getPath() {
    return path;
}

/**
 * returns the Vertex's connected edges
 * @return vector of pointers to Edge
 */
std::vector<Edge*> &Vertex::getEdges() {
    return edges;
}

/**
 * changes the value of the Vertex's visited variable
 * @param visited 
 */
void Vertex::setVisited(bool visited) {
    this->visited = visited;
}

/**
 * sets the Edge's path variable
 * @param path
 */
void Vertex::setPath(Edge* path) {
    this->path = path;
}

/**
 * delets an Edge from the vertex
 * @param v edges destination vertex
 */
void Vertex::deleteEdge(Vertex *v) {
    for(auto i = edges.begin(); i != edges.end(); i++) {
        if((*i)->getDest() == v) {
            edges.erase(i);
            break;
        }
    }
}

/**
 * adds an Edge to the vertex
 * @param edge
 */
void Vertex::addEdge(Edge *edge) {
    this->edges.push_back(edge);
}

/**
 * toggles the visited variable to false
 */
void Vertex::reset() {
    this->visited = false;
    for(Edge *e : this->edges) e->reset();
}

/**
 * returns the Vertex's distance
 * @return int 
 */
int Vertex::getDist() const {
    return this->dist;
}

/**
 * gives a value to the Vexte's distance
 * @param d distance
 */
void Vertex::setDist(int d) {
    this->dist = d;
}

/**
 * disconnects this Vextex to another
 * @param t Vertex at the other end of the edge
 */
void Vertex::disconnectEdge(Vertex* t) {
   for(auto a: this->getEdges()){
    if(a->getDest()==t){
        a->switchEdge();
    }
   }
   for(auto b: t->getEdges()){
    if(b->getDest() == this){
        b->switchEdge();
    }
   }
}

bool Vertex::operator<(const Vertex *v) const {
    return this->dist > v->dist;
}

/**
 * returns the edge's Destination
 * @return Vertex* 
 */
Vertex* Edge::getDest() const {
    return dest;
}

/**
 * returns the edge's Origin
 * @return Vertex* 
 */
Vertex* Edge::getOrig() const {
    return orig;
}

/**
 * returns the edge's maximum capacity
 * @return int 
 */
int Edge::getCapacity() const {
    return capacity;
}

/**
 * returns the Edge's occupation
 * @return int 
 */
int Edge::getOccupied() const {
    return occupied;
}

/**
 * returns the edge's service provider
 * @return string 
 */
std::string Edge::getService() {
    return service;
}

/**
 * sets the Edge's occupation
 * @param occup 
 */
void Edge::setOccupied(int occup) {
    this->occupied = occup;
}

/**
 * switches wether or not the edge is in the subgraph
 * 
 */
void Edge::switchEdge() {
    subgraph = !subgraph;
}

/**
 * returns the Edge's reverse edge
 * @return Edge* 
 */
Edge *Edge::getReverse() const {
    return this->reverse;
}

/**
 * sets an Edge as the reverse to this edge
 * @param rev reverse edge
 */
void Edge::setReverse(Edge *rev) {
    this->reverse = rev;
}

/**
 * resets the edges occupation
 */
void Edge::reset() {
    this->occupied = 0;
}

/**
 * returns an edges train operation cost
 * @return int 
 */
int Edge::getWeight() const {
    return this->weight;
}

/**
 * returns wether or not the edge belongs in the subgraph
 * @return subgraph
 */
bool Edge::getSwitch() { 
    return subgraph; 
}