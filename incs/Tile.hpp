#ifndef TILE_HPP
#define TILE_HPP

class Tile {
    public:

    Tile(int id);
    ~Tile();

    void    setId(int id);

    private:
    int     _id;
    int     _height;
    bool    _isWalkable;
    bool    _isEmpty;

    Tile();
    Tile(const Tile &);
    Tile &operator=(const Tile &);

};


#endif