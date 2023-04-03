#include "Station.h"

#include <utility>

using namespace std;

const string &Station::getName() const {
    return name;
}

void Station::setName(const string &n) {
    Station::name = n;
}

const string &Station::getDistrict() const {
    return district;
}

void Station::setDistrict(const string &distric) {
    Station::district = distric;
}

const string &Station::getMunicipality() const {
    return municipality;
}

void Station::setMunicipality(const string &m) {
    Station::municipality = m;
}

const string &Station::getTownship() const {
    return township;
}

void Station::setTownship(const string &t) {
    Station::township = t;
}

const string &Station::getLine() const {
    return line;
}

void Station::setLine(const string &l) {
    Station::line = l;
}

double Station::getDist() const {
    return dist;
}

void Station::setDist(double d) {
    Station::dist = d;
}

bool Station::isVisited() const {
    return visited;
}

void Station::setVisited(bool v) {
    Station::visited = v;
}

Network *Station::getPath() const {
    return path;
}

void Station::setPath(Network *p) {
    Station::path = p;
}

const vector<Network *> &Station::getAdj() const {
    return adj;
}

const vector<Network *> &Station::getIncoming() const {
    return incoming;
}

int Station::getInDegree() const {
    return (int)this->incoming.size();
}

int Station::getDegree() const {
    return (int)this->adj.size();
}

Network *Station::addIncoming(Network *incomingNetwork) {
    this->incoming.push_back(incomingNetwork);
}

Network *Station::addAdj(Network *network) {
    this->adj.push_back(network);
}

Station::Station(string name, string district, string municipality, string townships,
                 string line):name(std::move(name)), district(std::move(district)), municipality(std::move(municipality))
                 , township(std::move(townships)), line(std::move(line)){}

Network *Station::addNetwork(Station *dest, int capacity, Service service) {
    //TODO lembrar de fazer bidirecional divindo flow
}

bool Station::removeNetwork(std::string destStationName, Service service) {
    //TODO
}

bool Station::removeIncoming(std::string origStationName, Service service) {
    //TODO
}
