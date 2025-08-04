#include "map/MapTools.hpp"

MapTools::~MapTools() {}

Map *MapTools::generateMap() {
    Map *newMap = new Map();
    int tmpMap[MAP_WIDTH][MAP_HEIGHT];
    int tmpMapVar[MAP_WIDTH][MAP_HEIGHT];
     _clearMap(tmpMap);
    _clearMap(tmpMapVar);

    _generateIsland(tmpMap, tmpMapVar);
    _generateDeepSea(tmpMap, tmpMapVar);
    _generateTallGrass(tmpMap, tmpMapVar);
    _generateFlower(newMap);
    for (int x = 0; x < MAP_WIDTH; x++) {
        for (int y = 0; y < MAP_HEIGHT; y++) {
            newMap->setTile(x, y, _createTile(tmpMap[x][y], tmpMapVar[x][y]));
            
        }
    }

    return newMap;
}

void MapTools::generateView(Map *map, mlx_image_t *image) {
    if (!image)
        return;

    for (uint32_t x = 0; x < MAP_WIDTH; x++) {
        for (uint32_t y = 0; y < MAP_HEIGHT; y++) {
            _drawTile(image, x, y, map->getTile(x, y));
        }
    }
}

void MapTools::_generateIsland(int map[MAP_WIDTH][MAP_HEIGHT], int mapVar[MAP_WIDTH][MAP_HEIGHT]) {
    int islandType = rand() % 4;
    // islandType = LAKE_ISLAND; // For testing purposes, always generate a basic island

    if (islandType == CRESCENT_ISLAND) {
        std::cout << "Generating island type: Crescent" << std::endl;
        _generateCrescentIsland(map);
    } else if (islandType == LAKE_ISLAND) {
        std::cout << "Generating island type: Lake" << std::endl;
        _generateLakeIsland(map);
    } else if (islandType == ARCHIPELAGO) {
        std::cout << "Generating island type: Archipelago" << std::endl;
        _generateArchipelago(map);
    } else {
        std::cout << "Generating island type: Basic" << std::endl;
        _generateBasicIsland(map);
    }
    _mappingLakes(map);
    _generateBeach(map, mapVar, islandType);

}

void MapTools::_generateBasicIsland(int map[MAP_WIDTH][MAP_HEIGHT]) {
    GameLife gameLife;
    gameLife.generateGrid(MAP_WIDTH, MAP_HEIGHT, MAP_MARGING * 2, MAP_BASIC_DENSITY);
    gameLife.updateLife(20);
    for (uint32_t x = 0; x < MAP_WIDTH; x++) {
        for (uint32_t y = 0; y < MAP_HEIGHT; y++) {
            if (gameLife.getCell(x, y))
                map[x][y] = TILE_GRASS;
        }
    }
}

void MapTools::_generateCrescentIsland(int map[MAP_WIDTH][MAP_HEIGHT]) {
    GameLife gameLife;
    int width = (MAP_WIDTH - MAP_MARGING * 2) / 2;
    int height = (MAP_HEIGHT - MAP_MARGING * 2) / 2;

    gameLife.generateGrid(MAP_WIDTH, MAP_HEIGHT, MAP_MARGING, 0);
    gameLife.fillZone(MAP_MARGING, MAP_MARGING, width, height, MAP_BASIC_DENSITY, 0);
    gameLife.fillZone(MAP_WIDTH / 2, MAP_MARGING, width, height, MAP_BASIC_DENSITY, 0);
    gameLife.fillZone(MAP_MARGING, MAP_HEIGHT / 2, width, height, MAP_BASIC_DENSITY, 0);
    gameLife.fillZone(MAP_WIDTH / 2, MAP_HEIGHT / 2, width, height, MAP_BASIC_DENSITY, 2);
    gameLife.updateLife(20);

    for (uint32_t x = 0; x < MAP_WIDTH; x++) {
        for (uint32_t y = 0; y < MAP_HEIGHT; y++) {
            if (gameLife.getCell(x, y))
                map[x][y] = TILE_GRASS;
        }
    }
}

