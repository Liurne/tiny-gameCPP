#include "map/tiles/Sand.hpp"

Sand::Sand() {
    _type = TILE_SAND;
    _variant = 0;
    _height = 1;
    _walkable = true; // Sand is walkable
}

Sand::Sand(int height, int variant) {
    _type = TILE_SAND;
    _height = height;
    _variant = variant;
    _walkable = true; // Sand is walkable
}