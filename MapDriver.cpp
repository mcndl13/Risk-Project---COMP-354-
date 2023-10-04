#include "Map.h"
#include "MapLoader.h"

void testLoadMaps() {
    // Example code: adapt it for multiple files, handle memory cleanup etc.
    MapLoader loader("path_to_map_file.map");
    Map *map = loader.loadMap();

    if(map && map->validate()) {
        std::cout << "Valid map!" << std::endl;
    } else {
        std::cout << "Invalid map!" << std::endl;
    }

    delete map;  // Clean up memory
}

int main() {
    testLoadMaps();
    return 0;
}


