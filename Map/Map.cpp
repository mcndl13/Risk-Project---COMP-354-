#include "Map.h"

// Implementations for Map methods and operators go here.
// Include validation methods, memory management etc.

bool Map::isContinentConnected(Continent *continent) const {
    if (continent->getTerritories().empty()) return false;

    std::unordered_set<Territory*> visited;
    dfs(continent->getTerritories()[0], visited);  // start DFS from the first territory

    // Check if all territories in the continent were visited
    for (auto territory : continent->getTerritories()) {
        if (visited.find(territory) == visited.end()) return false;
    }

    return true;
}

void Map::dfs(Territory* territory, std::unordered_set<Territory*>& visited) const {
    visited.insert(territory);
    for (auto adjacent : territory->getAdjacencies()) {
        if (visited.find(adjacent) == visited.end()) {
            dfs(adjacent, visited);
        }
    }
}

const std::vector<Continent*>& Map::getContinents() const {  // Implementation of getContinents method
    return continents;
}



