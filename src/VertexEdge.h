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

        void addEdge(Edge *edge);
        void deleteEdge(Edge* edge);

        void reset();

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
        Edge(Vertex* orig, Vertex* dest, int capacity, std::string service, Edge *reverse);

        Vertex* getDest() const;
        Vertex* getOrig() const;
        int getCapacity() const;
        int getOccupied() const;
        std::string getService();
        Edge *getReverse() const;

        void setOccupied(int occup);
        void setReverse(Edge *rev);
        void reset();

    protected:
        Vertex* orig;
        Vertex* dest;

        Edge *reverse{};

        std::string service;
        int capacity;
        int occupied = 0;
        double flow = 0;
};

#endif
