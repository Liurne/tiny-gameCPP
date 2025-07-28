#include "map/MapTools.hpp"

MapTools::~MapTools() {
    std::cout << "MapGenerator destructor called" << std::endl;
}

Map *MapTools::generateMap() {
    Map *newMap = new Map();
    return new Map();
}
