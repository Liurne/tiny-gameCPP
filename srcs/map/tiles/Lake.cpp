#include "map/tiles/Lake.hpp"

Lake::Lake() {
    _type = TILE_LAKE;
    _variant = 0;
    _walkable = false; // Lakes are not walkable
}

Lake::Lake(int variant) {
    _type = TILE_LAKE;
    _variant = variant;
    _walkable = false; // Lakes are not walkable
}