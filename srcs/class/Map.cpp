#include "Map.hpp"

Map::Map() : _nbCollectible(0), _nbCollectibleLeft(0), _start((t_veci){.x = 0, .y = 0}), _enemy((t_veci){.x = 0, .y = 0}), _mapCreated(false) {
	std::cout << "Map constructor called, generating map" << std::endl;
	for (int32_t i = 0; i < MAP_WIDTH; i++) {
		for (int32_t j = 0; j < MAP_HEIGHT; j++) {
			_map[i][j] = '0';
		}
	}
}

Map::~Map() {
	std::cout << "Map destructor called" << std::endl;
}

Map::Map(Map const &src) {
	std::cout << "Map copy constructor called" << std::endl;
	*this = src;
}

Map &Map::operator=(Map const &rhs) {
	std::cout << "Map assignment operator called" << std::endl;
	if (this != &rhs) {
		for (int32_t i = 0; i < MAP_WIDTH; i++) {
			for (int32_t j = 0; j < MAP_HEIGHT; j++) {
				_map[i][j] = rhs._map[i][j];
			}
		}
		_nbCollectible = rhs._nbCollectible;
		_nbCollectibleLeft = rhs._nbCollectibleLeft;
		_start = rhs._start;
		_enemy = rhs._enemy;
		_mapCreated = rhs._mapCreated;
	}
	return (*this);
}

void Map::initMap() {
	MapGenerator mapGenerator;
	mapGenerator.generateMap(_map);
	_parseMapElement();
	_mapCreated = true;
}

void createMapImage(mlx_image_t *map_img, uint32_t tile_size) {
	(void)map_img;
	if (map_img->width != MAP_WIDTH * tile_size || map_img->height != MAP_HEIGHT * tile_size) {
		if (!resize_image(map_img, MAP_WIDTH * tile_size, MAP_HEIGHT * tile_size)) {
			exit_error("Failed to resize image");
		}
	}
	GameLife gameLife(100,100,0.55);
	gameLife.generateGrid();
	for (int i = 0; i < 100; i++) {
		gameLife.updateLife();
	}
	for (uint32_t i = 0; i < MAP_WIDTH; i++) {
		for (uint32_t j = 0; j < MAP_HEIGHT; j++) {
			if (gameLife.getCell(i, j) == '1') {
				draw_rect(map_img, i * tile_size, j * tile_size, tile_size, tile_size, 0xFFFFFFFF);
			}
			if (gameLife.getCell(i, j) == '0') {
				draw_rect(map_img, i * tile_size, j * tile_size, tile_size, tile_size, 0x000000FF);
			}
		}
	}
}

void Map::displayMap(mlx_image_t *renderer) const {
	for (int32_t i = 0; i < MAP_WIDTH; i++) {
		for (int32_t j = 0; j < MAP_HEIGHT; j++) {
			if (_map[i][j] == '1') {
				draw_rect(renderer, i * TILE_SIZE, j * TILE_SIZE, TILE_SIZE, TILE_SIZE, 0x00FF00FF);
			}
			else if (_map[i][j] == 'S') {
				draw_rect(renderer, i * TILE_SIZE, j * TILE_SIZE, TILE_SIZE, TILE_SIZE, 0x00FFFFFF);
			}
			else if (_map[i][j] == 'E') {
				draw_rect(renderer, i * TILE_SIZE, j * TILE_SIZE, TILE_SIZE, TILE_SIZE, 0xFF00FFFF);
			}
			else if (_map[i][j] == 'C') {
				draw_rect(renderer, i * TILE_SIZE, j * TILE_SIZE, TILE_SIZE, TILE_SIZE, 0xFFFF00FF);
			}
			else {
				draw_rect(renderer, i * TILE_SIZE, j * TILE_SIZE, TILE_SIZE, TILE_SIZE, 0x0000FFFF);
			}
		}
	}
}

void Map::_parseMapElement() {
	for (int32_t i = 0; i < MAP_WIDTH; i++) {
		for (int32_t j = 0; j < MAP_HEIGHT; j++) {
			if (_map[i][j] == 'S') {
				_start.x = i;
				_start.y = j;
			}
			else if (_map[i][j] == 'E') {
				_enemy.x = i;
				_enemy.y = j;
			}
			else if (_map[i][j] == 'C') {
				_nbCollectible++;
			}
		}
	}
	_nbCollectibleLeft = _nbCollectible;
}