void MapTools::_generateLakeIsland(int map[MAP_WIDTH][MAP_HEIGHT]) {
    GameLife gameLife;
    int x = (MAP_WIDTH / 2) - (MAP_WIDTH / 8);
    int y = (MAP_HEIGHT / 2) - (MAP_HEIGHT / 8);

    gameLife.generateGrid(MAP_WIDTH, MAP_HEIGHT, MAP_MARGING * 1.5, MAP_BASIC_DENSITY);
    gameLife.clearZone(x, y, MAP_WIDTH / 4, MAP_HEIGHT / 4);
    gameLife.updateLife(20);
    for (uint32_t x = 0; x < MAP_WIDTH; x++) {
        for (uint32_t y = 0; y < MAP_HEIGHT; y++) {
            if (gameLife.getCell(x, y))
                map[x][y] = TILE_GRASS;
        }
    }
}

void MapTools::_generateArchipelago(int map[MAP_WIDTH][MAP_HEIGHT]) {
    GameLife gameLife;

    gameLife.generateGrid(MAP_WIDTH, MAP_HEIGHT, MAP_MARGING, MAP_ARCHI_DENSITY);
    gameLife.updateLife(20);

    for (uint32_t x = 0; x < MAP_WIDTH; x++) {
        for (uint32_t y = 0; y < MAP_HEIGHT; y++) {
            if (gameLife.getCell(x, y))
                map[x][y] = TILE_GRASS;
        }
    }
}

void MapTools::_generateBeach(int map[MAP_WIDTH][MAP_HEIGHT], int mapVar[MAP_WIDTH][MAP_HEIGHT], int islandType) {
    int tmpBeachMap[MAP_WIDTH][MAP_HEIGHT];
    _clearMap(tmpBeachMap);

    if (islandType == CRESCENT_ISLAND) {
        _generateBeachForCrescentIsland(tmpBeachMap);
    } else if (islandType == LAKE_ISLAND) {
        _generateBeachForLakeIsland(tmpBeachMap);
    } else if (islandType == ARCHIPELAGO) {
        _generateBeachForArchipelago(tmpBeachMap);
    } else {
        _generateBeachForBasicIsland(tmpBeachMap);
    }
    for (int x = 0; x < MAP_WIDTH; x++) {
        for (int y = 0; y < MAP_HEIGHT; y++) {
            if (tmpBeachMap[x][y] && map[x][y] == TILE_OCEAN){
                map[x][y] = TILE_SAND;
                if (!_isLandNearWater(map, x, y))
                    mapVar[x][y] = 1; // Mark as beach
            }
        }
    }
}

void MapTools::_generateBeachForBasicIsland(int map[MAP_WIDTH][MAP_HEIGHT]) {
    GameLife gameLife;
    gameLife.generateGrid(MAP_WIDTH, MAP_HEIGHT, MAP_MARGING * 1.5, MAP_BEACH_DENSITY);
    gameLife.updateLife(20);

    for (uint32_t x = 0; x < MAP_WIDTH; x++) {
        for (uint32_t y = 0; y < MAP_HEIGHT; y++) {
            if (gameLife.getCell(x, y)) {
                map[x][y] = TILE_SAND;
            }
        }
    }
}

