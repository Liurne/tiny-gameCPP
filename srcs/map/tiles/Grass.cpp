#include "map/tiles/Grass.hpp"

Grass::Grass() {
    _type = TILE_GRASS;
    _variant = 0;
    _height = 2;
    _walkable = true;
    _flower = false;
    _flowerVariant = 0;
}

Grass::Grass(int height, int variant, bool flower, int flowerVariant) {
    _type = TILE_GRASS;
    _height = height;
    _variant = variant;
    _walkable = true;
    _flower = flower;
    _flowerVariant = flowerVariant;
}



