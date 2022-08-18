//
// Created by plcla on 8/16/2022.
//

#ifndef GRAPHSPRACTICE_GRAPH_H
#define GRAPHSPRACTICE_GRAPH_H

#include <cstdint>
#include <string>
#include <vector>
#include <list>

class Edge {
private:
    // .first = destination ID | .second = distance to airport (miles)
    std::list<std::pair<int32_t, int32_t>> connections;

public:
    Edge() : connections(0) {};
    Edge(const std::vector<std::pair<std::string, int32_t>>& routes);

    std::list<std::pair<int32_t, int32_t>> getConnections();
};

class Component {
private:
    int32_t IDNumber;
    std::string airportCode;
    Edge directFlights;

public:
    Component(const std::string& airportCode, const std::vector<std::pair<std::string, int32_t>>& routes);

    int32_t getUniqueID();
    Edge getEdges();
};

class Graph {
private:
    std::vector<Component> graph;

public:
    Graph(const std::vector<std::string>& startingAirports, const std::vector<std::vector<std::pair<std::string, int32_t>>>& potentialEndpoints);

    void showAdjacencyList();
    void showAdjacencyMatrix();
};


#endif //GRAPHSPRACTICE_GRAPH_H
