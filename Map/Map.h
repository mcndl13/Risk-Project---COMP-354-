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
    void addTerritory(Territory *territory);
    void addContinent(Continent *continent);
    bool isContinentConnected(Continent *continent) const;  // method to check connectivity of the continents to ensure the continents are connected subgraphs
    const std::vector<Continent*>& getContinents() const;  // new method to get continents

private:
    void dfs(Territory* territory, std::unordered_set<Territory*>& visited) const;  // method for DFS traversal
    std::vector<Territory*> territories;
    std::vector<Continent*> continents;
};



