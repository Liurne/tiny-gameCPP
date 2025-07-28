#ifndef DOCK_HPP
# define DOCK_HPP

# include "map/tiles/Tile.hpp"

class Dock : public Tile {
public:
    Dock();
    Dock(int height = 2, int variant = 0);

    bool isWalkable() const { return _walkable; }

private:

};

#endif