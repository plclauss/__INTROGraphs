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

Edge::Edge(const std::string& airportCode, const std::vector<std::pair<std::string, int32_t>>& routes) {
    for (const std::pair<std::string, int32_t>& route : routes) {
        if (um.find(route.first) == um.end()) {
            std::cout << route.first << " not in graph yet. Add " << route.first
                      << " first, and we'll ensure a back-and-forth connection exists." << std::endl;
            continue;
        }
        this->connections.emplace_back(um.at(route.first), route.second);
    }
}

std::list<std::pair<int32_t, int32_t>>& Edge::getConnections() {
    return this->connections;
}

Component::Component(const std::string& airportCode, const std::vector<std::pair<std::string, int32_t>>& routes) {
    this->IDNumber = um.at(airportCode);
    this->airportCode = airportCode;
    this->directFlights = Edge(airportCode, routes);
}

void Component::adjustID() {
    this->IDNumber--;
}

void Component::adjustIDs() {
    for (auto airport : this->getEdges().getConnections()) {
        if (airport.first >= this->getUniqueID()) {
            (airport.first)--;
        }
    }
    this->adjustID();
}

int32_t Component::getUniqueID() {
    return this->IDNumber;
}

Edge& Component::getEdges() {
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

int32_t Graph::hasConnection(Component newComponent, const int32_t previousComponentID) {
    std::list<std::pair<int32_t, int32_t>> newComponentList = newComponent.getEdges().getConnections();
    auto newComponentListIt = newComponentList.begin();
    while (newComponentListIt != newComponentList.end()) {
        if (newComponentListIt->first == previousComponentID)
            return newComponentListIt->second;
        newComponentListIt++;
    }
    return -1;
}

void Graph::addConnection(Component& previousComponent, std::pair<int32_t, int32_t> routeToAdd) {
    previousComponent.getEdges().getConnections().push_back(routeToAdd);
}

void Graph::addComponent(const std::string &airportCode, const std::vector<std::pair<std::string, int32_t>> &nonstopConnections) {
    if (um.find(airportCode) != um.end()) {
        std::cout << "Airport already in graph." << std::endl;
        return;
    }

    // add only the first parameter to graph
        // if there exists connections to airports not already in the graph, ignore them
        // later, if said "missing" airport is added to the graph, ensure there is a back and forth connection between airports
    um.insert(std::make_pair(airportCode, IDTracker));
    inverseUM.insert(std::make_pair(IDTracker, airportCode));
    IDTracker++;
    this->graph.emplace_back(Component(airportCode, nonstopConnections));

    //ensure back-and-forth connections
    for (Component& vertex : this->graph) {
        int32_t distanceBetweenFlights = hasConnection(this->graph.back(), vertex.getUniqueID());
        if (distanceBetweenFlights != -1) {
            addConnection(vertex, std::make_pair(this->graph.back().getUniqueID(), distanceBetweenFlights));
        }
    }
}

void Graph::removeFromConnections(Component& previousComponent, int32_t airportToRemoveID) {
    auto edgesIterator = previousComponent.getEdges().getConnections().begin();
    while (edgesIterator->first != airportToRemoveID)
        edgesIterator++;
    previousComponent.getEdges().getConnections().erase(edgesIterator);
}

void Graph::deleteComponent(const std::string &airportCode) {
    if (um.find(airportCode) == um.end()) {
        std::cout << "Airport not in graph; no node was removed." << std::endl;
        return;
    }

    // need to remove airport from graph vector and from all Components who have that airport in their lists
    // renumbering with IDs required
        // affected airports are all airports AFTER index of airport to be deleted in graph vector
        // subtracting 1 from each airport ID appearing after airport to be deleted in graph would solve this
    int32_t currIndex = um.at(airportCode) + 1;
    while (currIndex < this->graph.size()) {
        this->graph[currIndex].adjustIDs();
        currIndex++;
    }

    // Before removing node from graph, remove every instance of it in every other connection
    for (Component& vertex : this->graph) {
        if (hasConnection(vertex, um.at(airportCode)) != -1)
            removeFromConnections(vertex, um.at(airportCode));
    }

    this->graph.erase(this->graph.begin() + um.at(airportCode) - 1);
    IDTracker--;
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