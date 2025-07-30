#include "map/tiles/Lake.hpp"

Lake::Lake(int variant) {
    _type = TILE_LAKE;
    _variant = variant;
    _walkable = false; // Lakes are not walkable
}