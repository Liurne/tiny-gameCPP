#ifndef MAPVISUALGENERATOR_HPP
#define MAPVISUALGENERATOR_HPP

#include "Map.hpp"

class MapVisualGenerator {
public:
    MapVisualGenerator();
    ~MapVisualGenerator();
    MapVisualGenerator(MapVisualGenerator const &src);
    MapVisualGenerator &operator=(MapVisualGenerator const &rhs);

    mlx_image_t *generateMapImage(mlx_image_t *view, Map &map);

private:
    mlx_image_t *_mapView;

    void _drawMap(Map &map);
    void _drawCell(Map &map, int x, int y);

    void _drawWater(Map &map, int x, int y);
    void _drawBridge(Map &map, int x, int y);
    void _drawLake(Map &map, int x, int y);
    void _drawGrass(Map &map, int x, int y);
    void _drawFlower(Map &map, int x, int y);
    void _drawCollectible(Map &map, int x, int y);
    void _drawSpawn(Map &map, int x, int y);
    void _drawEnemy(Map &map, int x, int y);

    bool _isCellBridgeOrGround(char cell);

};

#endif