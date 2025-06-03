#include "MapVisualGenerator.hpp"

MapVisualGenerator::MapVisualGenerator() : _mapView(NULL) {

}
MapVisualGenerator::~MapVisualGenerator() {

}

MapVisualGenerator::MapVisualGenerator(MapVisualGenerator const &src) {
    *this = src;
}

MapVisualGenerator &MapVisualGenerator::operator=(MapVisualGenerator const &rhs) {
    if (this != &rhs) {
        _mapView = rhs._mapView;
    }
    return *this;
}

mlx_image_t *MapVisualGenerator::generateMapImage(mlx_image_t *view, Map &map) {
    if (view == NULL) {
        return NULL;
    }
    _mapView = view;
    _drawMap(map);
    return _mapView;
}

void MapVisualGenerator::_drawMap(Map &map) {
    for (int x = 0; x < MAP_WIDTH; x++) {
        for (int y = 0; y < MAP_HEIGHT; y++) {
            _drawCell(map, x, y);
        }
    }
}

void MapVisualGenerator::_drawCell(Map &map, int x, int y) {
    char cell = map.getCell(x, y);
    if (cell == '0' || cell == '2' || cell == '3') {
        _drawWater(map, x, y);
        if (cell == '2')
            _drawBridge(map, x, y);
        if (cell == '3')
            _drawLake(map, x, y);
    }
    else {
        _drawGrass(map, x, y);
        _drawFlower(map, x, y);
        if (cell == 'C')
            _drawCollectible(map, x, y);
        if (cell == 'S')
            _drawSpawn(map, x, y);
        if (cell == 'E')
            _drawEnemy(map, x, y);
    }
}

void MapVisualGenerator::_drawWater(Map &map, int x, int y) {
    if (map.getCellDeep(x, y) == '1') {
        draw_rect(_mapView, x * TEXTURE_SIZE, y * TEXTURE_SIZE, TEXTURE_SIZE, TEXTURE_SIZE, DEEP_WATER_COLOR);
    }
    else {
        draw_rect(_mapView, x * TEXTURE_SIZE, y * TEXTURE_SIZE, TEXTURE_SIZE, TEXTURE_SIZE, WATER_COLOR);
    }
}

