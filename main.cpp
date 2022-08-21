#include <iostream>
#include "Graph.h"

int main() {
    const std::vector<std::string> startingAirports = {"JFK", "IAD", "LAX", "AUS", "PDX", "CLE", "MIA", "DEN"};
    const std::vector<std::vector<std::pair<std::string, int32_t>>> nonstopConnections = {
            {{"IAD", 227}, {"LAX", 2475}, {"AUS", 1519}, {"PDX", 2447}, {"CLE", 416}, {"MIA", 1091}, {"DEN", 1639}},
            {{"JFK", 227}, {"LAX", 2272}, {"AUS", 1299}, {"PDX", 2320}, {"CLE", 282}, {"MIA", 923}, {"DEN", 1466}},
            {{"JFK", 2475}, {"IAD", 2272}, {"AUS", 1225}, {"PDX", 827}, {"CLE", 2044}, {"MIA", 2329}, {"DEN", 830}},
            {{"JFK", 1519}, {"IAD", 1299}, {"LAX", 1225}, {"PDX", 1706}, {"MIA", 1107}, {"DEN", 771}},
            {{"JFK", 2447}, {"IAD", 2320}, {"LAX", 827}, {"AUS", 1706}, {"DEN", 978}},
            {{"JFK", 416}, {"IAD", 282}, {"LAX", 827}, {"MIA", 1088}, {"DEN", 1223}},
            {{"JFK", 1091}, {"IAD", 923}, {"LAX", 2329}, {"AUS", 1107}, {"CLE", 1088}, {"DEN", 1718}},
            {{"JFK", 1639}, {"IAD", 1466}, {"LAX", 830}, {"AUS", 771}, {"PDX", 978}, {"CLE", 1223}, {"MIA", 1718}}
    };

    std::cout << std::endl << "***************************" << std::endl;
    std::cout << "***************************" << std::endl;
    std::cout << "* BEFORE ADDING COMPONENT *" << std::endl;
    std::cout << "***************************" << std::endl;
    std::cout << "***************************" << std::endl << std::endl;
    Graph graphInstance(startingAirports, nonstopConnections);
    std::cout << "Adjacency List: " << std::endl;
    graphInstance.showAdjacencyList();
    std::cout << std::endl << "Adjacency Matrix: " << std::endl;
    graphInstance.showAdjacencyMatrix();

    //Adding and Deleting
    std::string airportToAdd = "SAT";
    std::vector<std::pair<std::string, int32_t>> airportToAddConnections = {
            {"JFK", 1590},
            {"IAD", 1366},
            {"LAX", 1201},
            {"MIA", 1141},
            {"DEN", 802}
    };
    graphInstance.addComponent(airportToAdd, airportToAddConnections);

    std::cout << std::endl << "**************************" << std::endl;
    std::cout << "**************************" << std::endl;
    std::cout << "* AFTER ADDING COMPONENT *" << std::endl;
    std::cout << "**************************" << std::endl;
    std::cout << "**************************" << std::endl;
    std::cout << "Adjacency List: " << std::endl;
    graphInstance.showAdjacencyList();
    std::cout << std::endl << "Adjacency Matrix: " << std::endl;
    graphInstance.showAdjacencyMatrix();

    std::cout << std::endl << "****************************" << std::endl;
    std::cout << "****************************" << std::endl;
    std::cout << "* AFTER DELETING COMPONENT *" << std::endl;
    std::cout << "****************************" << std::endl;
    std::cout << "****************************" << std::endl;
    graphInstance.deleteComponent("SAT");
    std::cout << "Adjacency List: " << std::endl;
    graphInstance.showAdjacencyList();
    std::cout << std::endl << "Adjacency Matrix: " << std::endl;
    graphInstance.showAdjacencyMatrix();

    std::cout << "Done!" << std::endl;
    return 0;
}