void MapTools::_generateBeachForCrescentIsland(int map[MAP_WIDTH][MAP_HEIGHT]) {
    GameLife gameLife;
    gameLife.generateGrid(MAP_WIDTH, MAP_HEIGHT, MAP_MARGING * 2, 0);
    gameLife.fillZone(MAP_WIDTH / 3 , MAP_HEIGHT / 3, MAP_WIDTH / 2.5, MAP_HEIGHT / 2.5, MAP_BEACH_DENSITY, 0);
    gameLife.fillZone(MAP_WIDTH / 5, MAP_HEIGHT / 5, MAP_WIDTH / 1.75, MAP_HEIGHT / 6, MAP_BEACH_DENSITY, 0);
    gameLife.fillZone(MAP_WIDTH / 5, MAP_HEIGHT / 5 + MAP_HEIGHT / 6, MAP_WIDTH / 6, MAP_HEIGHT / 1.75 - MAP_HEIGHT / 6, MAP_BEACH_DENSITY, 0);

    gameLife.updateLife(20);

    for (uint32_t x = 0; x < MAP_WIDTH; x++) {
        for (uint32_t y = 0; y < MAP_HEIGHT; y++) {
            if (gameLife.getCell(x, y)) {
                map[x][y] = TILE_SAND;
            }
        }
    }
}

void MapTools::_generateBeachForLakeIsland(int map[MAP_WIDTH][MAP_HEIGHT]) {
    GameLife gameLife;
    gameLife.generateGrid(MAP_WIDTH, MAP_HEIGHT, MAP_MARGING, 0);
    gameLife.fillBorder(MAP_MARGING, MAP_MARGING, MAP_WIDTH - MAP_MARGING, MAP_HEIGHT - MAP_MARGING, MAP_BEACH_DENSITY, MAP_MARGING * 2);
    gameLife.updateLife(20);

    for (uint32_t x = 0; x < MAP_WIDTH; x++) {
        for (uint32_t y = 0; y < MAP_HEIGHT; y++) {
            if (gameLife.getCell(x, y)) {
                map[x][y] = TILE_SAND;
            }
        }
    }
}

void MapTools::_generateBeachForArchipelago(int map[MAP_WIDTH][MAP_HEIGHT]) {
    GameLife gameLife;
    gameLife.generateGrid(MAP_WIDTH, MAP_HEIGHT, MAP_MARGING * 2, 0);
    gameLife.fillZone(MAP_WIDTH / 4, MAP_HEIGHT / 4, MAP_WIDTH / 2, MAP_HEIGHT / 2, MAP_BEACH_DENSITY, 0);

    int angleW = MAP_WIDTH - (MAP_WIDTH / 8) - (MAP_WIDTH / 3.5);
    int angleH = MAP_HEIGHT - (MAP_HEIGHT / 8) - (MAP_HEIGHT / 3.5);
    gameLife.fillZone(MAP_WIDTH / 8, MAP_HEIGHT / 8, MAP_WIDTH / 3.5, MAP_HEIGHT / 3.5, MAP_BEACH_DENSITY, 0);
    gameLife.fillZone(angleW, angleH, MAP_WIDTH / 3.5, MAP_HEIGHT / 3.5, MAP_BEACH_DENSITY, 0);
    gameLife.fillZone(angleW, MAP_HEIGHT / 8, MAP_WIDTH / 3.5, MAP_HEIGHT / 3.5, MAP_BEACH_DENSITY, 0);
    gameLife.fillZone(MAP_WIDTH / 8, angleH, MAP_WIDTH / 3.5, MAP_HEIGHT / 3.5, MAP_BEACH_DENSITY, 0);
    gameLife.updateLife(20);

    for (uint32_t x = 0; x < MAP_WIDTH; x++) {
        for (uint32_t y = 0; y < MAP_HEIGHT; y++) {
            if (gameLife.getCell(x, y)) {
                map[x][y] = TILE_SAND;
            }
        }
    }
}

void MapTools::_generateDock(int map[MAP_WIDTH][MAP_HEIGHT]) {
    (void) map; // Suppress unused variable warning
    std::cout << "Generating dock..." << std::endl;
}

void MapTools::_generateTallGrass(int map[MAP_WIDTH][MAP_HEIGHT], int mapVar[MAP_WIDTH][MAP_HEIGHT]) {
    GameLife gameLife;
    gameLife.generateGrid(MAP_WIDTH, MAP_HEIGHT, 0, MAP_GRASS_DENSITY);
    gameLife.updateLife(20);
    for (uint32_t x = 0; x < MAP_WIDTH; x++) {
        for (uint32_t y = 0; y < MAP_HEIGHT; y++) {
            if (map[x][y] == TILE_GRASS && !gameLife.getCell(x, y)) {
                mapVar[x][y] = 1; // Mark as tall grass
            }
        }
    }
}

