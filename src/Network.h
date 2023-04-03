#ifndef PROJECT1_NETWORK_H
#define PROJECT1_NETWORK_H

#include "Station.h"

enum Service{STANDARD, ALFA_PENDULAR};

Service convert(std::string conversion) {
    if(conversion == "STANDARD") return STANDARD;
    if(conversion == "ALFA_PENDULAR") return ALFA_PENDULAR;
}

class Network {
private:
    Service service;
    Station *dest;
    int capacity;

    int flow = 0;

    Station *orig;
    Network *reverse = nullptr;
public:
    Network(Station *dest, Station *orig, Service service, int capacity);

    Service getService() const;

    void setService(Service service);

    Station *getDest() const;

    void setDest(Station *dest);

    int getCapacity() const;

    void setCapacity(int capacity);

    int getFlow() const;

    void setFlow(int flow);

    Station *getOrig() const;

    void setOrig(Station *orig);

    Network *getReverse() const;

    void setReverse(Network *reverse);
};


#endif //PROJECT1_NETWORK_H
