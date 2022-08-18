//
// Created by plcla on 8/16/2022.
//

#include <iostream>
#include <unordered_map>
#include "Graph.h"

// .first = airport code | .second = unique ID
std::unordered_map<std::string, int32_t> um;
// .first = unique ID | .second = airport code
std::unordered_map<int32_t, std::string> inverseUM;
static int32_t IDTracker = 1;

Edge::Edge(const std::vector<std::pair<std::string, int32_t>>& routes) {
    for (const std::pair<std::string, int32_t>& route : routes)
        this->connections.emplace_back(um.at(route.first), route.second);
}

std::list<std::pair<int32_t, int32_t>> Edge::getConnections() {
    return this->connections;
}

Component::Component(const std::string& airportCode, const std::vector<std::pair<std::string, int32_t>>& routes) {
    this->IDNumber = um.at(airportCode);
    this->airportCode = airportCode;
    this->directFlights = Edge(routes);
}

int32_t Component::getUniqueID() {
    return this->IDNumber;
}

Edge Component::getEdges() {
    return this->directFlights;
}

Graph::Graph(const std::vector<std::string>& startingAirports, const std::vector<std::vector<std::pair<std::string, int32_t>>>& potentialEndpoints) {
    if (startingAirports.size() != potentialEndpoints.size()) {
        std::cout << "Invalid input; size of arrays don't match. Graph not created." << std::endl;
        return;
    }

    //Assign each airport a unique ID
    for (const std::string& airport : startingAirports) {
        um.insert(std::make_pair(airport, IDTracker));
        inverseUM.insert(std::make_pair(IDTracker, airport));
        IDTracker++;
    }

    for (int32_t index = 0; index < startingAirports.size(); index++)
        this->graph.emplace_back(Component(startingAirports[index], potentialEndpoints[index]));
}

void Graph::showAdjacencyList() {
    std::cout << "[" << std::endl;
    for (Component vertex : this->graph) {
        std::cout << "\t[";
        for (auto& correspondingPathsIt : vertex.getEdges().getConnections()) {
            if (correspondingPathsIt == vertex.getEdges().getConnections().back())
                std::cout << correspondingPathsIt.first;
            else
                std::cout << correspondingPathsIt.first << ",";
        }
        if (this->graph.back().getUniqueID() == vertex.getUniqueID())
            std::cout << "]" << std::endl;
        else
            std::cout << "], " << std::endl;
    }
    std::cout << "]" << std::endl;
}

void Graph::showAdjacencyMatrix() {
    std::cout << "[" << std::endl;
    for (Component vertex : this->graph) {
        // .first = unique ID | .second = airport code (doesn't really matter)
        std::unordered_map<int32_t, std::string> trueConnections;
        for (auto& correspondingPathsIt : vertex.getEdges().getConnections())
            trueConnections.insert(std::make_pair(correspondingPathsIt.first, inverseUM.at(correspondingPathsIt.first)));

        std::cout << "\t[";
        for (int32_t uniqueID = 1; uniqueID < IDTracker; uniqueID++) {
            if (uniqueID == IDTracker - 1) {
                (trueConnections.find(uniqueID) == trueConnections.end()) ? std::cout << "0" : std::cout << "1";
            }
            else {
                (trueConnections.find(uniqueID) == trueConnections.end()) ? std::cout << "0," : std::cout << "1,";
            }
        }
        if (this->graph.back().getUniqueID() == vertex.getUniqueID())
            std::cout << "]" << std::endl;
        else
            std::cout << "], " << std::endl;
    }
    std::cout << "]" << std::endl;
}