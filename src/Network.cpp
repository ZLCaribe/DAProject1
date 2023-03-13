#include "Network.h"

Service Network::getService() const {
    return service;
}

void Network::setService(Service service) {
    Network::service = service;
}

Station *Network::getDest() const {
    return dest;
}

void Network::setDest(Station *dest) {
    Network::dest = dest;
}

int Network::getCapacity() const {
    return capacity;
}

void Network::setCapacity(int capacity) {
    Network::capacity = capacity;
}

int Network::getFlow() const {
    return flow;
}

void Network::setFlow(int flow) {
    Network::flow = flow;
}

Station *Network::getOrig() const {
    return orig;
}

void Network::setOrig(Station *orig) {
    Network::orig = orig;
}

Network *Network::getReverse() const {
    return reverse;
}

void Network::setReverse(Network *reverse) {
    Network::reverse = reverse;
}

Network::Network(Station *dest, Station *orig, Service service, int capacity): dest(dest), service(service),
    capacity(capacity), orig(orig) {}
