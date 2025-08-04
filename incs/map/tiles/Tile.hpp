#ifndef TILE_HPP
# define TILE_HPP

typedef enum {
    TILE_OCEAN = 0,
    TILE_GRASS = 1,
    TILE_LAKE = 2,
    TILE_SAND = 3,
    TILE_WATEREDSAND = 4,
    TILE_DOCK = 5,
} t_tile;

class Tile {
public:
    Tile();
    ~Tile();

    int             getType() const { return _type; };
    void            setType(int type) { _type = type; };
    int             getHeight() const { return _height; }
    void            setHeight(int height) { _height = height; }
    int             getVariant() const { return _variant; }
    void            setVariant(int variant) { _variant = variant; }
    void            setIsWalkable(bool isWalkable) { _walkable = isWalkable; }

    bool            isWalkable() const;

protected:
int     _type;
int     _variant;
int     _height;
bool    _walkable;

};

#endif