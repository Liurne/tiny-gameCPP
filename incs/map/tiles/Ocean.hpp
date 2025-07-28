#ifndef OCEAN_HPP
# define OCEAN_HPP

# include "map/tiles/Tile.hpp"

class Ocean : public Tile {
public:
    Ocean();

    bool isWalkable() const { return _walkable; }

private:

};

#endif