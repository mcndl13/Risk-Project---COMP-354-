#include <iostream>
#include <vector>
#include "Continent.h"
#include "Territory.h"

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

private:
    std::vector<Territory*> territories;
    std::vector<Continent*> continents;
};

/*

map rules:
- each territoy has a colour to represent the play
- Gray territory is neutral


Playing:
- Each turn you receive new armies.  Right now, you are receiving five armies per turn.
- The first step of every turn is deploying your new armies.


Format:
- Map is connected graph
    - Node = Territory

- Continent is connected subgraphs

continents > territories


1. The map must be implemented as a connected graph, where each node represents 
   a territory.



*/
