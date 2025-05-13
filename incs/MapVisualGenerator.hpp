#ifndef MAPVISUALGENERATOR_HPP
#define MAPVISUALGENERATOR_HPP

#include "Map.hpp"

class MapVisualGenerator {
public:
    MapVisualGenerator();
    ~MapVisualGenerator();
    MapVisualGenerator(MapVisualGenerator const &src);
    MapVisualGenerator &operator=(MapVisualGenerator const &rhs);

    mlx_image_t *generateMapImage(MLXWrapper &mlx, Map &map);

private:
    mlx_image_t *_mapView;

    void _drawCell(Map &map, int x, int y);

    void _drawMap(Map &map);
    void _drawDeep(Map &map);
    void _drawGrass(Map &map);
    void _drawFlower(Map &map);
    void _drawBridge(Map &map);

};
    void
};

#endif