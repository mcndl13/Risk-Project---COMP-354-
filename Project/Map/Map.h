#pragma once
#include <iostream>
#include <vector>
#include <unordered_set>

class Continent;
class Territory;

class Map {

    public:
        Map();
        ~Map();

        Map(const Map &m); // copy constructor
        Map& operator=(const Map &m); // assignment operator
        friend std::ostream& operator<<(std::ostream &os, const Map &m); // stream insertion operator

        
        bool validate() const;  // declaration for the validate method
        void addTerritory(Territory *territory);
        void addContinent(Continent *continent);
        bool isContinentConnected(Continent *continent) const;  // method to check connectivity of the continents to ensure the continents are connected subgraphs
        bool isConnectedGraph() const;  // new method for verification if the map is a connected graph
        bool isTerritoryInOneContinent() const;  // new method for verification if territory or country belongs to one and one continent
        const std::vector<Continent*>& getContinents() const;  // new method to get continents
        const std::vector<Territory*>& getTerritory() const;
    private:

        void dfs(Territory* territory, Continent* continent, std::unordered_set<Territory*>& visited) const;  // method for DFS traversal
        std::vector<Territory*> territories;
        std::vector<Continent*> continents;
};



class MapLoader {
    public:
        MapLoader(const std::string &filePath);
        ~MapLoader();
        Map* loadMap();
        Map* createMapfromFile (std::string map_file_path);

    private:
        std::string filePath;
        std::unordered_set<std::string> assignedTerritories;  // New data member to track assigned territories
};




// Continents
class Continent {

    public:
        Continent(const std::string &name);
        ~Continent();

        Continent(const Continent &c); // copy constructor
        Continent& operator=(const Continent &c); // assignment operator
        friend std::ostream& operator<<(std::ostream &os, const Continent* c); // stream insertion operator

        const std::string& getName() const;

        void addTerritory(Territory *territory);
        const std::vector<Territory*>& getTerritories() const;

    private:
        std::string *name;
        std::vector<Territory*> territories;
};


// Territory
class Territory {

    public:
        Territory(const std::string &name);
        ~Territory();

        Territory(const Territory &t); // copy constructor
        Territory& operator=(const Territory &t); // assignment operator
        friend std::ostream& operator<<(std::ostream &out, const Territory* t); // stream insertion operator
        friend std::ostream& operator<<(std::ostream &out, const std::vector<Territory*>&); // stream insertion operator
    

        std::string getName() const;
        int get_number_of_armies();
        void adding_armies_number(int);
        // int get_index_index();

        void addAdjacency(Territory *territory);
        const std::vector<Territory*>& getAdjacencies() const;
        void SetOwner(std::string owner_Name);
        std::string GetOwner();
    private:
        std::string name;
        std::string *owningPlayer;
        int numArmies;
        std::vector<Territory*> adjacencies;
};