void MapVisualGenerator::_drawBridge(Map &map, int x, int y) {
    bool cellUp = _isCellBridgeOrGround(map.getCell(x, y - 1));
    bool cellDown = _isCellBridgeOrGround(map.getCell(x, y + 1));
    bool cellLeft = _isCellBridgeOrGround(map.getCell(x - 1, y));
    bool cellRight = _isCellBridgeOrGround(map.getCell(x + 1, y));

    if (cellUp && cellDown && cellLeft && cellRight) {
        draw_rect(_mapView, (x * TEXTURE_SIZE) + TEXTURE_SIZE * 0.25, y * TEXTURE_SIZE, TEXTURE_SIZE * 0.5, TEXTURE_SIZE, BRIDGE_COLOR);
        draw_rect(_mapView, x * TEXTURE_SIZE, (y * TEXTURE_SIZE) + TEXTURE_SIZE * 0.25, TEXTURE_SIZE, TEXTURE_SIZE * 0.5, BRIDGE_COLOR);
    } else if (cellUp && cellDown && cellLeft) {
        draw_rect(_mapView, (x * TEXTURE_SIZE) + TEXTURE_SIZE * 0.25, y * TEXTURE_SIZE, TEXTURE_SIZE * 0.5, TEXTURE_SIZE, BRIDGE_COLOR);
        draw_rect(_mapView, x * TEXTURE_SIZE, (y * TEXTURE_SIZE) + TEXTURE_SIZE * 0.25, TEXTURE_SIZE * 0.75, TEXTURE_SIZE * 0.5, BRIDGE_COLOR);
    } else if (cellUp && cellDown && cellRight) {
        draw_rect(_mapView, (x * TEXTURE_SIZE) + TEXTURE_SIZE * 0.25, y * TEXTURE_SIZE, TEXTURE_SIZE * 0.5, TEXTURE_SIZE, BRIDGE_COLOR);
        draw_rect(_mapView, (x * TEXTURE_SIZE) + TEXTURE_SIZE * 0.25, (y * TEXTURE_SIZE) + TEXTURE_SIZE * 0.25, TEXTURE_SIZE * 0.75, TEXTURE_SIZE * 0.5, BRIDGE_COLOR);
    } else if (cellUp && cellLeft && cellRight) {
        draw_rect(_mapView, x * TEXTURE_SIZE, (y * TEXTURE_SIZE) + TEXTURE_SIZE * 0.25, TEXTURE_SIZE, TEXTURE_SIZE * 0.5, BRIDGE_COLOR);
        draw_rect(_mapView, (x * TEXTURE_SIZE) + TEXTURE_SIZE * 0.25, y * TEXTURE_SIZE, TEXTURE_SIZE * 0.5, TEXTURE_SIZE * 0.75, BRIDGE_COLOR);
    } else if (cellDown && cellLeft && cellRight) {
        draw_rect(_mapView, x * TEXTURE_SIZE, (y * TEXTURE_SIZE) + TEXTURE_SIZE * 0.25, TEXTURE_SIZE, TEXTURE_SIZE * 0.5, BRIDGE_COLOR);
        draw_rect(_mapView, (x * TEXTURE_SIZE) + TEXTURE_SIZE * 0.25, (y * TEXTURE_SIZE) + TEXTURE_SIZE * 0.25, TEXTURE_SIZE * 0.5, TEXTURE_SIZE * 0.75, BRIDGE_COLOR);
    } else if (cellUp && cellDown) {
        draw_rect(_mapView, (x * TEXTURE_SIZE) + TEXTURE_SIZE * 0.25, y * TEXTURE_SIZE, TEXTURE_SIZE * 0.5, TEXTURE_SIZE, BRIDGE_COLOR);
    } else if (cellLeft && cellRight) {
        draw_rect(_mapView, x * TEXTURE_SIZE, (y * TEXTURE_SIZE) + TEXTURE_SIZE * 0.25, TEXTURE_SIZE, TEXTURE_SIZE * 0.5, BRIDGE_COLOR);
    } else if (cellUp && cellLeft) {
        draw_rect(_mapView, x * TEXTURE_SIZE, (y * TEXTURE_SIZE) + TEXTURE_SIZE * 0.25, TEXTURE_SIZE * 0.75, TEXTURE_SIZE * 0.5, BRIDGE_COLOR);
        draw_rect(_mapView, (x * TEXTURE_SIZE) + TEXTURE_SIZE * 0.25, y * TEXTURE_SIZE, TEXTURE_SIZE * 0.5, TEXTURE_SIZE * 0.75, BRIDGE_COLOR);
    } else if (cellUp && cellRight) {
        draw_rect(_mapView, (x * TEXTURE_SIZE) + TEXTURE_SIZE * 0.25, (y * TEXTURE_SIZE) + TEXTURE_SIZE * 0.25, TEXTURE_SIZE * 0.75, TEXTURE_SIZE * 0.5, BRIDGE_COLOR);
        draw_rect(_mapView, (x * TEXTURE_SIZE) + TEXTURE_SIZE * 0.25, y * TEXTURE_SIZE, TEXTURE_SIZE * 0.5, TEXTURE_SIZE * 0.75, BRIDGE_COLOR);
    } else if (cellDown && cellLeft) {
        draw_rect(_mapView, x * TEXTURE_SIZE, (y * TEXTURE_SIZE) + TEXTURE_SIZE * 0.25, TEXTURE_SIZE * 0.75, TEXTURE_SIZE * 0.5, BRIDGE_COLOR);
        draw_rect(_mapView, (x * TEXTURE_SIZE) + TEXTURE_SIZE * 0.25, (y * TEXTURE_SIZE) + TEXTURE_SIZE * 0.25, TEXTURE_SIZE * 0.5, TEXTURE_SIZE * 0.75, BRIDGE_COLOR);
    } else if (cellDown && cellRight) {
        draw_rect(_mapView, (x * TEXTURE_SIZE) + TEXTURE_SIZE * 0.25, (y * TEXTURE_SIZE) + TEXTURE_SIZE * 0.25, TEXTURE_SIZE * 0.75, TEXTURE_SIZE * 0.5, BRIDGE_COLOR);
        draw_rect(_mapView, (x * TEXTURE_SIZE) + TEXTURE_SIZE * 0.25, (y * TEXTURE_SIZE) + TEXTURE_SIZE * 0.25, TEXTURE_SIZE * 0.5, TEXTURE_SIZE * 0.75, BRIDGE_COLOR);
    } else if (cellUp) {
        draw_rect(_mapView, (x * TEXTURE_SIZE) + TEXTURE_SIZE * 0.25, y * TEXTURE_SIZE, TEXTURE_SIZE * 0.5, TEXTURE_SIZE, BRIDGE_COLOR);
    } else if (cellDown) {
        draw_rect(_mapView, (x * TEXTURE_SIZE) + TEXTURE_SIZE * 0.25, (y * TEXTURE_SIZE) + TEXTURE_SIZE * 0.25, TEXTURE_SIZE * 0.5, TEXTURE_SIZE, BRIDGE_COLOR);
    } else if (cellLeft) {
        draw_rect(_mapView, x * TEXTURE_SIZE, (y * TEXTURE_SIZE) + TEXTURE_SIZE * 0.25, TEXTURE_SIZE, TEXTURE_SIZE * 0.5, BRIDGE_COLOR);
    } else if (cellRight) {
        draw_rect(_mapView, (x * TEXTURE_SIZE) + TEXTURE_SIZE * 0.25, (y * TEXTURE_SIZE) + TEXTURE_SIZE * 0.25, TEXTURE_SIZE * 0.5, TEXTURE_SIZE * 0.5, BRIDGE_COLOR);
    }
}

