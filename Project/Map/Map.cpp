#include <iostream>
#include <algorithm>  // for find
#include <fstream>
#include <sstream>
#include <map>
#include <cstring>  
#include "Map.h"
#include "../Player/Player.h"
using namespace std;

// Implementations for Map methods and operators go here.
Map::Map() {
    // Constructor implementation
    // Initialization of members can be done here later PSA: DO THIS LATER
}


Map::~Map() { 
    // Destructor implementation
    // Memory cleanup can be done here PSA: DO THIS LATER
    for (auto territory : territories) {
        delete territory;
    }
    for (auto continent : continents) {
        delete continent;
    }
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
    if (continent->getTerritories().empty()){
        return false;
    }


    unordered_set<Territory*> visited;
    dfs(continent->getTerritories()[0], continent, visited);  // Passing continent as an additional argument and start DFS from the first territory

// Check if all territories in the continent were visited
    for (auto territory : continent->getTerritories()) {
        if (visited.find(territory) == visited.end()) return false;
    }

    return true;
}


bool Map::isConnectedGraph() const {
    if (territories.empty()) return false;

    unordered_set<Territory*> visited;
    dfs(territories[0], nullptr, visited);  // Passing null for continent to traverse all territories

    return visited.size() == territories.size();  // All territories should be visited
}


bool Map::isTerritoryInOneContinent() const {
    for (const auto& territory : territories) {
        int continentCount = 0;
        for (const auto& continent : continents) {
            if (find(continent->getTerritories().begin(), continent->getTerritories().end(), territory) != continent->getTerritories().end()) {
                continentCount++;
                if (continentCount > 1) return false;  // Territory found in more than one continent
            }
        }
    }
    return true;  // All territories belong to exactly one continent
}


bool Map::validate() const {
    // Check if the map is a connected graph
    if (!isConnectedGraph()) {
        cout << "The map is not a connected graph." << endl;
        return false;
    }

    // Check if each continent is a connected subgraph
    for (const auto& continent : continents) {
        if (!isContinentConnected(continent)) {
            cout << "Continent " << continent->getName() << " is not a connected subgraph." << endl;
            return false;
        }
    }

    // Check if each territory belongs to one and only one continent
    if (!isTerritoryInOneContinent()) {
        cout << "Some territories belong to more than one continent." << endl;
        return false;
    }

    // All checks passed
    return true;
}


void Map::dfs(Territory* territory, Continent* continent, unordered_set<Territory*>& visited) const {
    if (continent && find(continent->getTerritories().begin(), continent->getTerritories().end(), territory) == continent->getTerritories().end()) {
    return;  // Territory is not part of the specified continent, return without further traversal
}


    visited.insert(territory);
    for (auto adjacent : territory->getAdjacencies()) {
        if (visited.find(adjacent) == visited.end()) {
            dfs(adjacent, continent, visited);  // Recursive call with the same continent
        }
    }
}

void Map::addTerritory(Territory *territory) {
    territories.push_back(territory);
}

void Map::addContinent(Continent *continent) {
    continents.push_back(continent);
}

const vector<Continent*>& Map::getContinents() const {  // Implementation of getContinents method
    return continents;
}

const vector<Territory*> Map::getTerritory() const {  // Implementation of getContinents method
    return territories;
}






// Implementations for Territory methods and operators go here. 
    Territory::Territory(const string &name): owningPlayer(){
        this->name = name;
        owningPlayer = nullptr;
        numArmies = 0;
    }

    Territory::~Territory() {
        delete owningPlayer;
        adjacencies.clear();
    }

    Territory::Territory(const Territory &t): owningPlayer() {
        name = t.name;
        owningPlayer = t.owningPlayer;  
        numArmies = t.numArmies;
        adjacencies = t.adjacencies;
    }

    Territory& Territory::operator=(const Territory &t) {
        if (this == &t) return *this;  // handle self assignment
        name = t.name;
        owningPlayer = t.owningPlayer; 
        numArmies = t.numArmies;
        adjacencies = t.adjacencies;
        return *this;
    }



    // overloading output stream operator cards. Printing a collection of territories
    ostream& operator<<(ostream &out, const vector<Territory*>& territory_list){

        for(Territory* temp: territory_list){
            out << "-  " << temp;
            out << "\n"; 
        }
        out << "\n\n";

        return out;
    }



    // overloading output stream operator cards
    ostream& operator<<(std::ostream &out, const Territory* t){
        out << "The territories's name is: " << t->getName() << "\n";
        return out;
    }

    


    void Territory::addAdjacency(Territory *territory) {
        adjacencies.push_back(territory);
    }

    const vector<Territory*>& Territory::getAdjacencies() const {
        return adjacencies;
    }

    string Territory::getName() const{
        return this->name;
    }

    int Territory::get_number_of_armies(){
        return numArmies;
    }

    void  Territory::adding_armies_number(int number){
        numArmies += number;
    }

    Player* Territory::get_owning_player(){
        return owningPlayer;
    }

    void Territory::set_owning_player(Player* p){
        owningPlayer = p;
    }








