#ifndef PROJECT1_VERTEXEDGE_H
#define PROJECT1_VERTEXEDGE_H

#include <string>
#include <vector>

class Edge;
class Vertex {
    public:
        Vertex(std::string name, std::string district, std::string municipality, std::string township, std::string line);

        std::string getName();
        std::string getDistrict();
        std::string getMunicipality();
        std::string getTownship();
        std::string getLine();

        bool isVisited();
        Edge* getPath();
        std::vector<Edge*> getEdges();

        void setVisited(bool visited);
        void setPath(Edge* path);

        void addEdge(Vertex* dest, int capacity, const std::string& service);
        void deleteEdge(Edge* edge);

    protected:
        std::string name;
        std::string district;
        std::string municipality;
        std::string township;
        std::string line;
        bool visited = false;

        Edge* path = nullptr;
        std::vector<Edge*> edges;
};

class Edge {
    public:
        Edge(Vertex* orig, Vertex* dest, int capacity, std::string service);

        Vertex* getDest() const;
        Vertex* getOrig() const;
        int getCapacity() const;
        int getOccupied() const;
        std::string getService();

        void setOccupied(int occupied);
        void reset();

    protected:
        Vertex* orig;
        Vertex* dest;

        std::string service;
        int capacity;
        int occupied = 0;
        double flow = 0;
};

#endif