void MapVisualGenerator::_drawLake(Map &map, int x, int y) {
    draw_rect(_mapView, x * TEXTURE_SIZE, y * TEXTURE_SIZE, TEXTURE_SIZE, TEXTURE_SIZE, WATER_COLOR);
    if (map.getCellRandom(x, y) == '0')
        return;
    draw_rect(_mapView, (x * TEXTURE_SIZE) + TEXTURE_SIZE * 0.25, (y * TEXTURE_SIZE) + TEXTURE_SIZE * 0.25, TEXTURE_SIZE * 0.5, TEXTURE_SIZE * 0.5, LONG_GRASS_COLOR);
}

void MapVisualGenerator::_drawGrass(Map &map, int x, int y) {
    if (map.getCellGrass(x, y) == '1') {
        draw_rect(_mapView, x * TEXTURE_SIZE, y * TEXTURE_SIZE, TEXTURE_SIZE, TEXTURE_SIZE, LONG_GRASS_COLOR);
    }
    else {
        draw_rect(_mapView, x * TEXTURE_SIZE, y * TEXTURE_SIZE, TEXTURE_SIZE, TEXTURE_SIZE, SHORT_GRASS_COLOR);
    }
}

void MapVisualGenerator::_drawFlower(Map &map, int x, int y) {
    if (map.getCellFlower(x, y) == '0')
        return;

    int nbFlower = rand() % 5;

    for (int i = 0; i < nbFlower; i++) {
        int flowerX = rand() % (TEXTURE_SIZE - 6);
        int flowerY = rand() % (TEXTURE_SIZE - 6);
        draw_rect(_mapView, x * TEXTURE_SIZE + flowerX, y * TEXTURE_SIZE + flowerY, 5, 5, FLOWER_COLOR);
    }
}
void MapVisualGenerator::_drawCollectible(Map &map, int x, int y) {
    (void)map;
    draw_rect(_mapView, (x * TEXTURE_SIZE) + TEXTURE_SIZE * 0.375, (y * TEXTURE_SIZE) + TEXTURE_SIZE * 0.375, TEXTURE_SIZE * 0.25, TEXTURE_SIZE * 0.25, GROUND_COLOR);
}
void MapVisualGenerator::_drawSpawn(Map &map, int x, int y) {
    (void)map;
    draw_rect(_mapView, (x * TEXTURE_SIZE) + TEXTURE_SIZE * 0.25, (y * TEXTURE_SIZE) + TEXTURE_SIZE * 0.25, TEXTURE_SIZE * 0.5, TEXTURE_SIZE * 0.5, GROUND_COLOR);

}
void MapVisualGenerator::_drawEnemy(Map &map, int x, int y) {
    (void)map;
    draw_rect(_mapView, (x * TEXTURE_SIZE) + TEXTURE_SIZE * 0.25, (y * TEXTURE_SIZE) + TEXTURE_SIZE * 0.25, TEXTURE_SIZE * 0.5, TEXTURE_SIZE * 0.5, GROUND_COLOR);
}

bool MapVisualGenerator::_isCellBridgeOrGround(char cell) {
    return (cell == '1' || cell == '2' || cell == 'S' || cell == 'E' || cell == 'C');
}