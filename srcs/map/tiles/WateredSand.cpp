#include "map/tiles/WateredSand.hpp"

WateredSand::WateredSand(int height, int variant) {
    _type = TILE_WATEREDSAND;
    _height = height;
    _variant = variant;
    _walkable = true; // Sand is walkable
}