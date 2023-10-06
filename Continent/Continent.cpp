#include "Continent.h"
// Implementations for Continent methods and operators go here. 

Continent::Continent(const std::string &name) {
    this->name = new std::string(name);
}

Continent::~Continent() {
    delete name;
}

Continent::Continent(const Continent &c) {
    name = new std::string(*(c.name));
    territories = c.territories;
}

Continent& Continent::operator=(const Continent &c) {
    if (this == &c) return *this;  // handle self assignment
    delete name;  // delete the existing name
    name = new std::string(*(c.name));
    territories = c.territories;
    return *this;
}

void Continent::addTerritory(Territory *territory) {
    territories.push_back(territory);
}

const std::vector<Territory*>& Continent::getTerritories() const {
    return territories;
}

const std::string& Continent::getName() const {
    return *name;
}
