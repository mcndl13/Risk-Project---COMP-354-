#pragma once
#include <string>
#include <vector>

using namespace std;

class Continent;


class Territory {

private:
    int id;
    string territory_name;

    // Reference to the continent it belongs to Continents must also be connected subgraphs, 
    // where each territory belongs to one and only one continent
    Continent*  continent; 
    vector<Territory*> neighbours;

public:
    Territory(int id, const string& name);
    
    // Getters
    int GetID();

    string GetName();

    Continent* GetContinent();

    const vector<Territory*>& GetNeighbors();


    // Set continent
    void SetContinent(Continent* continent);

    // Add neighbour
    void AddNeighbour(Territory* neighbour);
};