void MapTools::_generateFlower(Map *map) {
    GameLife    gameLife;
    int         mapFlower[MAP_WIDTH][MAP_HEIGHT];
    _clearMap(mapFlower);

    gameLife.generateGrid(MAP_WIDTH, MAP_HEIGHT, MAP_MARGING, 1);
    gameLife.updateLife(20);

    for (int i = 0; i < MAP_WIDTH; i++) {
        for (int j = 0; j < MAP_HEIGHT; j++) {
            std::cout << map->getTileType(i, j) << " tile grass:" << TILE_GRASS << std::endl;
            if (map->getTileType(i, j) == TILE_GRASS && gameLife.getCell(i, j)) {
                std::cout << "flower" << std::endl;
                Grass *tile = reinterpret_cast<Grass *>(map->getTile(i, j));
                tile->setFlower(true);
            }
        }
    }

}

void MapTools::_generateDeepSea(int map[MAP_WIDTH][MAP_HEIGHT], int mapVar[MAP_WIDTH][MAP_HEIGHT]) {
    GameLife gameLife;
    gameLife.generateGrid(MAP_WIDTH, MAP_HEIGHT, 0, 0);
    gameLife.fillBorder(0, 0, MAP_WIDTH, MAP_HEIGHT, 1, 1);
    gameLife.fillBorder(0, 0, MAP_WIDTH, MAP_HEIGHT, MAP_DEEP_DENSITY, MAP_MARGING + 1);
    gameLife.updateLife(20);
    gameLife.fillBorder(0, 0, MAP_WIDTH, MAP_HEIGHT, 1, MAP_MARGING * 0.6);

    for (uint32_t x = 0; x < MAP_WIDTH; x++) {
        for (uint32_t y = 0; y < MAP_HEIGHT; y++) {
            if ((map[x][y] == TILE_OCEAN || map[x][y] == TILE_SAND) && gameLife.getCell(x, y)) {
                map[x][y] = TILE_OCEAN;
                mapVar[x][y] = 1;
            }
        }
    }
}

void MapTools::_generateCollectible(Map *map) {
    (void) map; // Suppress unused variable warning
    std::cout << "Generating collectibles..." << std::endl;
}

void MapTools::_mappingLakes(int map[MAP_WIDTH][MAP_HEIGHT]) {
    int lakeMapping[MAP_WIDTH][MAP_HEIGHT];
    _clearMap(lakeMapping);
    _spreadingAlgoOcean(map, lakeMapping, 0, 0);
    for (int x = 0; x < MAP_WIDTH; x++) {
        for (int y = 0; y < MAP_HEIGHT; y++) {
            if (map[x][y] == TILE_OCEAN && lakeMapping[x][y] == 0) {
                map[x][y] = TILE_LAKE;
            }
        }
    }
}

void MapTools::_spreadingAlgoOcean(int map[MAP_WIDTH][MAP_HEIGHT], int lakeMapping[MAP_WIDTH][MAP_HEIGHT], int x, int y) {
    if (x < 0 || x >= MAP_WIDTH || y < 0 || y >= MAP_HEIGHT || map[x][y] != TILE_OCEAN || lakeMapping[x][y] != 0) {
        return;
    }
    lakeMapping[x][y] = 1;
    _spreadingAlgoOcean(map, lakeMapping, x + 1, y);
    _spreadingAlgoOcean(map, lakeMapping, x - 1, y);
    _spreadingAlgoOcean(map, lakeMapping, x, y + 1);
    _spreadingAlgoOcean(map, lakeMapping, x, y - 1);
}

