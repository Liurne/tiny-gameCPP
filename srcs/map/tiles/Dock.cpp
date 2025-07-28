#include "map/tiles/Dock.hpp"

Dock::Dock() {
    _type = TILE_DOCK;
    _variant = 0;
    _height = 2; // Default height for dock
    _walkable = true; // Docks are walkable
}

Dock::Dock(int height, int variant) {
    _type = TILE_DOCK;
    _height = height;
    _variant = variant;
    _walkable = true; // Docks are walkable
}