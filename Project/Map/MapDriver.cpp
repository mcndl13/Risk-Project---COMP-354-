// The testLoadMaps function now takes a vector of strings containing the paths to map files.
//The main function creates a vector of map file paths and passes it to testLoadMaps.
//The testLoadMaps function iterates through each map file, loading, validating, and verifying the map according to the specified requirements.

#include "Map.h"
#include <vector>

void testLoadMaps(const std::vector<std::string>& mapFiles) {
    for (const auto& mapFile : mapFiles) {
        MapLoader loader(mapFile);
        Map *map = loader.loadMap();

        if(map) {
            if (map->validate()) {
                std::cout << "Valid map loaded from: " << mapFile << std::endl;

              
                
                if (map->isConnectedGraph()) {
                    std::cout << "The map is a connected graph." << std::endl;
                } else {
                    std::cout << "The map is not a connected graph." << std::endl;
                }

                bool allContinentsConnected = true;
                for (const auto& continent : map->getContinents()) {
                    if (!map->isContinentConnected(continent)) {
                        allContinentsConnected = false;
                        std::cout << "Continent " << *(continent->getName()) << " is not a connected subgraph." << std::endl;
                    }
                }
                if (allContinentsConnected) {
                    std::cout << "All continents are connected subgraphs." << std::endl;
                }

                
                if (map->isTerritoryInOneContinent()) {
                    std::cout << "Each territory belongs to one and only one continent." << std::endl;
                } else {
                    std::cout << "There are territories belonging to more than one continent." << std::endl;
                }

            } else {
                std::cout << "Invalid map loaded from: " << mapFile << std::endl;
            }

            delete map;  // Clean up memory

        } else {
            std::cout << "Could not load map from: " << mapFile << std::endl;
        }
    }
}

int main() {
    std::vector<std::string> mapFiles = {
        "Mapfiles/solar.map",
        "Mapfiles/german-Empire1871.map",
       
        // ... add more map file paths
    };
    testLoadMaps(mapFiles);
    return 0;
}
