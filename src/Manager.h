#ifndef PROJECT1_MANAGER_H
#define PROJECT1_MANAGER_H

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

#include "Graph.h"

class Manager {
private:
    Graph graph;
public:
    Manager();
    void readFiles();

    void mainMenu();
    void basicMetricsMenu();

    void costOptmization();
    void testLineFailures();

    int inputStation(Vertex *station, const std::string& message);
};



#endif //PROJECT1_MANAGER_H
