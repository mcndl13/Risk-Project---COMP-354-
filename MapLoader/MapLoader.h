#include <string>
#include "Map.h"
#include <unordered_set>

class MapLoader {
public:
    MapLoader(const std::string &filePath);
    ~MapLoader();
    Map* loadMap();

private:
    std::string *filePath;
    std::unordered_set<std::string> assignedTerritories;  // New data member to track assigned territories
};

