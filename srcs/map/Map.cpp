#include "map/Map.hpp"

Map::Map() : _nbCollectible(0), _start((t_veci){0, 0}), _mapView(NULL), _mapPreview(NULL) {

    for (int x = 0; x < MAP_WIDTH; ++x) {
        for (int y = 0; y < MAP_HEIGHT; ++y) {
            _map[x][y] = new Ocean();
        }
    }
}

Map::~Map() {
    for (int x = 0; x < MAP_WIDTH; ++x) {
        for (int y = 0; y < MAP_HEIGHT; ++y) {
            delete _map[x][y];
        }
    }
}

void    Map::setTile(int x, int y, Tile *tile) {
    if (x >= 0 && x < MAP_WIDTH && y >= 0 && y < MAP_HEIGHT) {
        delete _map[x][y]; // Delete the old tile
        _map[x][y] = tile; // Set the new tile
    }
}