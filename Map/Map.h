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


