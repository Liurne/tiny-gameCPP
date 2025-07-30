#ifndef GRASS_HPP
# define GRASS_HPP

#include "map/tiles/Tile.hpp"

class Grass : public Tile {
public:
    Grass(int height = 2, int variant = 0, bool flower = false, int flowerVariant = 0);

    bool    hasFlower() const { return _flower; }
    int     getFlowerVariant() const { return _flowerVariant; }

    void    setFlower(bool flower) { _flower = flower; }
    void    setFlowerVariant(int flowerVariant) { _flowerVariant = flowerVariant; }


    bool isWalkable() const { return _walkable; }

private:
    bool    _flower;
    int     _flowerVariant;

};

#endif