// Implementations for Continent methods and operators go here. 
    Continent::Continent(const string &name) {
        this->name = new string(name);
    }

    Continent::~Continent() {
        delete name;
    }

    Continent::Continent(const Continent &c) {
        name = new string(*(c.name));
        territories = c.territories;
    }

    Continent& Continent::operator=(const Continent &c) {
        if (this == &c) return *this;  // handle self assignment
        delete name;  // delete the existing name
        name = new string(*(c.name));
        territories = c.territories;
        return *this;
    }

    void Continent::addTerritory(Territory *territory) {
        territories.push_back(territory);
    }

    const vector<Territory*>& Continent::getTerritories() const {
        return territories;
    }

    const string& Continent::getName() const {
        return *name;
    }

    ostream& operator<<(std::ostream &os, const Continent* c){
        os << c->getName() << "\n";
        return os;
    }









// Implementations for MapLoader methods. Handle file reading and parsing here.

MapLoader::MapLoader(const std::string &filePath) {
    this->filePath = filePath;
}

MapLoader::~MapLoader() {
    // delete filePath;
}

Map* MapLoader::loadMap() {

// Open the file
std::ifstream file(filePath);
   if (!file) {
        std::cerr << "Error: could not open file: " << filePath << std::endl;
        return nullptr;
    }

    

    Map* map = new Map();
    std::string line;
    std::map<std::string, Territory*> territoryMap;  // To lookup territories by name
    vector<string> temp;


    while (getline(file, line)) {
        std::stringstream ss(line);
        std::string token;

        if (line.find("[continents]") != std::string::npos) {
            while (getline(file, line) && !line.empty()) {
                std::stringstream ss(line);
                std::string name, value;
                getline(ss, name, '=');

                std::istringstream tokenStream(name);
                while (getline(tokenStream, name, ' ')) {
                    temp.push_back(name);
                }

                getline(ss, value, '=');
                Continent* continent = new Continent(temp.at(0));
                map->addContinent(continent);
                temp.clear();
            }

        
        } else if (line.find("[countries]") != std::string::npos) {
            while (getline(file, line) && !line.empty()) {
                std::stringstream ss(line);
                std::string name, x_coord, y_coord;
                getline(ss, name, ',');
                getline(ss, x_coord, ',');
                getline(ss, y_coord, ',');


                std::istringstream tokenStream(name);
                while (getline(tokenStream, name, ' ')) {
                    // cout << name << "-";
                    temp.push_back(name);
                }


                vector<string> contient_name;


                std::istringstream tokenStream1(temp.at(1));
                while (getline(tokenStream1, temp.at(1), '-')) {
                    contient_name.push_back(temp.at(1));
                }

                string c_name = contient_name.at(0);

                
                Territory* territory = new Territory(temp.at(1));
                map->addTerritory(territory);
                territoryMap[temp.at(0)] = territory;  // Store territory for later adjacency setup

                // Check if territory has already been assigned to a continent
                if (assignedTerritories.find(temp.at(1)) != assignedTerritories.end()) {
                    std::cerr << "Territory " << temp.at(1) << " is assigned to more than one continent." << std::endl;
                    delete map;  // free memory
                    return nullptr;  // return null if a territory is assigned to more than one continent
                }
                assignedTerritories.insert(name);  // Mark territory as assigned

                // Assuming continent names are unique and have been read already
                for (Continent* continent : map->getContinents()) {
                    if ((continent->getName()) == c_name) {
                        continent->addTerritory(territory);
                        break;
                    }
                }
                temp.clear();
            }
        } else if (line.find("[borders]") != std::string::npos) {
            while (getline(file, line) && !line.empty()) {
                std::stringstream ss(line);
                std::string name, adj_name;
                getline(ss, name, ',');
                
                std::istringstream tokenStream(name);

                while (getline(tokenStream, name, ' ')) {
                    temp.push_back(name);
                }


                Territory* territory = territoryMap[temp.at(0)];  // Assuming territory names are unique

                for(int i = 1; i < temp.size(); i++){
                    Territory* adj_territory = territoryMap[temp.at(i)];  // Assuming adj_name exists
                    territory->addAdjacency(adj_territory);
                }

                temp.clear();
            }
        }
    }

    file.close();
    
    // Validate the connectivity of continents
    for (auto continent : map->getContinents()) {
        if (!map->isContinentConnected(continent)) {
            std::cerr << "Continent " << (continent->getName()) << " is not a connected subgraph." << std::endl;
            delete map;  // free memory
            return nullptr;  // return null if any continent is not connected
        }
    }
    return map;
}


