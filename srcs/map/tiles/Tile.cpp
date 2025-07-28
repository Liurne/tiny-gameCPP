#include "map/tiles/Tile.hpp"

Tile::Tile() : _type(0), _variant(0), _height(0), _walkable(true) {
    // Constructor logic if needed
}

Tile::~Tile() {
    // Destructor logic if needed
}


bool Tile::isWalkable() const {
    return _walkable;
}

