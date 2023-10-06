#include "Territory.h"
// Implementations for Territory methods and operators go here. 
Territory::Territory(const std::string &name) {
    this->name = new std::string(name);
    owningPlayer = nullptr;
    numArmies = new int(0);
}

Territory::~Territory() {
    delete name;
    delete numArmies;
}

Territory::Territory(const Territory &t) {
    name = new std::string(*(t.name));
    owningPlayer = t.owningPlayer;  
    numArmies = new int(*(t.numArmies));
    adjacencies = t.adjacencies;
}

Territory& Territory::operator=(const Territory &t) {
    if (this == &t) return *this;  // handle self assignment
    delete name;  // delete the existing name
    delete numArmies;  // delete the existing numArmies
    name = new std::string(*(t.name));
    owningPlayer = t.owningPlayer; 
    numArmies = new int(*(t.numArmies));
    adjacencies = t.adjacencies;
    return *this;
}
