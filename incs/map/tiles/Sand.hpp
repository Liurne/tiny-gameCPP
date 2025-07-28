#ifndef SAND_HPP
# define SAND_HPP

# include "map/tiles/Tile.hpp"

class Sand : public Tile {
public:
    Sand();
    Sand(int height = 1, int variant = 0);

    bool isWalkable() const { return _walkable; }

private:

};

#endif