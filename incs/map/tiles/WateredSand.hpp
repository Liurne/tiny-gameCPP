#ifndef WATEREDSAND_HPP
# define WATEREDSAND_HPP

# include "map/tiles/Tile.hpp"

class WateredSand : public Tile {
public:
    WateredSand(int height = 1, int variant = 0);

    bool isWalkable() const { return _walkable; }

private:

};


#endif