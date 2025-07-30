#ifndef LAKE_HPP
# define LAKE_HPP

# include "map/tiles/Tile.hpp"
class Lake : public Tile {
public:
    Lake(int variant = 0);

    bool isWalkable() const { return _walkable; }

private:

};

#endif