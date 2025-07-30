#include "map/MapTools.hpp"

MapTools::~MapTools() {
    std::cout << "MapGenerator destructor called" << std::endl;
}

Map *MapTools::generateMap() {
    Map *newMap = new Map();
    int tmpMap[MAP_WIDTH][MAP_HEIGHT];

    _clearMap(tmpMap);
    _generateIsland(tmpMap);
    for (int x = 0; x < MAP_WIDTH; x++) {
        for (int y = 0; y < MAP_HEIGHT; y++) {
            if (tmpMap[x][y])
                newMap->setTile(x, y, _createTile(tmpMap[x][y]));
        }
    }

    return newMap;
}

void MapTools::generateView(Map *map, mlx_image_t *image) {
    if (!image)
        return;

    for (uint32_t x = 0; x < MAP_WIDTH; x++) {
        for (uint32_t y = 0; y < MAP_HEIGHT; y++) {
            int tileType = map->getTileType(x, y);
            if (tileType == TILE_OCEAN) {
                mlx_put_pixel(image, x * MAP_TILE_SIZE, y * MAP_TILE_SIZE, WATER_COLOR);
            } else if (tileType == TILE_GRASS) {
                mlx_put_pixel(image, x * MAP_TILE_SIZE, y * MAP_TILE_SIZE, SHORT_GRASS_COLOR);
            } else if (tileType == TILE_LAKE) {
                mlx_put_pixel(image, x * MAP_TILE_SIZE, y * MAP_TILE_SIZE, DEEP_WATER_COLOR);
            } else if (tileType == TILE_SAND) {
                mlx_put_pixel(image, x * MAP_TILE_SIZE, y * MAP_TILE_SIZE, GROUND_COLOR);
            } else if (tileType == TILE_DOCK) {
                mlx_put_pixel(image, x * MAP_TILE_SIZE, y * MAP_TILE_SIZE, BRIDGE_COLOR);
            }
        }
    }
}

void MapTools::_generateIsland(int map[MAP_WIDTH][MAP_HEIGHT]) {
    int islandType = rand() % 4;

    if (islandType == BASIC_ISLAND) {
        _generateBasicIsland(map);
    } else if (islandType == CRESCENT_ISLAND) {
        _generateCrescentIsland(map);
    } else if (islandType == LAKE_ISLAND) {
        _generateLakeIsland(map);
    } else if (islandType == ARCHIPELAGO) {
        _generateArchipelago(map);
    }
    _generateBeach(map, islandType);

}

void MapTools::_generateBasicIsland(int map[MAP_WIDTH][MAP_HEIGHT]) {
    GameLife gameLife;
    gameLife.generateGrid(MAP_WIDTH, MAP_HEIGHT, MAP_MARGING, MAP_BASIC_DENSITY);
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

    gameLife.generateGrid(MAP_WIDTH, MAP_HEIGHT, MAP_MARGING, MAP_BASIC_DENSITY);
    gameLife.fillZone(x, y, MAP_WIDTH / 4, MAP_HEIGHT / 4, MAP_LAKE_DENSITY, MAP_MARGING);
    gameLife.updateLife(20);
    for (uint32_t x = 0; x < MAP_WIDTH; x++) {
        for (uint32_t y = 0; y < MAP_HEIGHT; y++) {
            if (gameLife.getCell(x, y))
                map[x][y] = TILE_LAKE;
        }
    }
}

void MapTools::_generateArchipelago(int map[MAP_WIDTH][MAP_HEIGHT]) {
    GameLife gameLife;

    gameLife.generateGrid(MAP_WIDTH, MAP_HEIGHT, MAP_MARGING, MAP_ARCHI_DENSITY);
    gameLife.updateLife(5);

    for (uint32_t x = 0; x < MAP_WIDTH; x++) {
        for (uint32_t y = 0; y < MAP_HEIGHT; y++) {
            if (gameLife.getCell(x, y))
                map[x][y] = TILE_GRASS;
        }
    }
}

void MapTools::_generateBeach(int map[MAP_WIDTH][MAP_HEIGHT], int islandType) {
    (void) map; // Suppress unused variable warning
    std::cout << "Generating beach for island type: " << islandType << std::endl;
}

void MapTools::_generateDock(int map[MAP_WIDTH][MAP_HEIGHT]) {
    (void) map; // Suppress unused variable warning
    std::cout << "Generating dock..." << std::endl;
}

void MapTools::_generateTallGrass(Map *map) {
    (void) map; // Suppress unused variable warning
    std::cout << "Generating tall grass..." << std::endl;
}

void MapTools::_generateFlower(Map *map) {
    (void) map; // Suppress unused variable warning
    std::cout << "Generating flowers..." << std::endl;
}

void MapTools::_generateDeepSea(Map *map) {
    (void) map; // Suppress unused variable warning
    std::cout << "Generating deep sea..." << std::endl;
}

void MapTools::_generateCollectible(Map *map) {
    (void) map; // Suppress unused variable warning
    std::cout << "Generating collectibles..." << std::endl;
}

void MapTools::_mappingLakes(int map[MAP_WIDTH][MAP_HEIGHT]) {
    (void) map; // Suppress unused variable warning
    std::cout << "Mapping islands..." << std::endl;
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
            map[x][y] = '0'; // Initialize the map with '0'
        }
    }
}

Tile *MapTools::_createTile(int tile) {
    Tile *newTile = NULL;
    if (tile == TILE_GRASS)
        newTile = new Grass();
    else if (tile == TILE_LAKE)
        newTile = new Lake();
    else if (tile == TILE_SAND)
        newTile = new Sand();
    else if (tile == TILE_DOCK)
        newTile = new Dock();
    else if (tile == TILE_OCEAN)
        newTile = new Ocean();
    return newTile;
}
