#include <string>
#include "Map.h"

class MapLoader {
public:
    MapLoader(const std::string &filePath);
    Map* loadMap();

private:
    std::string *filePath;
};
