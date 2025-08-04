#ifndef OCEAN_HPP
# define OCEAN_HPP

# include "map/tiles/Tile.hpp"

class Ocean : public Tile {
public:
    Ocean(int variant = 0);

    bool isWalkable() const { return _walkable; }

private:

};

#endif