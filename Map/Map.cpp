#include "Map.h"
#include <algorithm>  // for std::find
// Implementations for Map methods and operators go here.
Map::Map() {
    // Constructor implementation
    // Initialization of members can be done here later PSA: DO THIS LATER
}

Map::~Map() {
    // Destructor implementation
    // Memory cleanup can be done here PSA: DO THIS LATER
}

Map::Map(const Map &m) {
    // Copy constructor implementation
    // Deep copy of territories and continents
    for (auto territory : m.territories) {
        territories.push_back(new Territory(*territory));
    }
    for (auto continent : m.continents) {
        continents.push_back(new Continent(*continent));
    }
}

Map& Map::operator=(const Map &m) {
    if (this == &m) {
        return *this;  // handle self assignment
    }
    
    // Cleanup existing data
    for (auto territory : territories) {
        delete territory;
    }
    for (auto continent : continents) {
        delete continent;
    }
    territories.clear();
    continents.clear();
    
    // Deep copy of territories and continents
    for (auto territory : m.territories) {
        territories.push_back(new Territory(*territory));
    }
    for (auto continent : m.continents) {
        continents.push_back(new Continent(*continent));
    }

    return *this;
}

bool Map::isContinentConnected(Continent *continent) const {
    if (continent->getTerritories().empty()) return false;

    std::unordered_set<Territory*> visited;
    dfs(continent->getTerritories()[0], continent, visited);  // Passing continent as an additional argument and start DFS from the first territory

// Check if all territories in the continent were visited
    for (auto territory : continent->getTerritories()) {
        if (visited.find(territory) == visited.end()) return false;
    }

    return true;
}

void Map::dfs(Territory* territory, Continent* continent, std::unordered_set<Territory*>& visited) const {
    if (std::find(continent->getTerritories().begin(), continent->getTerritories().end(), territory) == continent->getTerritories().end()) {
        return;  // Territory is not part of the specified continent, return without further traversal
    }

    visited.insert(territory);
    for (auto adjacent : territory->getAdjacencies()) {
        if (visited.find(adjacent) == visited.end()) {
            dfs(adjacent, continent, visited);  // Recursive call with the same continent
        }
    }
}

const std::vector<Continent*>& Map::getContinents() const {  // Implementation of getContinents method
    return continents;
}


