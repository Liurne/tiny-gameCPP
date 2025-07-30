#include "map/tiles/Sand.hpp"

Sand::Sand(int height, int variant) {
    _type = TILE_SAND;
    _height = height;
    _variant = variant;
    _walkable = true; // Sand is walkable
}