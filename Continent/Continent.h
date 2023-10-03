#pragma once
#include <string>
#include <vector>

using namespace std;

class Territory; // Forward declaration of Territory class

class Continent {
public:
    Continent(); // Default Constructor
    Continent(const string& continent_name);
    
    const string& GetName() const;
    const vector<Territory*>& GetTerritories() const; // Contains all the territories of the continent

    void AddTerritory(Territory* territory);

private:
    string continent_name;
    vector<Territory*> territories;
};