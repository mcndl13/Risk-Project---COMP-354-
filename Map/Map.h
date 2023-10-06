#include <iostream>
#include <vector>
#include "Continent.h"
#include "Territory.h"
#include <unordered_set>

class Map {
public:
    Map();
    ~Map();

    Map(const Map &m); // copy constructor
    Map& operator=(const Map &m); // assignment operator
    friend std::ostream& operator<<(std::ostream &os, const Map &m); // stream insertion operator

    bool validate() const;
    bool validate() const;  // declaration for the validate method
    void addTerritory(Territory *territory);
    void addContinent(Continent *continent);
    bool isContinentConnected(Continent *continent) const;  // method to check connectivity of the continents to ensure the continents are connected subgraphs
    bool isConnectedGraph() const;  // new method for verification if the map is a connected graph
    bool isTerritoryInOneContinent() const;  // new method for verification if territory or country belongs to one and one continent
    const std::vector<Continent*>& getContinents() const;  // new method to get continents

private:

    void dfs(Territory* territory, Continent* continent, std::unordered_set<Territory*>& visited) const;  // method for DFS traversal
    std::vector<Territory*> territories;
    std::vector<Continent*> continents;
};



