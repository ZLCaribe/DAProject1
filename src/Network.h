#ifndef PROJECT1_NETWORK_H
#define PROJECT1_NETWORK_H

#include "Station.h"

enum Service{STANDARD, ALFA_PENDULAR};

class Network {
private:
    Service service;
    Station *dest;
    int capacity;

    int flow;
public:
    Network(Station *dest, Service service, int capacity);
};


#endif //PROJECT1_NETWORK_H
