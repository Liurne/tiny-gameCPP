#include "map/tiles/Ocean.hpp"

Ocean::Ocean(int variant) {
    _type = TILE_OCEAN;
    _variant = variant;
    _walkable = false; // Oceans are not walkable
}