bool MapTools::_isLandNearWater(int map[MAP_WIDTH][MAP_HEIGHT], int x, int y) {
    if (x + 1 < MAP_WIDTH && map[x + 1][y] == TILE_GRASS) {
        return true;
    }
    if (x - 1 > 0 && map[x - 1][y] == TILE_GRASS) {
        return true;
    }
    if (y + 1 < MAP_HEIGHT && map[x][y + 1] == TILE_GRASS) {
        return true;
    }
    if (y - 1 > 0 && map[x][y - 1] == TILE_GRASS) {
        return true;
    }
    return false;
}

int MapTools::_getSumLandSurfaces(int map[MAP_WIDTH][MAP_HEIGHT]) {
    (void) map; // Suppress unused variable warning
    std::cout << "Calculating sum of surfaces..." << std::endl;
    return 0; // Placeholder return value
}

t_veci MapTools::_findLandFromBorder(int map[MAP_WIDTH][MAP_HEIGHT], int side, int pos, int dir) {
    (void) map; // Suppress unused variable warning
    std::cout << "Finding land from border side: " << side << ", position: " << pos << ", direction: " << dir << std::endl;
    return (t_veci){0, 0}; // Placeholder return value
}

void MapTools::_clearMap(int map[MAP_WIDTH][MAP_HEIGHT]) {
    for (int x = 0; x < MAP_WIDTH; x++) {
        for (int y = 0; y < MAP_HEIGHT; y++) {
            map[x][y] = 0; // Initialize the map with '0'
        }
    }
}

Tile *MapTools::_createTile(int tile, int variant) {
    if (tile == TILE_GRASS)
        return new Grass(2, variant);
    else if (tile == TILE_LAKE)
        return new Lake();
    else if (tile == TILE_SAND)
        return new Sand(1, variant);
    else if (tile == TILE_DOCK)
        return new Dock();
    else
        return new Ocean(variant);
}

void MapTools::_drawTile(mlx_image_t *image, int x, int y, Tile *tile) {
    uint32_t color = 0;
    int tileType = tile->getType();
    int tileVariant = tile->getVariant();
    if (tileType == TILE_GRASS) {
        color = SHORT_GRASS_COLOR;
        if (tileVariant == 1)
            color = LONG_GRASS_COLOR;
        draw_rect(image, x * MAP_TILE_SIZE, y * MAP_TILE_SIZE, MAP_TILE_SIZE, MAP_TILE_SIZE, color);
        if (reinterpret_cast<Grass *>(tile)->hasFlower()) {
            draw_rect(image, (x * MAP_TILE_SIZE) + MAP_TILE_SIZE / 4, (y * MAP_TILE_SIZE) * MAP_TILE_SIZE / 4, MAP_TILE_SIZE / 2, MAP_TILE_SIZE / 2, FLOWER_COLOR);
        }
    } else if (tileType == TILE_LAKE) {
        color = LAKE_COLOR;
        draw_rect(image, x * MAP_TILE_SIZE, y * MAP_TILE_SIZE, MAP_TILE_SIZE, MAP_TILE_SIZE, color);
    } else if (tileType == TILE_SAND) {
        color = SAND_COLOR;
        if (tileVariant == 1) {
            color = SANDWATERED_COLOR;
        }
        draw_rect(image, x * MAP_TILE_SIZE, y * MAP_TILE_SIZE, MAP_TILE_SIZE, MAP_TILE_SIZE, color);
    } else if (tileType == TILE_DOCK) {
        color = BRIDGE_COLOR;
        draw_rect(image, x * MAP_TILE_SIZE, y * MAP_TILE_SIZE, MAP_TILE_SIZE, MAP_TILE_SIZE, color);
    } else if (tileType == TILE_OCEAN) {
        if (tileVariant == 1) {
            color = DEEP_WATER_COLOR;
        } else {
            color = WATER_COLOR;
        }
        draw_rect(image, x * MAP_TILE_SIZE, y * MAP_TILE_SIZE, MAP_TILE_SIZE, MAP_TILE_SIZE, color);
    }
}
