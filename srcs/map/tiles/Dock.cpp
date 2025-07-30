#include "map/tiles/Dock.hpp"

Dock::Dock(int height, int variant) {
    _type = TILE_DOCK;
    _height = height;
    _variant = variant;
    _walkable = true; // Docks are walkable
}