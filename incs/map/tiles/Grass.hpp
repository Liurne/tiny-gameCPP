#ifndef GRASS_HPP
# define GRASS_HPP

#include "map/tiles/Tile.hpp"

class Grass : public Tile {
public:
    Grass();
    Grass(int height = 2, int variant = 0, bool flower = false, int flowerVariant = 0);

    bool isWalkable() const { return _walkable; }

private:
    bool    _flower;
    int     _flowerVariant;

};

#endif