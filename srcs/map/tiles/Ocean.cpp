#include "map/tiles/Ocean.hpp"

Ocean::Ocean() {
    _type = TILE_OCEAN;
    _variant = 0;
    _walkable = true; // Oceans are not walkable
}
