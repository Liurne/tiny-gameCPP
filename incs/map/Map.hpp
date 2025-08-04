#ifndef MAP_HPP
# define MAP_HPP

# include "game_rule.h"
# include "core/MLXWrapper.hpp"

# include "tiles/Ocean.hpp"
# include "tiles/Grass.hpp"
# include "tiles/Lake.hpp"
# include "tiles/Sand.hpp"
# include "tiles/WateredSand.hpp"
# include "tiles/Dock.hpp"

class Map {
public:
    Map();
    ~Map();

    Tile            *getTile(int x, int y) const { return _map[x][y]; }
    int             getTileType(int x, int y) const { return _map[x][y]->getType(); }
    int             getTileHeight(int x, int y) const { return _map[x][y]->getHeight(); }
    int             getTileVariant(int x, int y) const { return _map[x][y]->getVariant(); }
    bool            isTileWalkable(int x, int y) const { return _map[x][y]->isWalkable(); }
    uint32_t        getNbCollectible() const { return _nbCollectible; }
    t_veci          getStart() const { return _start; }
    int             getStartSide() const { return _startSide; }

    void            setTile(int x, int y, Tile *tile);
    void            setStart(int x, int y, int side) { _start = (t_veci){x, y}; _startSide = side;}
    void            setNbCollectible(uint32_t nb) { _nbCollectible = nb; }
    void            setMapView(mlx_image_t *image) { _mapView = image; }
    void            setMapPreview(mlx_image_t *image) { _mapPreview = image; }
    bool            isPositionValid(t_veci currentPos, t_veci newPos) const;

private:
    Tile            *_map[MAP_WIDTH][MAP_HEIGHT];

    uint32_t        _nbCollectible;
    t_veci          _start;
    int             _startSide;

    mlx_image_t     *_mapView;
    mlx_image_t     *_mapPreview;

    Map(Map const &src);
    Map &operator=(Map const &rhs);
};

#endif