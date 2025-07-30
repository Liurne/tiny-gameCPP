#include "map/tiles/Grass.hpp"

Grass::Grass(int height, int variant, bool flower, int flowerVariant) {
    _type = TILE_GRASS;
    _height = height;
    _variant = variant;
    _walkable = true;
    _flower = flower;
    _flowerVariant = flowerVariant;
}



