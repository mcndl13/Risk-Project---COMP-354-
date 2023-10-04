#include <iostream>
#include <vector>
#include "Territory.h"

class Continent {
public:
    Continent(const std::string &name);
    ~Continent();

    Continent(const Continent &c); // copy constructor
    Continent& operator=(const Continent &c); // assignment operator
    friend std::ostream& operator<<(std::ostream &os, const Continent &c); // stream insertion operator

    void addTerritory(Territory *territory);
    const std::vector<Territory*>& getTerritories() const;

private:
    std::string *name;
    std::vector<Territory*> territories;
};

