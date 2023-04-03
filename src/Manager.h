#ifndef PROJECT1_MANAGER_H
#define PROJECT1_MANAGER_H

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

    int inputStation(Station *station, std::string message);
};



#endif //PROJECT1_MANAGER_H
