#ifndef PROJECT1_STATION_H
#define PROJECT1_STATION_H

#include <string>
#include <vector>
#include "Network.h"

class Station {
private:
    std::string name;
    std::string district;
    std::string municipality;
    std::string township;
    std::string line;

    std::vector<Network *> adj;

    double dist = 0;
    bool visited = false;
    Network *path = nullptr;

    std::vector<Network *> incoming;

public:
    Station(std::string name, std::string district, std::string municipality, std::string townships,std::string line);

    Network *addNetwork(Station *dest, int capacity, Service service);

    Network *addIncoming(Network *incomingNetwork);

    bool removeNetwork(std::string destStationName ,Service service);

    bool removeIncoming(std::string origStationName, Service service);

    int getInDegree() const;

    int getDegree() const;

    const std::vector<Network *> &getAdj() const;

    const std::vector<Network *> &getIncoming() const;

    const std::string &getName() const;

    void setName(const std::string &n);

    const std::string &getDistrict() const;

    void setDistrict(const std::string &distric);

    const std::string &getMunicipality() const;

    void setMunicipality(const std::string &m);

    const std::string &getTownship() const;

    void setTownship(const std::string &t);

    const std::string &getLine() const;

    void setLine(const std::string &l);

    double getDist() const;

    void setDist(double d);

    bool isVisited() const;

    void setVisited(bool v);

    Network *getPath() const;

    void setPath(Network *p);
};


#endif //PROJECT1_STATION_H
