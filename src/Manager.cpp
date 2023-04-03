#include "Manager.h"

Manager::Manager() {}

void Manager::readFiles() {
    bool ignore = true;
    bool fileSwitch = false;

    std::fstream file ("../stations.csv", std::ios::in);

    std::string entry;
    std::string first, second, third, fourth, fifth;

    if(file.is_open()) {
        while(getline(file, entry)) {
            if(ignore) {
                ignore = false;
            } else {
                std::stringstream station(entry);

                getline(station, first, ',');
                getline(station, second, ',');
                getline(station, third, ',');
                getline(station, fourth, ',');
                getline(station, fifth, ',');

                graph.addStation(Station(first, second, third, fourth, fifth));
            }
        }
    }

    std::fstream file ("../network.csv", std::ios::in);

    if(file.is_open()) {
        while(getline(file, entry)) {
            if(ignore) {
                ignore = false;
            } else {
                std::stringstream station(entry);

                getline(station, first, ',');
                getline(station, second, ',');
                getline(station, third, ',');
                getline(station, fourth, ',');



                graph.addNetwork(first, second, stoi(third), convert(fourth));
            }
        }
    }

}
